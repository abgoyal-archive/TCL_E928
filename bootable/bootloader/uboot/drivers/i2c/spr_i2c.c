

#include <common.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/spr_i2c.h>

static struct i2c_regs *const i2c_regs_p =
    (struct i2c_regs *)CONFIG_SYS_I2C_BASE;

static void set_speed(int i2c_spd)
{
	unsigned int cntl;
	unsigned int hcnt, lcnt;
	unsigned int high, low;

	cntl = (readl(&i2c_regs_p->ic_con) & (~IC_CON_SPD_MSK));

	switch (i2c_spd) {
	case IC_SPEED_MODE_MAX:
		cntl |= IC_CON_SPD_HS;
		high = MIN_HS_SCL_HIGHTIME;
		low = MIN_HS_SCL_LOWTIME;
		break;

	case IC_SPEED_MODE_STANDARD:
		cntl |= IC_CON_SPD_SS;
		high = MIN_SS_SCL_HIGHTIME;
		low = MIN_SS_SCL_LOWTIME;
		break;

	case IC_SPEED_MODE_FAST:
	default:
		cntl |= IC_CON_SPD_FS;
		high = MIN_FS_SCL_HIGHTIME;
		low = MIN_FS_SCL_LOWTIME;
		break;
	}

	writel(cntl, &i2c_regs_p->ic_con);

	hcnt = (IC_CLK * high) / NANO_TO_MICRO;
	writel(hcnt, &i2c_regs_p->ic_fs_scl_hcnt);

	lcnt = (IC_CLK * low) / NANO_TO_MICRO;
	writel(lcnt, &i2c_regs_p->ic_fs_scl_lcnt);
}

void i2c_set_bus_speed(int speed)
{
	if (speed >= I2C_MAX_SPEED)
		set_speed(IC_SPEED_MODE_MAX);
	else if (speed >= I2C_FAST_SPEED)
		set_speed(IC_SPEED_MODE_FAST);
	else
		set_speed(IC_SPEED_MODE_STANDARD);
}

int i2c_get_bus_speed(void)
{
	u32 cntl;

	cntl = (readl(&i2c_regs_p->ic_con) & IC_CON_SPD_MSK);

	if (cntl == IC_CON_SPD_HS)
		return I2C_MAX_SPEED;
	else if (cntl == IC_CON_SPD_FS)
		return I2C_FAST_SPEED;
	else if (cntl == IC_CON_SPD_SS)
		return I2C_STANDARD_SPEED;

	return 0;
}

void i2c_init(int speed, int slaveadd)
{
	unsigned int enbl;

	/* Disable i2c */
	enbl = readl(&i2c_regs_p->ic_enable);
	enbl &= ~IC_ENABLE_0B;
	writel(enbl, &i2c_regs_p->ic_enable);

	writel((IC_CON_SD | IC_CON_SPD_FS | IC_CON_MM), &i2c_regs_p->ic_con);
	writel(IC_RX_TL, &i2c_regs_p->ic_rx_tl);
	writel(IC_TX_TL, &i2c_regs_p->ic_tx_tl);
	i2c_set_bus_speed(speed);
	writel(IC_STOP_DET, &i2c_regs_p->ic_intr_mask);
	writel(slaveadd, &i2c_regs_p->ic_sar);

	/* Enable i2c */
	enbl = readl(&i2c_regs_p->ic_enable);
	enbl |= IC_ENABLE_0B;
	writel(enbl, &i2c_regs_p->ic_enable);
}

static void i2c_setaddress(unsigned int i2c_addr)
{
	writel(i2c_addr, &i2c_regs_p->ic_tar);
}

static void i2c_flush_rxfifo(void)
{
	while (readl(&i2c_regs_p->ic_status) & IC_STATUS_RFNE)
		readl(&i2c_regs_p->ic_cmd_data);
}

static int i2c_wait_for_bb(void)
{
	unsigned long start_time_bb = get_timer(0);

	while ((readl(&i2c_regs_p->ic_status) & IC_STATUS_MA) ||
	       !(readl(&i2c_regs_p->ic_status) & IC_STATUS_TFE)) {

		/* Evaluate timeout */
		if (get_timer(start_time_bb) > (unsigned long)(I2C_BYTE_TO_BB))
			return 1;
	}

	return 0;
}

/* check parameters for i2c_read and i2c_write */
static int check_params(uint addr, int alen, uchar *buffer, int len)
{
	if (buffer == NULL) {
		printf("Buffer is invalid\n");
		return 1;
	}

	if (alen > 1) {
		printf("addr len %d not supported\n", alen);
		return 1;
	}

	if (addr + len > 256) {
		printf("address out of range\n");
		return 1;
	}

	return 0;
}

static int i2c_xfer_init(uchar chip, uint addr)
{
	if (i2c_wait_for_bb()) {
		printf("Timed out waiting for bus\n");
		return 1;
	}

	i2c_setaddress(chip);
	writel(addr, &i2c_regs_p->ic_cmd_data);

	return 0;
}

static int i2c_xfer_finish(void)
{
	ulong start_stop_det = get_timer(0);

	while (1) {
		if ((readl(&i2c_regs_p->ic_raw_intr_stat) & IC_STOP_DET)) {
			readl(&i2c_regs_p->ic_clr_stop_det);
			break;
		} else if (get_timer(start_stop_det) > I2C_STOPDET_TO) {
			break;
		}
	}

	if (i2c_wait_for_bb()) {
		printf("Timed out waiting for bus\n");
		return 1;
	}

	i2c_flush_rxfifo();

	/* Wait for read/write operation to complete on actual memory */
	udelay(10000);

	return 0;
}

int i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned long start_time_rx;

	if (check_params(addr, alen, buffer, len))
		return 1;

	if (i2c_xfer_init(chip, addr))
		return 1;

	start_time_rx = get_timer(0);
	while (len) {
		writel(IC_CMD, &i2c_regs_p->ic_cmd_data);

		if (readl(&i2c_regs_p->ic_status) & IC_STATUS_RFNE) {
			*buffer++ = (uchar)readl(&i2c_regs_p->ic_cmd_data);
			len--;
			start_time_rx = get_timer(0);

		} else if (get_timer(start_time_rx) > I2C_BYTE_TO) {
				printf("Timed out. i2c read Failed\n");
				return 1;
		}
	}

	return i2c_xfer_finish();
}

int i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	int nb = len;
	unsigned long start_time_tx;

	if (check_params(addr, alen, buffer, len))
		return 1;

	if (i2c_xfer_init(chip, addr))
		return 1;

	start_time_tx = get_timer(0);
	while (len) {
		if (readl(&i2c_regs_p->ic_status) & IC_STATUS_TFNF) {
			writel(*buffer, &i2c_regs_p->ic_cmd_data);
			buffer++;
			len--;
			start_time_tx = get_timer(0);

		} else if (get_timer(start_time_tx) > (nb * I2C_BYTE_TO)) {
				printf("Timed out. i2c write Failed\n");
				return 1;
		}
	}

	return i2c_xfer_finish();
}

int i2c_probe(uchar chip)
{
	u32 tmp;

	/*
	 * Try to read the first location of the chip.
	 */
	return i2c_read(chip, 0, 1, (uchar *)&tmp, 1);
}

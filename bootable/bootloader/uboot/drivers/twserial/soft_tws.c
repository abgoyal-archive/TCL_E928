

#define TWS_IMPLEMENTATION
#include <common.h>

/*=====================================================================*/
/*                         Public Functions                            */
/*=====================================================================*/

int tws_read(uchar *buffer, int len)
{
	int rem = len;
	uchar accu, shift;

	debug("tws_read: buffer %p len %d\n", buffer, len);

	/* Configure the data pin for input */
	tws_data_config_output(0);

	/* Disable WR, i.e. setup a read */
	tws_wr(0);
	udelay(1);

	/* Rise CE */
	tws_ce(1);
	udelay(1);

	for (; rem > 0; ) {
		for (shift = 0, accu = 0;
		     (rem > 0) && (shift < 8);
		     rem--, shift++) {
			tws_clk(1);
			udelay(10);
			accu |= (tws_data_read() << shift); /* LSB first */
			tws_clk(0);
			udelay(10);
		}
		*buffer++ = accu;
	}

	/* Lower CE */
	tws_ce(0);

	return len - rem;
}


int tws_write(uchar *buffer, int len)
{
	int rem = len;
	uchar accu, shift;

	debug("tws_write: buffer %p len %d\n", buffer, len);

	/* Configure the data pin for output */
	tws_data_config_output(1);

	/* Enable WR, i.e. setup a write */
	tws_wr(1);
	udelay(1);

	/* Rise CE */
	tws_ce(1);
	udelay(1);

	for (; rem > 0; ) {
		for (shift = 0, accu = *buffer++;
		     (rem > 0) && (shift < 8);
		     rem--, shift++) {
			tws_data(accu & 0x01); /* LSB first */
			tws_clk(1);
			udelay(10);
			tws_clk(0);
			udelay(10);
			accu >>= 1;
		}
	}

	/* Lower CE */
	tws_ce(0);

	return len - rem;
}

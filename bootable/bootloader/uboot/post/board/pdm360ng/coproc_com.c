

#include <common.h>
#include <post.h>
#include <serial.h>

#if defined(CONFIG_SERIAL_MULTI)

char alive[] = "$AL;38\r\n";
char ping[] = "$PI;2C\n";

int coprocessor_post_test(int flags)
{
	struct stdio_dev *cop_port;
	int ret;
	char buf[10];

	/* Test IO Coprocessor communication */
	cop_port = open_port(4, CONFIG_SYS_PDM360NG_COPROC_BAUDRATE);
	if (!cop_port)
		return -1;

	write_port(cop_port, ping);
	udelay(CONFIG_SYS_PDM360NG_COPROC_READ_DELAY);

	memset(buf, 0, sizeof(buf));
	ret = read_port(cop_port, buf, sizeof(buf));
	close_port(4);
	if (ret <= 0) {
		post_log("Error: Can't read IO Coprocessor port.\n");
		return -1;
	}

	if (strcmp(buf, alive)) {
		post_log("Error: IO-Cop. resp.: %s\n", buf);
		return -1;
	}

	/* Test WD Coprocessor communication */
	cop_port = open_port(1, CONFIG_SYS_PDM360NG_COPROC_BAUDRATE);
	if (!cop_port) {
		post_log("Error: Can't open WD Coprocessor port.\n");
		return -1;
	}

	write_port(cop_port, ping);
	udelay(CONFIG_SYS_PDM360NG_COPROC_READ_DELAY);

	memset(buf, 0, sizeof(buf));
	ret = read_port(cop_port, buf, sizeof(buf));
	close_port(1);
	if (ret <= 0) {
		post_log("Error: Can't read WD Coprocessor port.\n");
		return -1;
	}

	if (strcmp(buf, alive)) {
		post_log("Error: WD-Cop. resp.: %s\n", buf);
		return -1;
	}

	return 0;
}
#endif	/* CONFIG_SERIAL_MULTI */

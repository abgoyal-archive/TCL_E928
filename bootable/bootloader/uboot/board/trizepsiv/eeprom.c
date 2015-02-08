

#include <common.h>
#include <command.h>
#include <dm9000.h>

static int do_read_dm9000_eeprom ( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]) {
	unsigned int i;
	u8 data[2];

	for (i=0; i < 0x40; i++) {
		if (!(i % 0x10))
			printf("\n%08x:", i);
		dm9000_read_srom_word(i, data);
		printf(" %02x%02x", data[1], data[0]);
	}
	printf ("\n");
	return (0);
}

static int do_write_dm9000_eeprom ( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]) {
	int offset,value;

	if (argc < 4) {
		cmd_usage(cmdtp);
		return 1;
	}

	offset=simple_strtoul(argv[2],NULL,16);
	value=simple_strtoul(argv[3],NULL,16);
	if (offset > 0x40) {
		printf("Wrong offset : 0x%x\n",offset);
		cmd_usage(cmdtp);
		return 1;
	}
	dm9000_write_srom_word(offset, value);
	return (0);
}

int do_dm9000_eeprom ( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]) {
	if (argc < 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	if (strcmp (argv[1],"read") == 0) {
		return (do_read_dm9000_eeprom(cmdtp,flag,argc,argv));
	} else if (strcmp (argv[1],"write") == 0) {
		return (do_write_dm9000_eeprom(cmdtp,flag,argc,argv));
	} else {
		cmd_usage(cmdtp);
		return 1;
	}
}

U_BOOT_CMD(
	dm9000ee,4,1,do_dm9000_eeprom,
	"Read/Write eeprom connected to Ethernet Controller",
	"\ndm9000ee write <word offset> <value> \n"
	"\tdm9000ee read \n"
	"\tword:\t\t00-02 : MAC Address\n"
	"\t\t\t03-07 : DM9000 Configuration\n"
	"\t\t\t08-63 : User data"
);



#ifndef __KEYMILE_COMMON_H
#define __KEYMILE_COMMON_H

int ethernet_present (void);
int ivm_read_eeprom (void);

#ifdef CONFIG_KEYMILE_HDLC_ENET
int keymile_hdlc_enet_initialize (bd_t *bis);
#endif

int fdt_set_node_and_value (void *blob,
			char *nodename,
			char *regname,
			void *var,
			int size);
int fdt_get_node_and_value (void *blob,
				char *nodename,
				char *propname,
				void **var);
#endif /* __KEYMILE_COMMON_H */

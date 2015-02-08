

#define NUM_PORTS	4
#define PORT_BITS	18

typedef struct {
    unsigned char conf:1;	/* If 1, configure this port		*/
    unsigned char ppar:1;	/* Port Pin Assignment Register		*/
    unsigned char psor:1;	/* Port Special Options Register	*/
    unsigned char pdir:1;	/* Port Data Direction Register		*/
    unsigned char podr:1;	/* Port Open Drain Register			*/
    unsigned char pdat:1;	/* Port Data Register				*/
    unsigned char pint:1;	/* Port Interrupt Register			*/
} mpc8xx_iop_conf_t;

extern void config_mpc8xx_ioports(volatile immap_t *immr);

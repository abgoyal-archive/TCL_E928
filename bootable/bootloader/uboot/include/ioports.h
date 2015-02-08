

typedef struct {
    unsigned int pdir;		/* Port Data Direction Register (35-3) */
    unsigned int ppar;		/* Port Pin Assignment Register (35-4) */
    unsigned int psor;		/* Port Special Options Register (35-5) */
    unsigned int podr;		/* Port Open Drain Register (35-2) */
    unsigned int pdat;		/* Port Data Register (35-3) */
} ioport_t;

#ifdef CONFIG_MPC85xx
#define ioport_addr(im, idx) (ioport_t *)((uint)&(im->im_cpm_iop) + ((idx)*0x20))
#else
#define ioport_addr(im, idx) (ioport_t *)((uint)&(im)->im_ioport + ((idx)*0x20))
#endif

typedef struct {
    unsigned char conf:1;	/* if 1, configure this port */
    unsigned char ppar:1;	/* Port Pin Assignment Register (35-4) */
    unsigned char psor:1;	/* Port Special Options Register (35-2) */
    unsigned char pdir:1;	/* Port Data Direction Register (35-3) */
    unsigned char podr:1;	/* Port Open Drain Register (35-2) */
    unsigned char pdat:1;	/* Port Data Register (35-2) */
} iop_conf_t;

extern const iop_conf_t iop_conf_tab[4][32];

typedef struct {
	unsigned char	port;
	unsigned char	pin;
	int		dir;
	int		open_drain;
	int		assign;
} qe_iop_conf_t;

#define QE_IOP_TAB_END	(-1)

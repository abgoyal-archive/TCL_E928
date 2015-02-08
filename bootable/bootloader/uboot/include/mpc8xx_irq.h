
#ifndef _MPC8XX_IRQ_H
#define _MPC8XX_IRQ_H

#define NR_SIU_INTS	16
#define	NR_8259_INTS	0

#define NR_IRQS	(NR_SIU_INTS + NR_8259_INTS)

#define	SIU_IRQ0	(0)	/* Highest priority */
#define	SIU_LEVEL0	(1)
#define	SIU_IRQ1	(2)
#define	SIU_LEVEL1	(3)
#define	SIU_IRQ2	(4)
#define	SIU_LEVEL2	(5)
#define	SIU_IRQ3	(6)
#define	SIU_LEVEL3	(7)
#define	SIU_IRQ4	(8)
#define	SIU_LEVEL4	(9)
#define	SIU_IRQ5	(10)
#define	SIU_LEVEL5	(11)
#define	SIU_IRQ6	(12)
#define	SIU_LEVEL6	(13)
#define	SIU_IRQ7	(14)
#define	SIU_LEVEL7	(15)


#ifdef CONFIG_SYS_CPM_INTERRUPT
# define CPM_INTERRUPT		CONFIG_SYS_CPM_INTERRUPT
#else
# define CPM_INTERRUPT		SIU_LEVEL2
#endif

#define	mk_int_int_mask(IL) (1 << (7 - (IL/2)))

#endif /* _MPC8XX_IRQ_H */

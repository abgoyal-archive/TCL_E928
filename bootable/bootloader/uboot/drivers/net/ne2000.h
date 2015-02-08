


#ifndef __DRIVERS_NE2000_H__
#define __DRIVERS_NE2000_H__

/* Enable NE2000 basic init function */
#define NE2000_BASIC_INIT

#define DP_DATA		0x10
#define START_PG	0x50	/* First page of TX buffer */
#define START_PG2	0x48
#define STOP_PG		0x80	/* Last page +1 of RX ring */

#define RX_START	0x50
#define RX_END		0x80

#define DP_IN(_b_, _o_, _d_)	(_d_) = *( (vu_char *) ((_b_)+(_o_)))
#define DP_OUT(_b_, _o_, _d_)	*( (vu_char *) ((_b_)+(_o_))) = (_d_)
#define DP_IN_DATA(_b_, _d_)	(_d_) = *( (vu_char *) ((_b_)))
#define DP_OUT_DATA(_b_, _d_)	*( (vu_char *) ((_b_))) = (_d_)
#endif /* __DRIVERS_NE2000_H__ */

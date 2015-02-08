
#ifndef _nicext_h_
#define _nicext_h_

#define SIOCNICE	SIOCDEVPRIVATE+7

struct nice_req
{
    __u32 cmd;

    union
    {
#ifdef __KERNEL__
	/* cmd = NICE_CMD_SET_RX or NICE_CMD_GET_RX */
	struct
	{
	    void (*nrqus1_rx)( struct sk_buff*, void* );
	    void* nrqus1_ctx;
	} nrqu_nrqus1;

	/* cmd = NICE_CMD_QUERY_SUPPORT */
	struct
	{
	    __u32 nrqus2_magic;
	    __u32 nrqus2_support_rx:1;
	    __u32 nrqus2_support_vlan:1;
	    __u32 nrqus2_support_get_speed:1;
	} nrqu_nrqus2;
#endif

	/* cmd = NICE_CMD_GET_SPEED */
	struct
	{
	    unsigned int nrqus3_speed; /* 0 if link is down, */
				       /* otherwise speed in Mbps */
	} nrqu_nrqus3;

	/* cmd = NICE_CMD_BLINK_LED */
	struct
	{
	    unsigned int nrqus4_blink_time; /* blink duration in seconds */
	} nrqu_nrqus4;

    } nrq_nrqu;
};

#define nrq_rx           nrq_nrqu.nrqu_nrqus1.nrqus1_rx
#define nrq_ctx          nrq_nrqu.nrqu_nrqus1.nrqus1_ctx
#define nrq_support_rx   nrq_nrqu.nrqu_nrqus2.nrqus2_support_rx
#define nrq_magic        nrq_nrqu.nrqu_nrqus2.nrqus2_magic
#define nrq_support_vlan nrq_nrqu.nrqu_nrqus2.nrqus2_support_vlan
#define nrq_support_get_speed nrq_nrqu.nrqu_nrqus2.nrqus2_support_get_speed
#define nrq_speed        nrq_nrqu.nrqu_nrqus3.nrqus3_speed
#define nrq_blink_time   nrq_nrqu.nrqu_nrqus4.nrqus4_blink_time

#define NICE_REQUESTOR_MAGIC            0x4543494E /* NICE in ascii */
#define NICE_DEVICE_MAGIC               0x4E494345 /* ECIN in ascii */

#define NICE_CMD_QUERY_SUPPORT          0x00000001
#define NICE_CMD_SET_RX                 0x00000002
#define NICE_CMD_GET_RX                 0x00000003
#define NICE_CMD_GET_SPEED              0x00000004
#define NICE_CMD_BLINK_LED              0x00000005

#endif  /* _nicext_h_ */

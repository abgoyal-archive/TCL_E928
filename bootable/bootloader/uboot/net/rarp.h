


#ifndef __RARP_H__
#define __RARP_H__

#ifndef __NET_H__
#include <net.h>
#endif /* __NET_H__ */


/**********************************************************************/

extern int	RarpTry;

extern void RarpRequest (void);	/* Send a RARP request */

/**********************************************************************/

#endif /* __RARP_H__ */

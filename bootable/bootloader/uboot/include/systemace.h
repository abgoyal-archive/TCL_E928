
#ifndef __SYSTEMACE_H
#define __SYSTEMACE_H
#ident "$Id:$"

#ifdef CONFIG_SYSTEMACE

# include  <part.h>

block_dev_desc_t *  systemace_get_dev(int dev);

#endif	/* CONFIG_SYSTEMACE */
#endif	/* __SYSTEMACE_H */




#ifndef __NIOS2_EPCS_H__
#define __NIOS2_EPCS_H__

typedef struct epcs_devinfo_t {
	const char	*name;		/* Device name */
	unsigned char	id;		/* Device silicon id */
	unsigned char	size;		/* Total size log2(bytes)*/
	unsigned char	num_sects;	/* Number of sectors */
	unsigned char	sz_sect;	/* Sector size log2(bytes) */
	unsigned char	sz_page;	/* Page size log2(bytes) */
	unsigned char   prot_mask;	/* Protection mask */
}epcs_devinfo_t;

extern int epcs_reset (void);

extern epcs_devinfo_t *epcs_dev_find (void);

extern int epcs_cfgsz (void);

extern int epcs_erase (unsigned start, unsigned end);

extern int epcs_read (ulong addr, ulong off, ulong cnt);

extern int epcs_write (ulong addr, ulong off, ulong cnt);

extern int epcs_verify (ulong addr, ulong off, ulong cnt, ulong *err);

#endif /* __NIOS2_EPCS_H__ */

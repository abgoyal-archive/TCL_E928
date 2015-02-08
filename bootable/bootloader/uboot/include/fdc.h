

#ifndef _FDC_H_
#define _FDC_H_

/* Functions prototype                                                       */
int fdc_fdos_init (int drive);
int fdc_fdos_seek (int where);
int fdc_fdos_read (void *buffer, int len);

int dos_open(char *name);
int dos_read (ulong addr);
int dos_dir (void);

#endif

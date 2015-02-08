

#ifndef _IO_MUX_H
#define _IO_MUX_H

#include <stdio_dev.h>


extern struct stdio_dev **console_devices[MAX_FILES];
extern int cd_count[MAX_FILES];

int iomux_doenv(const int, const char *);
void iomux_printdevs(const int);
struct stdio_dev *search_device(int, char *);

#endif /* _IO_MUX_H */

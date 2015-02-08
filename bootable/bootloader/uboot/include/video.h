

#ifndef _VIDEO_H_
#define _VIDEO_H_

/* Video functions */

int	video_init	(void *videobase);
void	video_putc	(const char c);
void	video_puts	(const char *s);
void	video_printf	(const char *fmt, ...);

//copy from mtk u-boot-1.1.6 /include/video.h
void video_clean_screen(void);
void video_set_cursor(int row, int col);
int  video_get_rows(void);
int  video_get_colums(void);

#endif

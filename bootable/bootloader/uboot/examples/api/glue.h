


#ifndef _API_GLUE_H_
#define _API_GLUE_H_

#define API_SEARCH_LEN		(3 * 1024 * 1024)	/* 3MB search range */

#define UB_MAX_MR	5	/* max mem regions number */
#define UB_MAX_DEV	6	/* max devices number */

extern void *syscall_ptr;
extern uint32_t search_hint;

int	syscall(int, int *, ...);
int	api_search_sig(struct api_signature **sig);


/* console */
int	ub_getc(void);
int	ub_tstc(void);
void	ub_putc(char c);
void	ub_puts(const char *s);

/* system */
void			ub_reset(void);
struct sys_info *	ub_get_sys_info(void);

/* time */
void		ub_udelay(unsigned long);
unsigned long	ub_get_timer(unsigned long);

/* env vars */
char *		ub_env_get(const char *name);
void		ub_env_set(const char *name, char *value);
const char *	ub_env_enum(const char *last);

/* devices */
int			ub_dev_enum(void);
int			ub_dev_open(int handle);
int			ub_dev_close(int handle);
int			ub_dev_read(int handle, void *buf, lbasize_t len,
				lbastart_t start, lbasize_t *rlen);
int			ub_dev_send(int handle, void *buf, int len);
int			ub_dev_recv(int handle, void *buf, int len, int *rlen);
struct device_info *	ub_dev_get(int);

#endif /* _API_GLUE_H_ */



struct fb_var_screeninfo {
	unsigned int xres;		/* visible resolution		*/
	unsigned int yres;

	unsigned int bits_per_pixel;	/* guess what			*/

	/* Timing: All values in pixclocks, except pixclock (of course) */
	unsigned int pixclock;		/* pixel clock in ps (pico seconds) */
	unsigned int left_margin;	/* time from sync to picture	*/
	unsigned int right_margin;	/* time from picture to sync	*/
	unsigned int upper_margin;	/* time from sync to picture	*/
	unsigned int lower_margin;
	unsigned int hsync_len;		/* length of horizontal sync	*/
	unsigned int vsync_len;		/* length of vertical sync	*/
	unsigned int sync;		/* see FB_SYNC_*		*/
	unsigned int vmode;		/* see FB_VMODE_*		*/
	unsigned int rotate;		/* angle we rotate counter clockwise */
};

struct fb_info {
	struct fb_var_screeninfo var;	/* Current var */
	unsigned long smem_start;	/* Start of frame buffer mem */
					/* (physical address) */
	unsigned int smem_len;		/* Length of frame buffer mem */
	unsigned int type;		/* see FB_TYPE_*		*/
	unsigned int line_length;	/* length of a line in bytes    */

	char *screen_base;
	unsigned long screen_size;
	int logo_height;
	unsigned int logo_size;
};


extern char *fsl_fb_open(struct fb_info **info);
extern int fsl_diu_init(int xres,
			unsigned int pixel_format,
			int gamma_fix,
			unsigned char *splash_bmp);
extern void fsl_diu_clear_screen(void);
extern int fsl_diu_display_bmp(unsigned char *bmp,
			       int xoffset,
			       int yoffset,
			       int transpar);

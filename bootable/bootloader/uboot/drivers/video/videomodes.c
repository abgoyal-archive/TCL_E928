


#include <common.h>
#include "videomodes.h"

const struct ctfb_vesa_modes vesa_modes[VESA_MODES_COUNT] = {
	{0x301, RES_MODE_640x480, 8},
	{0x310, RES_MODE_640x480, 15},
	{0x311, RES_MODE_640x480, 16},
	{0x312, RES_MODE_640x480, 24},
	{0x303, RES_MODE_800x600, 8},
	{0x313, RES_MODE_800x600, 15},
	{0x314, RES_MODE_800x600, 16},
	{0x315, RES_MODE_800x600, 24},
	{0x305, RES_MODE_1024x768, 8},
	{0x316, RES_MODE_1024x768, 15},
	{0x317, RES_MODE_1024x768, 16},
	{0x318, RES_MODE_1024x768, 24},
	{0x161, RES_MODE_1152x864, 8},
	{0x162, RES_MODE_1152x864, 15},
	{0x163, RES_MODE_1152x864, 16},
	{0x307, RES_MODE_1280x1024, 8},
	{0x319, RES_MODE_1280x1024, 15},
	{0x31A, RES_MODE_1280x1024, 16},
	{0x31B, RES_MODE_1280x1024, 24},
};
const struct ctfb_res_modes res_mode_init[RES_MODES_COUNT] = {
	/* x	 y pixclk   le	ri  up	lo   hs vs  s  vmode */
	{640, 480, 39721, 40, 24, 32, 11, 96, 2, 0, FB_VMODE_NONINTERLACED},
	{800, 600, 27778, 64, 24, 22, 1, 72, 2, 0, FB_VMODE_NONINTERLACED},
	{1024, 768, 15384, 168, 8, 29, 3, 144, 4, 0, FB_VMODE_NONINTERLACED},
	{960, 720, 13100, 160, 40, 32, 8, 80, 4, 0, FB_VMODE_NONINTERLACED},
	{1152, 864, 12004, 200, 64, 32, 16, 80, 4, 0, FB_VMODE_NONINTERLACED},
	{1280, 1024, 9090, 200, 48, 26, 1, 184, 3, 0, FB_VMODE_NONINTERLACED},
};

static int
video_get_param_len (char *start, char sep)
{
	int i = 0;
	while ((*start != 0) && (*start != sep)) {
		start++;
		i++;
	}
	return i;
}

static int
video_search_param (char *start, char *param)
{
	int len, totallen, i;
	char *p = start;
	len = strlen (param);
	totallen = len + strlen (start);
	for (i = 0; i < totallen; i++) {
		if (strncmp (p++, param, len) == 0)
			return (i);
	}
	return -1;
}


#define GET_OPTION(name,var)				\
	if(strncmp(p,name,strlen(name))==0) {		\
		val_s=p+strlen(name);			\
		var=simple_strtoul(val_s, NULL, 10);	\
	}

int video_get_params (struct ctfb_res_modes *pPar, char *penv)
{
	char *p, *s, *val_s;
	int i = 0, t;
	int bpp;
	int mode;
	/* first search for the environment containing the real param string */
	s = penv;
	if ((p = getenv (s)) != NULL) {
		s = p;
	}
	/* in case of the bootargs line, we have to start
	 * after "video=ctfb:"
	 */
	i = video_search_param (s, "video=ctfb:");
	if (i >= 0) {
		s += i;
		s += strlen ("video=ctfb:");
	}
	/* search for mode as a default value */
	p = s;
	t = 0;
	mode = 0;		/* default */
	while ((i = video_get_param_len (p, ',')) != 0) {
		GET_OPTION ("mode:", mode)
			p += i;
		if (*p != 0)
			p++;	/* skip ',' */
	}
	if (mode >= RES_MODES_COUNT)
		mode = 0;
	*pPar = res_mode_init[mode];	/* copy default values */
	bpp = 24 - ((mode % 3) * 8);
	p = s;			/* restart */
	while ((i = video_get_param_len (p, ',')) != 0) {
		GET_OPTION ("x:", pPar->xres)
			GET_OPTION ("y:", pPar->yres)
			GET_OPTION ("le:", pPar->left_margin)
			GET_OPTION ("ri:", pPar->right_margin)
			GET_OPTION ("up:", pPar->upper_margin)
			GET_OPTION ("lo:", pPar->lower_margin)
			GET_OPTION ("hs:", pPar->hsync_len)
			GET_OPTION ("vs:", pPar->vsync_len)
			GET_OPTION ("sync:", pPar->sync)
			GET_OPTION ("vmode:", pPar->vmode)
			GET_OPTION ("pclk:", pPar->pixclock)
			GET_OPTION ("depth:", bpp)
			p += i;
		if (*p != 0)
			p++;	/* skip ',' */
	}
	return bpp;
}



struct syscntl_regs {
	u32 scctrl;
	u32 scsysstat;
	u32 scimctrl;
	u32 scimsysstat;
	u32 scxtalctrl;
	u32 scpllctrl;
	u32 scpllfctrl;
	u32 scperctrl0;
	u32 scperctrl1;
	u32 scperen;
	u32 scperdis;
	const u32 scperclken;
	const u32 scperstat;
};

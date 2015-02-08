

#ifndef	_IDE_H
#define _IDE_H

#define	IDE_BUS(dev)	(dev >> 1)

#define	ATA_CURR_BASE(dev)	(CONFIG_SYS_ATA_BASE_ADDR+ide_bus_offset[IDE_BUS(dev)])

#ifdef CONFIG_IDE_LED

#define	LED_PORT	((uchar *)(PER8_BASE + 0x3000))
#define LED_IDE1	0x01
#define LED_IDE2	0x02
#define	DEVICE_LED(d)	((d & 2) | ((d & 2) == 0)) /* depends on bit positions! */

#endif /* CONFIG_IDE_LED */

#ifdef CONFIG_SYS_64BIT_LBA
typedef uint64_t lbaint_t;
#else
typedef ulong lbaint_t;
#endif


void ide_init(void);
ulong ide_read(int device, lbaint_t blknr, ulong blkcnt, void *buffer);
ulong ide_write(int device, lbaint_t blknr, ulong blkcnt, void *buffer);

#if defined(CONFIG_OF_IDE_FIXUP)
int ide_device_present(int dev);
#endif
#endif /* _IDE_H */

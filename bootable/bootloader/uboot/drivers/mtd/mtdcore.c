

#include <linux/mtd/mtd.h>
#include <linux/mtd/compat.h>
#include <ubi_uboot.h>

struct mtd_info *mtd_table[MAX_MTD_DEVICES];

int add_mtd_device(struct mtd_info *mtd)
{
	int i;

	BUG_ON(mtd->writesize == 0);

	for (i = 0; i < MAX_MTD_DEVICES; i++)
		if (!mtd_table[i]) {
			mtd_table[i] = mtd;
			mtd->index = i;
			mtd->usecount = 0;

			/* No need to get a refcount on the module containing
			   the notifier, since we hold the mtd_table_mutex */

			/* We _know_ we aren't being removed, because
			   our caller is still holding us here. So none
			   of this try_ nonsense, and no bitching about it
			   either. :) */
			return 0;
		}

	return 1;
}

int del_mtd_device(struct mtd_info *mtd)
{
	int ret;

	if (mtd_table[mtd->index] != mtd) {
		ret = -ENODEV;
	} else if (mtd->usecount) {
		printk(KERN_NOTICE "Removing MTD device #%d (%s)"
				" with use count %d\n",
				mtd->index, mtd->name, mtd->usecount);
		ret = -EBUSY;
	} else {
		/* No need to get a refcount on the module containing
		 * the notifier, since we hold the mtd_table_mutex */
		mtd_table[mtd->index] = NULL;

		ret = 0;
	}

	return ret;
}

struct mtd_info *get_mtd_device(struct mtd_info *mtd, int num)
{
	struct mtd_info *ret = NULL;
	int i, err = -ENODEV;

	if (num == -1) {
		for (i = 0; i < MAX_MTD_DEVICES; i++)
			if (mtd_table[i] == mtd)
				ret = mtd_table[i];
	} else if (num < MAX_MTD_DEVICES) {
		ret = mtd_table[num];
		if (mtd && mtd != ret)
			ret = NULL;
	}

	if (!ret)
		goto out_unlock;

	ret->usecount++;
	return ret;

out_unlock:
	return ERR_PTR(err);
}

struct mtd_info *get_mtd_device_nm(const char *name)
{
	int i, err = -ENODEV;
	struct mtd_info *mtd = NULL;

	for (i = 0; i < MAX_MTD_DEVICES; i++) {
		if (mtd_table[i] && !strcmp(name, mtd_table[i]->name)) {
			mtd = mtd_table[i];
			break;
		}
	}

	if (!mtd)
		goto out_unlock;

	mtd->usecount++;
	return mtd;

out_unlock:
	return ERR_PTR(err);
}

void put_mtd_device(struct mtd_info *mtd)
{
	int c;

	c = --mtd->usecount;
	BUG_ON(c < 0);
}

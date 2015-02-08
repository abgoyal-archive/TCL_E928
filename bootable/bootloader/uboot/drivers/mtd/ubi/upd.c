


#ifdef UBI_LINUX
#include <linux/err.h>
#include <asm/uaccess.h>
#include <asm/div64.h>
#endif

#include <ubi_uboot.h>
#include "ubi.h"

static int set_update_marker(struct ubi_device *ubi, struct ubi_volume *vol)
{
	int err;
	struct ubi_vtbl_record vtbl_rec;

	dbg_msg("set update marker for volume %d", vol->vol_id);

	if (vol->upd_marker) {
		ubi_assert(ubi->vtbl[vol->vol_id].upd_marker);
		dbg_msg("already set");
		return 0;
	}

	memcpy(&vtbl_rec, &ubi->vtbl[vol->vol_id],
	       sizeof(struct ubi_vtbl_record));
	vtbl_rec.upd_marker = 1;

	mutex_lock(&ubi->volumes_mutex);
	err = ubi_change_vtbl_record(ubi, vol->vol_id, &vtbl_rec);
	mutex_unlock(&ubi->volumes_mutex);
	vol->upd_marker = 1;
	return err;
}

static int clear_update_marker(struct ubi_device *ubi, struct ubi_volume *vol,
			       long long bytes)
{
	int err;
	uint64_t tmp;
	struct ubi_vtbl_record vtbl_rec;

	dbg_msg("clear update marker for volume %d", vol->vol_id);

	memcpy(&vtbl_rec, &ubi->vtbl[vol->vol_id],
	       sizeof(struct ubi_vtbl_record));
	ubi_assert(vol->upd_marker && vtbl_rec.upd_marker);
	vtbl_rec.upd_marker = 0;

	if (vol->vol_type == UBI_STATIC_VOLUME) {
		vol->corrupted = 0;
		vol->used_bytes = tmp = bytes;
		vol->last_eb_bytes = do_div(tmp, vol->usable_leb_size);
		vol->used_ebs = tmp;
		if (vol->last_eb_bytes)
			vol->used_ebs += 1;
		else
			vol->last_eb_bytes = vol->usable_leb_size;
	}

	mutex_lock(&ubi->volumes_mutex);
	err = ubi_change_vtbl_record(ubi, vol->vol_id, &vtbl_rec);
	mutex_unlock(&ubi->volumes_mutex);
	vol->upd_marker = 0;
	return err;
}

int ubi_start_update(struct ubi_device *ubi, struct ubi_volume *vol,
		     long long bytes)
{
	int i, err;
	uint64_t tmp;

	dbg_msg("start update of volume %d, %llu bytes", vol->vol_id, bytes);
	ubi_assert(!vol->updating && !vol->changing_leb);
	vol->updating = 1;

	err = set_update_marker(ubi, vol);
	if (err)
		return err;

	/* Before updating - wipe out the volume */
	for (i = 0; i < vol->reserved_pebs; i++) {
		err = ubi_eba_unmap_leb(ubi, vol, i);
		if (err)
			return err;
	}

	if (bytes == 0) {
		err = clear_update_marker(ubi, vol, 0);
		if (err)
			return err;
		err = ubi_wl_flush(ubi);
		if (!err)
			vol->updating = 0;
	}

	vol->upd_buf = vmalloc(ubi->leb_size);
	if (!vol->upd_buf)
		return -ENOMEM;

	tmp = bytes;
	vol->upd_ebs = !!do_div(tmp, vol->usable_leb_size);
	vol->upd_ebs += tmp;
	vol->upd_bytes = bytes;
	vol->upd_received = 0;
	return 0;
}

int ubi_start_leb_change(struct ubi_device *ubi, struct ubi_volume *vol,
			 const struct ubi_leb_change_req *req)
{
	ubi_assert(!vol->updating && !vol->changing_leb);

	dbg_msg("start changing LEB %d:%d, %u bytes",
		vol->vol_id, req->lnum, req->bytes);
	if (req->bytes == 0)
		return ubi_eba_atomic_leb_change(ubi, vol, req->lnum, NULL, 0,
						 req->dtype);

	vol->upd_bytes = req->bytes;
	vol->upd_received = 0;
	vol->changing_leb = 1;
	vol->ch_lnum = req->lnum;
	vol->ch_dtype = req->dtype;

	vol->upd_buf = vmalloc(req->bytes);
	if (!vol->upd_buf)
		return -ENOMEM;

	return 0;
}

static int write_leb(struct ubi_device *ubi, struct ubi_volume *vol, int lnum,
		     void *buf, int len, int used_ebs)
{
	int err;

	if (vol->vol_type == UBI_DYNAMIC_VOLUME) {
		int l = ALIGN(len, ubi->min_io_size);

		memset(buf + len, 0xFF, l - len);
		len = ubi_calc_data_len(ubi, buf, l);
		if (len == 0) {
			dbg_msg("all %d bytes contain 0xFF - skip", len);
			return 0;
		}

		err = ubi_eba_write_leb(ubi, vol, lnum, buf, 0, len, UBI_UNKNOWN);
	} else {
		/*
		 * When writing static volume, and this is the last logical
		 * eraseblock, the length (@len) does not have to be aligned to
		 * the minimal flash I/O unit. The 'ubi_eba_write_leb_st()'
		 * function accepts exact (unaligned) length and stores it in
		 * the VID header. And it takes care of proper alignment by
		 * padding the buffer. Here we just make sure the padding will
		 * contain zeros, not random trash.
		 */
		memset(buf + len, 0, vol->usable_leb_size - len);
		err = ubi_eba_write_leb_st(ubi, vol, lnum, buf, len,
					   UBI_UNKNOWN, used_ebs);
	}

	return err;
}

int ubi_more_update_data(struct ubi_device *ubi, struct ubi_volume *vol,
			 const void __user *buf, int count)
{
	uint64_t tmp;
	int lnum, offs, err = 0, len, to_write = count;

	dbg_msg("write %d of %lld bytes, %lld already passed",
		count, vol->upd_bytes, vol->upd_received);

	if (ubi->ro_mode)
		return -EROFS;

	tmp = vol->upd_received;
	offs = do_div(tmp, vol->usable_leb_size);
	lnum = tmp;

	if (vol->upd_received + count > vol->upd_bytes)
		to_write = count = vol->upd_bytes - vol->upd_received;

	/*
	 * When updating volumes, we accumulate whole logical eraseblock of
	 * data and write it at once.
	 */
	if (offs != 0) {
		/*
		 * This is a write to the middle of the logical eraseblock. We
		 * copy the data to our update buffer and wait for more data or
		 * flush it if the whole eraseblock is written or the update
		 * is finished.
		 */

		len = vol->usable_leb_size - offs;
		if (len > count)
			len = count;

		err = copy_from_user(vol->upd_buf + offs, buf, len);
		if (err)
			return -EFAULT;

		if (offs + len == vol->usable_leb_size ||
		    vol->upd_received + len == vol->upd_bytes) {
			int flush_len = offs + len;

			/*
			 * OK, we gathered either the whole eraseblock or this
			 * is the last chunk, it's time to flush the buffer.
			 */
			ubi_assert(flush_len <= vol->usable_leb_size);
			err = write_leb(ubi, vol, lnum, vol->upd_buf, flush_len,
					vol->upd_ebs);
			if (err)
				return err;
		}

		vol->upd_received += len;
		count -= len;
		buf += len;
		lnum += 1;
	}

	/*
	 * If we've got more to write, let's continue. At this point we know we
	 * are starting from the beginning of an eraseblock.
	 */
	while (count) {
		if (count > vol->usable_leb_size)
			len = vol->usable_leb_size;
		else
			len = count;

		err = copy_from_user(vol->upd_buf, buf, len);
		if (err)
			return -EFAULT;

		if (len == vol->usable_leb_size ||
		    vol->upd_received + len == vol->upd_bytes) {
			err = write_leb(ubi, vol, lnum, vol->upd_buf,
					len, vol->upd_ebs);
			if (err)
				break;
		}

		vol->upd_received += len;
		count -= len;
		lnum += 1;
		buf += len;
	}

	ubi_assert(vol->upd_received <= vol->upd_bytes);
	if (vol->upd_received == vol->upd_bytes) {
		/* The update is finished, clear the update marker */
		err = clear_update_marker(ubi, vol, vol->upd_bytes);
		if (err)
			return err;
		err = ubi_wl_flush(ubi);
		if (err == 0) {
			vol->updating = 0;
			err = to_write;
			vfree(vol->upd_buf);
		}
	}

	return err;
}

int ubi_more_leb_change_data(struct ubi_device *ubi, struct ubi_volume *vol,
			     const void __user *buf, int count)
{
	int err;

	dbg_msg("write %d of %lld bytes, %lld already passed",
		count, vol->upd_bytes, vol->upd_received);

	if (ubi->ro_mode)
		return -EROFS;

	if (vol->upd_received + count > vol->upd_bytes)
		count = vol->upd_bytes - vol->upd_received;

	err = copy_from_user(vol->upd_buf + vol->upd_received, buf, count);
	if (err)
		return -EFAULT;

	vol->upd_received += count;

	if (vol->upd_received == vol->upd_bytes) {
		int len = ALIGN((int)vol->upd_bytes, ubi->min_io_size);

		memset(vol->upd_buf + vol->upd_bytes, 0xFF, len - vol->upd_bytes);
		len = ubi_calc_data_len(ubi, vol->upd_buf, len);
		err = ubi_eba_atomic_leb_change(ubi, vol, vol->ch_lnum,
						vol->upd_buf, len, UBI_UNKNOWN);
		if (err)
			return err;
	}

	ubi_assert(vol->upd_received <= vol->upd_bytes);
	if (vol->upd_received == vol->upd_bytes) {
		vol->changing_leb = 0;
		err = count;
		vfree(vol->upd_buf);
	}

	return err;
}




#ifdef UBI_LINUX
#include <linux/slab.h>
#include <linux/crc32.h>
#include <linux/freezer.h>
#include <linux/kthread.h>
#endif

#include <ubi_uboot.h>
#include "ubi.h"

/* Number of physical eraseblocks reserved for wear-leveling purposes */
#define WL_RESERVED_PEBS 1

#define ST_PROTECTION 16
#define U_PROTECTION  10
#define LT_PROTECTION 4

#define UBI_WL_THRESHOLD CONFIG_MTD_UBI_WL_THRESHOLD

#define WL_FREE_MAX_DIFF (2*UBI_WL_THRESHOLD)

#define WL_MAX_FAILURES 32

struct ubi_wl_prot_entry {
	struct rb_node rb_pnum;
	struct rb_node rb_aec;
	unsigned long long abs_ec;
	struct ubi_wl_entry *e;
};

struct ubi_work {
	struct list_head list;
	int (*func)(struct ubi_device *ubi, struct ubi_work *wrk, int cancel);
	/* The below fields are only relevant to erasure works */
	struct ubi_wl_entry *e;
	int torture;
};

#ifdef CONFIG_MTD_UBI_DEBUG_PARANOID
static int paranoid_check_ec(struct ubi_device *ubi, int pnum, int ec);
static int paranoid_check_in_wl_tree(struct ubi_wl_entry *e,
				     struct rb_root *root);
#else
#define paranoid_check_ec(ubi, pnum, ec) 0
#define paranoid_check_in_wl_tree(e, root)
#endif

static void wl_tree_add(struct ubi_wl_entry *e, struct rb_root *root)
{
	struct rb_node **p, *parent = NULL;

	p = &root->rb_node;
	while (*p) {
		struct ubi_wl_entry *e1;

		parent = *p;
		e1 = rb_entry(parent, struct ubi_wl_entry, rb);

		if (e->ec < e1->ec)
			p = &(*p)->rb_left;
		else if (e->ec > e1->ec)
			p = &(*p)->rb_right;
		else {
			ubi_assert(e->pnum != e1->pnum);
			if (e->pnum < e1->pnum)
				p = &(*p)->rb_left;
			else
				p = &(*p)->rb_right;
		}
	}

	rb_link_node(&e->rb, parent, p);
	rb_insert_color(&e->rb, root);
}

static int do_work(struct ubi_device *ubi)
{
	int err;
	struct ubi_work *wrk;

	cond_resched();

	/*
	 * @ubi->work_sem is used to synchronize with the workers. Workers take
	 * it in read mode, so many of them may be doing works at a time. But
	 * the queue flush code has to be sure the whole queue of works is
	 * done, and it takes the mutex in write mode.
	 */
	down_read(&ubi->work_sem);
	spin_lock(&ubi->wl_lock);
	if (list_empty(&ubi->works)) {
		spin_unlock(&ubi->wl_lock);
		up_read(&ubi->work_sem);
		return 0;
	}

	wrk = list_entry(ubi->works.next, struct ubi_work, list);
	list_del(&wrk->list);
	ubi->works_count -= 1;
	ubi_assert(ubi->works_count >= 0);
	spin_unlock(&ubi->wl_lock);

	/*
	 * Call the worker function. Do not touch the work structure
	 * after this call as it will have been freed or reused by that
	 * time by the worker function.
	 */
	err = wrk->func(ubi, wrk, 0);
	if (err)
		ubi_err("work failed with error code %d", err);
	up_read(&ubi->work_sem);

	return err;
}

static int produce_free_peb(struct ubi_device *ubi)
{
	int err;

	spin_lock(&ubi->wl_lock);
	while (!ubi->free.rb_node) {
		spin_unlock(&ubi->wl_lock);

		dbg_wl("do one work synchronously");
		err = do_work(ubi);
		if (err)
			return err;

		spin_lock(&ubi->wl_lock);
	}
	spin_unlock(&ubi->wl_lock);

	return 0;
}

static int in_wl_tree(struct ubi_wl_entry *e, struct rb_root *root)
{
	struct rb_node *p;

	p = root->rb_node;
	while (p) {
		struct ubi_wl_entry *e1;

		e1 = rb_entry(p, struct ubi_wl_entry, rb);

		if (e->pnum == e1->pnum) {
			ubi_assert(e == e1);
			return 1;
		}

		if (e->ec < e1->ec)
			p = p->rb_left;
		else if (e->ec > e1->ec)
			p = p->rb_right;
		else {
			ubi_assert(e->pnum != e1->pnum);
			if (e->pnum < e1->pnum)
				p = p->rb_left;
			else
				p = p->rb_right;
		}
	}

	return 0;
}

static void prot_tree_add(struct ubi_device *ubi, struct ubi_wl_entry *e,
			  struct ubi_wl_prot_entry *pe, int abs_ec)
{
	struct rb_node **p, *parent = NULL;
	struct ubi_wl_prot_entry *pe1;

	pe->e = e;
	pe->abs_ec = ubi->abs_ec + abs_ec;

	p = &ubi->prot.pnum.rb_node;
	while (*p) {
		parent = *p;
		pe1 = rb_entry(parent, struct ubi_wl_prot_entry, rb_pnum);

		if (e->pnum < pe1->e->pnum)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}
	rb_link_node(&pe->rb_pnum, parent, p);
	rb_insert_color(&pe->rb_pnum, &ubi->prot.pnum);

	p = &ubi->prot.aec.rb_node;
	parent = NULL;
	while (*p) {
		parent = *p;
		pe1 = rb_entry(parent, struct ubi_wl_prot_entry, rb_aec);

		if (pe->abs_ec < pe1->abs_ec)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}
	rb_link_node(&pe->rb_aec, parent, p);
	rb_insert_color(&pe->rb_aec, &ubi->prot.aec);
}

static struct ubi_wl_entry *find_wl_entry(struct rb_root *root, int max)
{
	struct rb_node *p;
	struct ubi_wl_entry *e;

	e = rb_entry(rb_first(root), struct ubi_wl_entry, rb);
	max += e->ec;

	p = root->rb_node;
	while (p) {
		struct ubi_wl_entry *e1;

		e1 = rb_entry(p, struct ubi_wl_entry, rb);
		if (e1->ec >= max)
			p = p->rb_left;
		else {
			p = p->rb_right;
			e = e1;
		}
	}

	return e;
}

int ubi_wl_get_peb(struct ubi_device *ubi, int dtype)
{
	int err, protect, medium_ec;
	struct ubi_wl_entry *e, *first, *last;
	struct ubi_wl_prot_entry *pe;

	ubi_assert(dtype == UBI_LONGTERM || dtype == UBI_SHORTTERM ||
		   dtype == UBI_UNKNOWN);

	pe = kmalloc(sizeof(struct ubi_wl_prot_entry), GFP_NOFS);
	if (!pe)
		return -ENOMEM;

retry:
	spin_lock(&ubi->wl_lock);
	if (!ubi->free.rb_node) {
		if (ubi->works_count == 0) {
			ubi_assert(list_empty(&ubi->works));
			ubi_err("no free eraseblocks");
			spin_unlock(&ubi->wl_lock);
			kfree(pe);
			return -ENOSPC;
		}
		spin_unlock(&ubi->wl_lock);

		err = produce_free_peb(ubi);
		if (err < 0) {
			kfree(pe);
			return err;
		}
		goto retry;
	}

	switch (dtype) {
		case UBI_LONGTERM:
			/*
			 * For long term data we pick a physical eraseblock
			 * with high erase counter. But the highest erase
			 * counter we can pick is bounded by the the lowest
			 * erase counter plus %WL_FREE_MAX_DIFF.
			 */
			e = find_wl_entry(&ubi->free, WL_FREE_MAX_DIFF);
			protect = LT_PROTECTION;
			break;
		case UBI_UNKNOWN:
			/*
			 * For unknown data we pick a physical eraseblock with
			 * medium erase counter. But we by no means can pick a
			 * physical eraseblock with erase counter greater or
			 * equivalent than the lowest erase counter plus
			 * %WL_FREE_MAX_DIFF.
			 */
			first = rb_entry(rb_first(&ubi->free),
					 struct ubi_wl_entry, rb);
			last = rb_entry(rb_last(&ubi->free),
					struct ubi_wl_entry, rb);

			if (last->ec - first->ec < WL_FREE_MAX_DIFF)
				e = rb_entry(ubi->free.rb_node,
						struct ubi_wl_entry, rb);
			else {
				medium_ec = (first->ec + WL_FREE_MAX_DIFF)/2;
				e = find_wl_entry(&ubi->free, medium_ec);
			}
			protect = U_PROTECTION;
			break;
		case UBI_SHORTTERM:
			/*
			 * For short term data we pick a physical eraseblock
			 * with the lowest erase counter as we expect it will
			 * be erased soon.
			 */
			e = rb_entry(rb_first(&ubi->free),
				     struct ubi_wl_entry, rb);
			protect = ST_PROTECTION;
			break;
		default:
			protect = 0;
			e = NULL;
			BUG();
	}

	/*
	 * Move the physical eraseblock to the protection trees where it will
	 * be protected from being moved for some time.
	 */
	paranoid_check_in_wl_tree(e, &ubi->free);
	rb_erase(&e->rb, &ubi->free);
	prot_tree_add(ubi, e, pe, protect);

	dbg_wl("PEB %d EC %d, protection %d", e->pnum, e->ec, protect);
	spin_unlock(&ubi->wl_lock);

	return e->pnum;
}

static int prot_tree_del(struct ubi_device *ubi, int pnum)
{
	struct rb_node *p;
	struct ubi_wl_prot_entry *pe = NULL;

	p = ubi->prot.pnum.rb_node;
	while (p) {

		pe = rb_entry(p, struct ubi_wl_prot_entry, rb_pnum);

		if (pnum == pe->e->pnum)
			goto found;

		if (pnum < pe->e->pnum)
			p = p->rb_left;
		else
			p = p->rb_right;
	}

	return -ENODEV;

found:
	ubi_assert(pe->e->pnum == pnum);
	rb_erase(&pe->rb_aec, &ubi->prot.aec);
	rb_erase(&pe->rb_pnum, &ubi->prot.pnum);
	kfree(pe);
	return 0;
}

static int sync_erase(struct ubi_device *ubi, struct ubi_wl_entry *e, int torture)
{
	int err;
	struct ubi_ec_hdr *ec_hdr;
	unsigned long long ec = e->ec;

	dbg_wl("erase PEB %d, old EC %llu", e->pnum, ec);

	err = paranoid_check_ec(ubi, e->pnum, e->ec);
	if (err > 0)
		return -EINVAL;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_NOFS);
	if (!ec_hdr)
		return -ENOMEM;

	err = ubi_io_sync_erase(ubi, e->pnum, torture);
	if (err < 0)
		goto out_free;

	ec += err;
	if (ec > UBI_MAX_ERASECOUNTER) {
		/*
		 * Erase counter overflow. Upgrade UBI and use 64-bit
		 * erase counters internally.
		 */
		ubi_err("erase counter overflow at PEB %d, EC %llu",
			e->pnum, ec);
		err = -EINVAL;
		goto out_free;
	}

	dbg_wl("erased PEB %d, new EC %llu", e->pnum, ec);

	ec_hdr->ec = cpu_to_be64(ec);

	err = ubi_io_write_ec_hdr(ubi, e->pnum, ec_hdr);
	if (err)
		goto out_free;

	e->ec = ec;
	spin_lock(&ubi->wl_lock);
	if (e->ec > ubi->max_ec)
		ubi->max_ec = e->ec;
	spin_unlock(&ubi->wl_lock);

out_free:
	kfree(ec_hdr);
	return err;
}

static void check_protection_over(struct ubi_device *ubi)
{
	struct ubi_wl_prot_entry *pe;

	/*
	 * There may be several protected physical eraseblock to remove,
	 * process them all.
	 */
	while (1) {
		spin_lock(&ubi->wl_lock);
		if (!ubi->prot.aec.rb_node) {
			spin_unlock(&ubi->wl_lock);
			break;
		}

		pe = rb_entry(rb_first(&ubi->prot.aec),
			      struct ubi_wl_prot_entry, rb_aec);

		if (pe->abs_ec > ubi->abs_ec) {
			spin_unlock(&ubi->wl_lock);
			break;
		}

		dbg_wl("PEB %d protection over, abs_ec %llu, PEB abs_ec %llu",
		       pe->e->pnum, ubi->abs_ec, pe->abs_ec);
		rb_erase(&pe->rb_aec, &ubi->prot.aec);
		rb_erase(&pe->rb_pnum, &ubi->prot.pnum);
		wl_tree_add(pe->e, &ubi->used);
		spin_unlock(&ubi->wl_lock);

		kfree(pe);
		cond_resched();
	}
}

static void schedule_ubi_work(struct ubi_device *ubi, struct ubi_work *wrk)
{
	spin_lock(&ubi->wl_lock);
	list_add_tail(&wrk->list, &ubi->works);
	ubi_assert(ubi->works_count >= 0);
	ubi->works_count += 1;

	/*
	 * U-Boot special: We have no bgt_thread in U-Boot!
	 * So just call do_work() here directly.
	 */
	do_work(ubi);

	spin_unlock(&ubi->wl_lock);
}

static int erase_worker(struct ubi_device *ubi, struct ubi_work *wl_wrk,
			int cancel);

static int schedule_erase(struct ubi_device *ubi, struct ubi_wl_entry *e,
			  int torture)
{
	struct ubi_work *wl_wrk;

	dbg_wl("schedule erasure of PEB %d, EC %d, torture %d",
	       e->pnum, e->ec, torture);

	wl_wrk = kmalloc(sizeof(struct ubi_work), GFP_NOFS);
	if (!wl_wrk)
		return -ENOMEM;

	wl_wrk->func = &erase_worker;
	wl_wrk->e = e;
	wl_wrk->torture = torture;

	schedule_ubi_work(ubi, wl_wrk);
	return 0;
}

static int wear_leveling_worker(struct ubi_device *ubi, struct ubi_work *wrk,
				int cancel)
{
	int err, put = 0, scrubbing = 0, protect = 0;
	struct ubi_wl_prot_entry *uninitialized_var(pe);
	struct ubi_wl_entry *e1, *e2;
	struct ubi_vid_hdr *vid_hdr;

	kfree(wrk);

	if (cancel)
		return 0;

	vid_hdr = ubi_zalloc_vid_hdr(ubi, GFP_NOFS);
	if (!vid_hdr)
		return -ENOMEM;

	mutex_lock(&ubi->move_mutex);
	spin_lock(&ubi->wl_lock);
	ubi_assert(!ubi->move_from && !ubi->move_to);
	ubi_assert(!ubi->move_to_put);

	if (!ubi->free.rb_node ||
	    (!ubi->used.rb_node && !ubi->scrub.rb_node)) {
		/*
		 * No free physical eraseblocks? Well, they must be waiting in
		 * the queue to be erased. Cancel movement - it will be
		 * triggered again when a free physical eraseblock appears.
		 *
		 * No used physical eraseblocks? They must be temporarily
		 * protected from being moved. They will be moved to the
		 * @ubi->used tree later and the wear-leveling will be
		 * triggered again.
		 */
		dbg_wl("cancel WL, a list is empty: free %d, used %d",
		       !ubi->free.rb_node, !ubi->used.rb_node);
		goto out_cancel;
	}

	if (!ubi->scrub.rb_node) {
		/*
		 * Now pick the least worn-out used physical eraseblock and a
		 * highly worn-out free physical eraseblock. If the erase
		 * counters differ much enough, start wear-leveling.
		 */
		e1 = rb_entry(rb_first(&ubi->used), struct ubi_wl_entry, rb);
		e2 = find_wl_entry(&ubi->free, WL_FREE_MAX_DIFF);

		if (!(e2->ec - e1->ec >= UBI_WL_THRESHOLD)) {
			dbg_wl("no WL needed: min used EC %d, max free EC %d",
			       e1->ec, e2->ec);
			goto out_cancel;
		}
		paranoid_check_in_wl_tree(e1, &ubi->used);
		rb_erase(&e1->rb, &ubi->used);
		dbg_wl("move PEB %d EC %d to PEB %d EC %d",
		       e1->pnum, e1->ec, e2->pnum, e2->ec);
	} else {
		/* Perform scrubbing */
		scrubbing = 1;
		e1 = rb_entry(rb_first(&ubi->scrub), struct ubi_wl_entry, rb);
		e2 = find_wl_entry(&ubi->free, WL_FREE_MAX_DIFF);
		paranoid_check_in_wl_tree(e1, &ubi->scrub);
		rb_erase(&e1->rb, &ubi->scrub);
		dbg_wl("scrub PEB %d to PEB %d", e1->pnum, e2->pnum);
	}

	paranoid_check_in_wl_tree(e2, &ubi->free);
	rb_erase(&e2->rb, &ubi->free);
	ubi->move_from = e1;
	ubi->move_to = e2;
	spin_unlock(&ubi->wl_lock);

	/*
	 * Now we are going to copy physical eraseblock @e1->pnum to @e2->pnum.
	 * We so far do not know which logical eraseblock our physical
	 * eraseblock (@e1) belongs to. We have to read the volume identifier
	 * header first.
	 *
	 * Note, we are protected from this PEB being unmapped and erased. The
	 * 'ubi_wl_put_peb()' would wait for moving to be finished if the PEB
	 * which is being moved was unmapped.
	 */

	err = ubi_io_read_vid_hdr(ubi, e1->pnum, vid_hdr, 0);
	if (err && err != UBI_IO_BITFLIPS) {
		if (err == UBI_IO_PEB_FREE) {
			/*
			 * We are trying to move PEB without a VID header. UBI
			 * always write VID headers shortly after the PEB was
			 * given, so we have a situation when it did not have
			 * chance to write it down because it was preempted.
			 * Just re-schedule the work, so that next time it will
			 * likely have the VID header in place.
			 */
			dbg_wl("PEB %d has no VID header", e1->pnum);
			goto out_not_moved;
		}

		ubi_err("error %d while reading VID header from PEB %d",
			err, e1->pnum);
		if (err > 0)
			err = -EIO;
		goto out_error;
	}

	err = ubi_eba_copy_leb(ubi, e1->pnum, e2->pnum, vid_hdr);
	if (err) {

		if (err < 0)
			goto out_error;
		if (err == 1)
			goto out_not_moved;

		/*
		 * For some reason the LEB was not moved - it might be because
		 * the volume is being deleted. We should prevent this PEB from
		 * being selected for wear-levelling movement for some "time",
		 * so put it to the protection tree.
		 */

		dbg_wl("cancelled moving PEB %d", e1->pnum);
		pe = kmalloc(sizeof(struct ubi_wl_prot_entry), GFP_NOFS);
		if (!pe) {
			err = -ENOMEM;
			goto out_error;
		}

		protect = 1;
	}

	ubi_free_vid_hdr(ubi, vid_hdr);
	spin_lock(&ubi->wl_lock);
	if (protect)
		prot_tree_add(ubi, e1, pe, protect);
	if (!ubi->move_to_put)
		wl_tree_add(e2, &ubi->used);
	else
		put = 1;
	ubi->move_from = ubi->move_to = NULL;
	ubi->move_to_put = ubi->wl_scheduled = 0;
	spin_unlock(&ubi->wl_lock);

	if (put) {
		/*
		 * Well, the target PEB was put meanwhile, schedule it for
		 * erasure.
		 */
		dbg_wl("PEB %d was put meanwhile, erase", e2->pnum);
		err = schedule_erase(ubi, e2, 0);
		if (err)
			goto out_error;
	}

	if (!protect) {
		err = schedule_erase(ubi, e1, 0);
		if (err)
			goto out_error;
	}


	dbg_wl("done");
	mutex_unlock(&ubi->move_mutex);
	return 0;

	/*
	 * For some reasons the LEB was not moved, might be an error, might be
	 * something else. @e1 was not changed, so return it back. @e2 might
	 * be changed, schedule it for erasure.
	 */
out_not_moved:
	ubi_free_vid_hdr(ubi, vid_hdr);
	spin_lock(&ubi->wl_lock);
	if (scrubbing)
		wl_tree_add(e1, &ubi->scrub);
	else
		wl_tree_add(e1, &ubi->used);
	ubi->move_from = ubi->move_to = NULL;
	ubi->move_to_put = ubi->wl_scheduled = 0;
	spin_unlock(&ubi->wl_lock);

	err = schedule_erase(ubi, e2, 0);
	if (err)
		goto out_error;

	mutex_unlock(&ubi->move_mutex);
	return 0;

out_error:
	ubi_err("error %d while moving PEB %d to PEB %d",
		err, e1->pnum, e2->pnum);

	ubi_free_vid_hdr(ubi, vid_hdr);
	spin_lock(&ubi->wl_lock);
	ubi->move_from = ubi->move_to = NULL;
	ubi->move_to_put = ubi->wl_scheduled = 0;
	spin_unlock(&ubi->wl_lock);

	kmem_cache_free(ubi_wl_entry_slab, e1);
	kmem_cache_free(ubi_wl_entry_slab, e2);
	ubi_ro_mode(ubi);

	mutex_unlock(&ubi->move_mutex);
	return err;

out_cancel:
	ubi->wl_scheduled = 0;
	spin_unlock(&ubi->wl_lock);
	mutex_unlock(&ubi->move_mutex);
	ubi_free_vid_hdr(ubi, vid_hdr);
	return 0;
}

static int ensure_wear_leveling(struct ubi_device *ubi)
{
	int err = 0;
	struct ubi_wl_entry *e1;
	struct ubi_wl_entry *e2;
	struct ubi_work *wrk;

	spin_lock(&ubi->wl_lock);
	if (ubi->wl_scheduled)
		/* Wear-leveling is already in the work queue */
		goto out_unlock;

	/*
	 * If the ubi->scrub tree is not empty, scrubbing is needed, and the
	 * the WL worker has to be scheduled anyway.
	 */
	if (!ubi->scrub.rb_node) {
		if (!ubi->used.rb_node || !ubi->free.rb_node)
			/* No physical eraseblocks - no deal */
			goto out_unlock;

		/*
		 * We schedule wear-leveling only if the difference between the
		 * lowest erase counter of used physical eraseblocks and a high
		 * erase counter of free physical eraseblocks is greater then
		 * %UBI_WL_THRESHOLD.
		 */
		e1 = rb_entry(rb_first(&ubi->used), struct ubi_wl_entry, rb);
		e2 = find_wl_entry(&ubi->free, WL_FREE_MAX_DIFF);

		if (!(e2->ec - e1->ec >= UBI_WL_THRESHOLD))
			goto out_unlock;
		dbg_wl("schedule wear-leveling");
	} else
		dbg_wl("schedule scrubbing");

	ubi->wl_scheduled = 1;
	spin_unlock(&ubi->wl_lock);

	wrk = kmalloc(sizeof(struct ubi_work), GFP_NOFS);
	if (!wrk) {
		err = -ENOMEM;
		goto out_cancel;
	}

	wrk->func = &wear_leveling_worker;
	schedule_ubi_work(ubi, wrk);
	return err;

out_cancel:
	spin_lock(&ubi->wl_lock);
	ubi->wl_scheduled = 0;
out_unlock:
	spin_unlock(&ubi->wl_lock);
	return err;
}

static int erase_worker(struct ubi_device *ubi, struct ubi_work *wl_wrk,
			int cancel)
{
	struct ubi_wl_entry *e = wl_wrk->e;
	int pnum = e->pnum, err, need;

	if (cancel) {
		dbg_wl("cancel erasure of PEB %d EC %d", pnum, e->ec);
		kfree(wl_wrk);
		kmem_cache_free(ubi_wl_entry_slab, e);
		return 0;
	}

	dbg_wl("erase PEB %d EC %d", pnum, e->ec);

	err = sync_erase(ubi, e, wl_wrk->torture);
	if (!err) {
		/* Fine, we've erased it successfully */
		kfree(wl_wrk);

		spin_lock(&ubi->wl_lock);
		ubi->abs_ec += 1;
		wl_tree_add(e, &ubi->free);
		spin_unlock(&ubi->wl_lock);

		/*
		 * One more erase operation has happened, take care about protected
		 * physical eraseblocks.
		 */
		check_protection_over(ubi);

		/* And take care about wear-leveling */
		err = ensure_wear_leveling(ubi);
		return err;
	}

	ubi_err("failed to erase PEB %d, error %d", pnum, err);
	kfree(wl_wrk);
	kmem_cache_free(ubi_wl_entry_slab, e);

	if (err == -EINTR || err == -ENOMEM || err == -EAGAIN ||
	    err == -EBUSY) {
		int err1;

		/* Re-schedule the LEB for erasure */
		err1 = schedule_erase(ubi, e, 0);
		if (err1) {
			err = err1;
			goto out_ro;
		}
		return err;
	} else if (err != -EIO) {
		/*
		 * If this is not %-EIO, we have no idea what to do. Scheduling
		 * this physical eraseblock for erasure again would cause
		 * errors again and again. Well, lets switch to RO mode.
		 */
		goto out_ro;
	}

	/* It is %-EIO, the PEB went bad */

	if (!ubi->bad_allowed) {
		ubi_err("bad physical eraseblock %d detected", pnum);
		goto out_ro;
	}

	spin_lock(&ubi->volumes_lock);
	need = ubi->beb_rsvd_level - ubi->beb_rsvd_pebs + 1;
	if (need > 0) {
		need = ubi->avail_pebs >= need ? need : ubi->avail_pebs;
		ubi->avail_pebs -= need;
		ubi->rsvd_pebs += need;
		ubi->beb_rsvd_pebs += need;
		if (need > 0)
			ubi_msg("reserve more %d PEBs", need);
	}

	if (ubi->beb_rsvd_pebs == 0) {
		spin_unlock(&ubi->volumes_lock);
		ubi_err("no reserved physical eraseblocks");
		goto out_ro;
	}

	spin_unlock(&ubi->volumes_lock);
	ubi_msg("mark PEB %d as bad", pnum);

	err = ubi_io_mark_bad(ubi, pnum);
	if (err)
		goto out_ro;

	spin_lock(&ubi->volumes_lock);
	ubi->beb_rsvd_pebs -= 1;
	ubi->bad_peb_count += 1;
	ubi->good_peb_count -= 1;
	ubi_calculate_reserved(ubi);
	if (ubi->beb_rsvd_pebs == 0)
		ubi_warn("last PEB from the reserved pool was used");
	spin_unlock(&ubi->volumes_lock);

	return err;

out_ro:
	ubi_ro_mode(ubi);
	return err;
}

int ubi_wl_put_peb(struct ubi_device *ubi, int pnum, int torture)
{
	int err;
	struct ubi_wl_entry *e;

	dbg_wl("PEB %d", pnum);
	ubi_assert(pnum >= 0);
	ubi_assert(pnum < ubi->peb_count);

retry:
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (e == ubi->move_from) {
		/*
		 * User is putting the physical eraseblock which was selected to
		 * be moved. It will be scheduled for erasure in the
		 * wear-leveling worker.
		 */
		dbg_wl("PEB %d is being moved, wait", pnum);
		spin_unlock(&ubi->wl_lock);

		/* Wait for the WL worker by taking the @ubi->move_mutex */
		mutex_lock(&ubi->move_mutex);
		mutex_unlock(&ubi->move_mutex);
		goto retry;
	} else if (e == ubi->move_to) {
		/*
		 * User is putting the physical eraseblock which was selected
		 * as the target the data is moved to. It may happen if the EBA
		 * unit already re-mapped the LEB in 'ubi_eba_copy_leb()' but
		 * the WL unit has not put the PEB to the "used" tree yet, but
		 * it is about to do this. So we just set a flag which will
		 * tell the WL worker that the PEB is not needed anymore and
		 * should be scheduled for erasure.
		 */
		dbg_wl("PEB %d is the target of data moving", pnum);
		ubi_assert(!ubi->move_to_put);
		ubi->move_to_put = 1;
		spin_unlock(&ubi->wl_lock);
		return 0;
	} else {
		if (in_wl_tree(e, &ubi->used)) {
			paranoid_check_in_wl_tree(e, &ubi->used);
			rb_erase(&e->rb, &ubi->used);
		} else if (in_wl_tree(e, &ubi->scrub)) {
			paranoid_check_in_wl_tree(e, &ubi->scrub);
			rb_erase(&e->rb, &ubi->scrub);
		} else {
			err = prot_tree_del(ubi, e->pnum);
			if (err) {
				ubi_err("PEB %d not found", pnum);
				ubi_ro_mode(ubi);
				spin_unlock(&ubi->wl_lock);
				return err;
			}
		}
	}
	spin_unlock(&ubi->wl_lock);

	err = schedule_erase(ubi, e, torture);
	if (err) {
		spin_lock(&ubi->wl_lock);
		wl_tree_add(e, &ubi->used);
		spin_unlock(&ubi->wl_lock);
	}

	return err;
}

int ubi_wl_scrub_peb(struct ubi_device *ubi, int pnum)
{
	struct ubi_wl_entry *e;

	ubi_msg("schedule PEB %d for scrubbing", pnum);

retry:
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (e == ubi->move_from || in_wl_tree(e, &ubi->scrub)) {
		spin_unlock(&ubi->wl_lock);
		return 0;
	}

	if (e == ubi->move_to) {
		/*
		 * This physical eraseblock was used to move data to. The data
		 * was moved but the PEB was not yet inserted to the proper
		 * tree. We should just wait a little and let the WL worker
		 * proceed.
		 */
		spin_unlock(&ubi->wl_lock);
		dbg_wl("the PEB %d is not in proper tree, retry", pnum);
		yield();
		goto retry;
	}

	if (in_wl_tree(e, &ubi->used)) {
		paranoid_check_in_wl_tree(e, &ubi->used);
		rb_erase(&e->rb, &ubi->used);
	} else {
		int err;

		err = prot_tree_del(ubi, e->pnum);
		if (err) {
			ubi_err("PEB %d not found", pnum);
			ubi_ro_mode(ubi);
			spin_unlock(&ubi->wl_lock);
			return err;
		}
	}

	wl_tree_add(e, &ubi->scrub);
	spin_unlock(&ubi->wl_lock);

	/*
	 * Technically scrubbing is the same as wear-leveling, so it is done
	 * by the WL worker.
	 */
	return ensure_wear_leveling(ubi);
}

int ubi_wl_flush(struct ubi_device *ubi)
{
	int err;

	/*
	 * Erase while the pending works queue is not empty, but not more then
	 * the number of currently pending works.
	 */
	dbg_wl("flush (%d pending works)", ubi->works_count);
	while (ubi->works_count) {
		err = do_work(ubi);
		if (err)
			return err;
	}

	/*
	 * Make sure all the works which have been done in parallel are
	 * finished.
	 */
	down_write(&ubi->work_sem);
	up_write(&ubi->work_sem);

	/*
	 * And in case last was the WL worker and it cancelled the LEB
	 * movement, flush again.
	 */
	while (ubi->works_count) {
		dbg_wl("flush more (%d pending works)", ubi->works_count);
		err = do_work(ubi);
		if (err)
			return err;
	}

	return 0;
}

static void tree_destroy(struct rb_root *root)
{
	struct rb_node *rb;
	struct ubi_wl_entry *e;

	rb = root->rb_node;
	while (rb) {
		if (rb->rb_left)
			rb = rb->rb_left;
		else if (rb->rb_right)
			rb = rb->rb_right;
		else {
			e = rb_entry(rb, struct ubi_wl_entry, rb);

			rb = rb_parent(rb);
			if (rb) {
				if (rb->rb_left == &e->rb)
					rb->rb_left = NULL;
				else
					rb->rb_right = NULL;
			}

			kmem_cache_free(ubi_wl_entry_slab, e);
		}
	}
}

int ubi_thread(void *u)
{
	int failures = 0;
	struct ubi_device *ubi = u;

	ubi_msg("background thread \"%s\" started, PID %d",
		ubi->bgt_name, task_pid_nr(current));

	set_freezable();
	for (;;) {
		int err;

		if (kthread_should_stop())
			break;

		if (try_to_freeze())
			continue;

		spin_lock(&ubi->wl_lock);
		if (list_empty(&ubi->works) || ubi->ro_mode ||
			       !ubi->thread_enabled) {
			set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock(&ubi->wl_lock);
			schedule();
			continue;
		}
		spin_unlock(&ubi->wl_lock);

		err = do_work(ubi);
		if (err) {
			ubi_err("%s: work failed with error code %d",
				ubi->bgt_name, err);
			if (failures++ > WL_MAX_FAILURES) {
				/*
				 * Too many failures, disable the thread and
				 * switch to read-only mode.
				 */
				ubi_msg("%s: %d consecutive failures",
					ubi->bgt_name, WL_MAX_FAILURES);
				ubi_ro_mode(ubi);
				break;
			}
		} else
			failures = 0;

		cond_resched();
	}

	dbg_wl("background thread \"%s\" is killed", ubi->bgt_name);
	return 0;
}

static void cancel_pending(struct ubi_device *ubi)
{
	while (!list_empty(&ubi->works)) {
		struct ubi_work *wrk;

		wrk = list_entry(ubi->works.next, struct ubi_work, list);
		list_del(&wrk->list);
		wrk->func(ubi, wrk, 1);
		ubi->works_count -= 1;
		ubi_assert(ubi->works_count >= 0);
	}
}

int ubi_wl_init_scan(struct ubi_device *ubi, struct ubi_scan_info *si)
{
	int err;
	struct rb_node *rb1, *rb2;
	struct ubi_scan_volume *sv;
	struct ubi_scan_leb *seb, *tmp;
	struct ubi_wl_entry *e;


	ubi->used = ubi->free = ubi->scrub = RB_ROOT;
	ubi->prot.pnum = ubi->prot.aec = RB_ROOT;
	spin_lock_init(&ubi->wl_lock);
	mutex_init(&ubi->move_mutex);
	init_rwsem(&ubi->work_sem);
	ubi->max_ec = si->max_ec;
	INIT_LIST_HEAD(&ubi->works);

	sprintf(ubi->bgt_name, UBI_BGT_NAME_PATTERN, ubi->ubi_num);

	err = -ENOMEM;
	ubi->lookuptbl = kzalloc(ubi->peb_count * sizeof(void *), GFP_KERNEL);
	if (!ubi->lookuptbl)
		return err;

	list_for_each_entry_safe(seb, tmp, &si->erase, u.list) {
		cond_resched();

		e = kmem_cache_alloc(ubi_wl_entry_slab, GFP_KERNEL);
		if (!e)
			goto out_free;

		e->pnum = seb->pnum;
		e->ec = seb->ec;
		ubi->lookuptbl[e->pnum] = e;
		if (schedule_erase(ubi, e, 0)) {
			kmem_cache_free(ubi_wl_entry_slab, e);
			goto out_free;
		}
	}

	list_for_each_entry(seb, &si->free, u.list) {
		cond_resched();

		e = kmem_cache_alloc(ubi_wl_entry_slab, GFP_KERNEL);
		if (!e)
			goto out_free;

		e->pnum = seb->pnum;
		e->ec = seb->ec;
		ubi_assert(e->ec >= 0);
		wl_tree_add(e, &ubi->free);
		ubi->lookuptbl[e->pnum] = e;
	}

	list_for_each_entry(seb, &si->corr, u.list) {
		cond_resched();

		e = kmem_cache_alloc(ubi_wl_entry_slab, GFP_KERNEL);
		if (!e)
			goto out_free;

		e->pnum = seb->pnum;
		e->ec = seb->ec;
		ubi->lookuptbl[e->pnum] = e;
		if (schedule_erase(ubi, e, 0)) {
			kmem_cache_free(ubi_wl_entry_slab, e);
			goto out_free;
		}
	}

	ubi_rb_for_each_entry(rb1, sv, &si->volumes, rb) {
		ubi_rb_for_each_entry(rb2, seb, &sv->root, u.rb) {
			cond_resched();

			e = kmem_cache_alloc(ubi_wl_entry_slab, GFP_KERNEL);
			if (!e)
				goto out_free;

			e->pnum = seb->pnum;
			e->ec = seb->ec;
			ubi->lookuptbl[e->pnum] = e;
			if (!seb->scrub) {
				dbg_wl("add PEB %d EC %d to the used tree",
				       e->pnum, e->ec);
				wl_tree_add(e, &ubi->used);
			} else {
				dbg_wl("add PEB %d EC %d to the scrub tree",
				       e->pnum, e->ec);
				wl_tree_add(e, &ubi->scrub);
			}
		}
	}

	if (ubi->avail_pebs < WL_RESERVED_PEBS) {
		ubi_err("no enough physical eraseblocks (%d, need %d)",
			ubi->avail_pebs, WL_RESERVED_PEBS);
		goto out_free;
	}
	ubi->avail_pebs -= WL_RESERVED_PEBS;
	ubi->rsvd_pebs += WL_RESERVED_PEBS;

	/* Schedule wear-leveling if needed */
	err = ensure_wear_leveling(ubi);
	if (err)
		goto out_free;

	return 0;

out_free:
	cancel_pending(ubi);
	tree_destroy(&ubi->used);
	tree_destroy(&ubi->free);
	tree_destroy(&ubi->scrub);
	kfree(ubi->lookuptbl);
	return err;
}

static void protection_trees_destroy(struct ubi_device *ubi)
{
	struct rb_node *rb;
	struct ubi_wl_prot_entry *pe;

	rb = ubi->prot.aec.rb_node;
	while (rb) {
		if (rb->rb_left)
			rb = rb->rb_left;
		else if (rb->rb_right)
			rb = rb->rb_right;
		else {
			pe = rb_entry(rb, struct ubi_wl_prot_entry, rb_aec);

			rb = rb_parent(rb);
			if (rb) {
				if (rb->rb_left == &pe->rb_aec)
					rb->rb_left = NULL;
				else
					rb->rb_right = NULL;
			}

			kmem_cache_free(ubi_wl_entry_slab, pe->e);
			kfree(pe);
		}
	}
}

void ubi_wl_close(struct ubi_device *ubi)
{
	dbg_wl("close the UBI wear-leveling unit");

	cancel_pending(ubi);
	protection_trees_destroy(ubi);
	tree_destroy(&ubi->used);
	tree_destroy(&ubi->free);
	tree_destroy(&ubi->scrub);
	kfree(ubi->lookuptbl);
}

#ifdef CONFIG_MTD_UBI_DEBUG_PARANOID

static int paranoid_check_ec(struct ubi_device *ubi, int pnum, int ec)
{
	int err;
	long long read_ec;
	struct ubi_ec_hdr *ec_hdr;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_NOFS);
	if (!ec_hdr)
		return -ENOMEM;

	err = ubi_io_read_ec_hdr(ubi, pnum, ec_hdr, 0);
	if (err && err != UBI_IO_BITFLIPS) {
		/* The header does not have to exist */
		err = 0;
		goto out_free;
	}

	read_ec = be64_to_cpu(ec_hdr->ec);
	if (ec != read_ec) {
		ubi_err("paranoid check failed for PEB %d", pnum);
		ubi_err("read EC is %lld, should be %d", read_ec, ec);
		ubi_dbg_dump_stack();
		err = 1;
	} else
		err = 0;

out_free:
	kfree(ec_hdr);
	return err;
}

static int paranoid_check_in_wl_tree(struct ubi_wl_entry *e,
				     struct rb_root *root)
{
	if (in_wl_tree(e, root))
		return 0;

	ubi_err("paranoid check failed for PEB %d, EC %d, RB-tree %p ",
		e->pnum, e->ec, root);
	ubi_dbg_dump_stack();
	return 1;
}

#endif /* CONFIG_MTD_UBI_DEBUG_PARANOID */
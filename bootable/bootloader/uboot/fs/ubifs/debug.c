


#define UBIFS_DBG_PRESERVE_UBI

#include "ubifs.h"

#ifdef CONFIG_UBIFS_FS_DEBUG

DEFINE_SPINLOCK(dbg_lock);

static char dbg_key_buf0[128];
static char dbg_key_buf1[128];

unsigned int ubifs_msg_flags = UBIFS_MSG_FLAGS_DEFAULT;
unsigned int ubifs_chk_flags = UBIFS_CHK_FLAGS_DEFAULT;
unsigned int ubifs_tst_flags;

module_param_named(debug_msgs, ubifs_msg_flags, uint, S_IRUGO | S_IWUSR);
module_param_named(debug_chks, ubifs_chk_flags, uint, S_IRUGO | S_IWUSR);
module_param_named(debug_tsts, ubifs_tst_flags, uint, S_IRUGO | S_IWUSR);

MODULE_PARM_DESC(debug_msgs, "Debug message type flags");
MODULE_PARM_DESC(debug_chks, "Debug check flags");
MODULE_PARM_DESC(debug_tsts, "Debug special test flags");

static const char *get_key_type(int type)
{
	switch (type) {
	case UBIFS_INO_KEY:
		return "inode";
	case UBIFS_DENT_KEY:
		return "direntry";
	case UBIFS_XENT_KEY:
		return "xentry";
	case UBIFS_DATA_KEY:
		return "data";
	case UBIFS_TRUN_KEY:
		return "truncate";
	default:
		return "unknown/invalid key";
	}
}

static void sprintf_key(const struct ubifs_info *c, const union ubifs_key *key,
			char *buffer)
{
	char *p = buffer;
	int type = key_type(c, key);

	if (c->key_fmt == UBIFS_SIMPLE_KEY_FMT) {
		switch (type) {
		case UBIFS_INO_KEY:
			sprintf(p, "(%lu, %s)", (unsigned long)key_inum(c, key),
			       get_key_type(type));
			break;
		case UBIFS_DENT_KEY:
		case UBIFS_XENT_KEY:
			sprintf(p, "(%lu, %s, %#08x)",
				(unsigned long)key_inum(c, key),
				get_key_type(type), key_hash(c, key));
			break;
		case UBIFS_DATA_KEY:
			sprintf(p, "(%lu, %s, %u)",
				(unsigned long)key_inum(c, key),
				get_key_type(type), key_block(c, key));
			break;
		case UBIFS_TRUN_KEY:
			sprintf(p, "(%lu, %s)",
				(unsigned long)key_inum(c, key),
				get_key_type(type));
			break;
		default:
			sprintf(p, "(bad key type: %#08x, %#08x)",
				key->u32[0], key->u32[1]);
		}
	} else
		sprintf(p, "bad key format %d", c->key_fmt);
}

const char *dbg_key_str0(const struct ubifs_info *c, const union ubifs_key *key)
{
	/* dbg_lock must be held */
	sprintf_key(c, key, dbg_key_buf0);
	return dbg_key_buf0;
}

const char *dbg_key_str1(const struct ubifs_info *c, const union ubifs_key *key)
{
	/* dbg_lock must be held */
	sprintf_key(c, key, dbg_key_buf1);
	return dbg_key_buf1;
}

int ubifs_debugging_init(struct ubifs_info *c)
{
	c->dbg = kzalloc(sizeof(struct ubifs_debug_info), GFP_KERNEL);
	if (!c->dbg)
		return -ENOMEM;

	c->dbg->buf = vmalloc(c->leb_size);
	if (!c->dbg->buf)
		goto out;

	return 0;

out:
	kfree(c->dbg);
	return -ENOMEM;
}

void ubifs_debugging_exit(struct ubifs_info *c)
{
	vfree(c->dbg->buf);
	kfree(c->dbg);
}

#endif /* CONFIG_UBIFS_FS_DEBUG */

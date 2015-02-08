



#include <common.h>
#include <linux/stat.h>

#if ( S_ISUID != 04000 ) || ( S_ISGID != 02000 ) || ( S_ISVTX != 01000 ) \
 || ( S_IRUSR != 00400 ) || ( S_IWUSR != 00200 ) || ( S_IXUSR != 00100 ) \
 || ( S_IRGRP != 00040 ) || ( S_IWGRP != 00020 ) || ( S_IXGRP != 00010 ) \
 || ( S_IROTH != 00004 ) || ( S_IWOTH != 00002 ) || ( S_IXOTH != 00001 )
#error permission bitflag value assumption(s) violated!
#endif

#if ( S_IFSOCK!= 0140000 ) || ( S_IFLNK != 0120000 ) \
 || ( S_IFREG != 0100000 ) || ( S_IFBLK != 0060000 ) \
 || ( S_IFDIR != 0040000 ) || ( S_IFCHR != 0020000 ) \
 || ( S_IFIFO != 0010000 )
#warning mode type bitflag value assumption(s) violated! falling back to larger version

#if (S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX) == 07777
#undef mode_t
#define mode_t unsigned short
#endif

static const mode_t mode_flags[] = {
	S_IRUSR, S_IWUSR, S_IXUSR, S_ISUID,
	S_IRGRP, S_IWGRP, S_IXGRP, S_ISGID,
	S_IROTH, S_IWOTH, S_IXOTH, S_ISVTX
};


static const char type_chars[16] = "?pc?d?b?-?l?s???";
/*                                  0123456789abcdef */
static const char mode_chars[7] = "rwxSTst";

const char *bb_mode_string(int mode)
{
	static char buf[12];
	char *p = buf;

	int i, j, k;

	*p = type_chars[ (mode >> 12) & 0xf ];
	i = 0;
	do {
		j = k = 0;
		do {
			*++p = '-';
			if (mode & mode_flags[i+j]) {
				*p = mode_chars[j];
				k = j;
			}
		} while (++j < 3);
		if (mode & mode_flags[i+j]) {
			*p = mode_chars[3 + (k & 2) + ((i&8) >> 3)];
		}
		i += 4;
	} while (i < 12);

	/* Note: We don't bother with nul termination because bss initialization
	 * should have taken care of that for us.  If the user scribbled in buf
	 * memory, they deserve whatever happens.  But we'll at least assert. */
	if (buf[10] != 0) return NULL;

	return buf;
}

#else

static const char type_chars[16] = "?pc?d?b?-?l?s???";
/*                                  0123456789abcdef */
static const char mode_chars[7] = "rwxSTst";

const char *bb_mode_string(int mode)
{
	static char buf[12];
	char *p = buf;

	int i, j, k, m;

	*p = type_chars[ (mode >> 12) & 0xf ];
	i = 0;
	m = 0400;
	do {
		j = k = 0;
		do {
			*++p = '-';
			if (mode & m) {
				*p = mode_chars[j];
				k = j;
			}
			m >>= 1;
		} while (++j < 3);
		++i;
		if (mode & (010000 >> i)) {
			*p = mode_chars[3 + (k & 2) + (i == 3)];
		}
	} while (i < 3);

	/* Note: We don't bother with nul termination because bss initialization
	 * should have taken care of that for us.  If the user scribbled in buf
	 * memory, they deserve whatever happens.  But we'll at least assert. */
	if (buf[10] != 0) return NULL;

	return buf;
}

#endif

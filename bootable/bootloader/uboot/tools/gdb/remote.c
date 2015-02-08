

/* enough so that it will compile */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*nicked from gcc..*/

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#ifdef __cplusplus
extern "C" {
#endif
    void* alloca(size_t);
#ifdef __cplusplus
}
#endif
#endif /* alloca not defined.  */


#include "serial.h"
#include "error.h"
#include "remote.h"
#define REGISTER_BYTES 0
#define fprintf_unfiltered fprintf
#define fprintf_filtered fprintf
#define fputs_unfiltered fputs
#define fputs_filtered fputs
#define fputc_unfiltered fputc
#define fputc_filtered fputc
#define printf_unfiltered printf
#define printf_filtered printf
#define puts_unfiltered puts
#define puts_filtered puts
#define putchar_unfiltered putchar
#define putchar_filtered putchar
#define fputstr_unfiltered(a,b,c) fputs((a), (c))
#define gdb_stdlog stderr
#define SERIAL_READCHAR(fd,timo)	serialreadchar((fd), (timo))
#define SERIAL_WRITE(fd, addr, len)	serialwrite((fd), (addr), (len))
#define error Error
#define perror_with_name Perror
#define gdb_flush fflush
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define target_mourn_inferior() {}
#define ULONGEST unsigned long
#define CORE_ADDR unsigned long

static int putpkt (char *);
static int putpkt_binary(char *, int);
static void getpkt (char *, int);

static int remote_debug = 0, remote_register_buf_size = 0, watchdog = 0;

int remote_desc = -1, remote_timeout = 10;

static void
fputstrn_unfiltered(char *s, int n, int x, FILE *fp)
{
    while (n-- > 0)
	fputc(*s++, fp);
}

void
remote_reset(void)
{
    SERIAL_WRITE(remote_desc, "+", 1);
}

void
remote_continue(void)
{
    putpkt("c");
}

/* *INDENT-OFF* */
/* *INDENT-ON* */

static int remote_binary_download = 1;

/* Have we already checked whether binary downloads work? */
static int remote_binary_checked;

#define MAXBUFBYTES(N) (((N)-32)/2)

/* Round up PBUFSIZ to hold all the registers, at least.  */
#define	PBUFSIZ ((REGISTER_BYTES > MAXBUFBYTES (400)) \
		 ? (REGISTER_BYTES * 2 + 32) \
		 : 400)



static int remote_write_size = 0x7fffffff;


static int remote_address_size;

/* Convert hex digit A to a number.  */

static int
fromhex (int a)
{
  if (a >= '0' && a <= '9')
    return a - '0';
  else if (a >= 'a' && a <= 'f')
    return a - 'a' + 10;
  else if (a >= 'A' && a <= 'F')
    return a - 'A' + 10;
  else {
    error ("Reply contains invalid hex digit %d", a);
    return -1;
  }
}

/* Convert number NIB to a hex digit.  */

static int
tohex (int nib)
{
  if (nib < 10)
    return '0' + nib;
  else
    return 'a' + nib - 10;
}

/* Return the number of hex digits in num.  */

static int
hexnumlen (ULONGEST num)
{
  int i;

  for (i = 0; num != 0; i++)
    num >>= 4;

  return max (i, 1);
}

/* Set BUF to the hex digits representing NUM.  */

static int
hexnumstr (char *buf, ULONGEST num)
{
  int i;
  int len = hexnumlen (num);

  buf[len] = '\0';

  for (i = len - 1; i >= 0; i--)
    {
      buf[i] = "0123456789abcdef"[(num & 0xf)];
      num >>= 4;
    }

  return len;
}

/* Mask all but the least significant REMOTE_ADDRESS_SIZE bits. */

static CORE_ADDR
remote_address_masked (CORE_ADDR addr)
{
  if (remote_address_size > 0
      && remote_address_size < (sizeof (ULONGEST) * 8))
    {
      /* Only create a mask when that mask can safely be constructed
	 in a ULONGEST variable. */
      ULONGEST mask = 1;
      mask = (mask << remote_address_size) - 1;
      addr &= mask;
    }
  return addr;
}

static void
check_binary_download (CORE_ADDR addr)
{
  if (remote_binary_download && !remote_binary_checked)
    {
      char *buf = alloca (PBUFSIZ);
      char *p;
      remote_binary_checked = 1;

      p = buf;
      *p++ = 'X';
      p += hexnumstr (p, (ULONGEST) addr);
      *p++ = ',';
      p += hexnumstr (p, (ULONGEST) 0);
      *p++ = ':';
      *p = '\0';

      putpkt_binary (buf, (int) (p - buf));
      getpkt (buf, 0);

      if (buf[0] == '\0')
	remote_binary_download = 0;
    }

  if (remote_debug)
    {
      if (remote_binary_download)
	fprintf_unfiltered (gdb_stdlog,
			    "binary downloading suppported by target\n");
      else
	fprintf_unfiltered (gdb_stdlog,
			    "binary downloading NOT suppported by target\n");
    }
}


int
remote_write_bytes (memaddr, myaddr, len)
     CORE_ADDR memaddr;
     char *myaddr;
     int len;
{
  unsigned char *buf = alloca (PBUFSIZ);
  int max_buf_size;		/* Max size of packet output buffer */
  int origlen;
  extern int verbose;

  /* Verify that the target can support a binary download */
  check_binary_download (memaddr);

  /* Chop the transfer down if necessary */

  max_buf_size = min (remote_write_size, PBUFSIZ);
  if (remote_register_buf_size != 0)
    max_buf_size = min (max_buf_size, remote_register_buf_size);

  /* Subtract header overhead from max payload size -  $M<memaddr>,<len>:#nn */
  max_buf_size -= 2 + hexnumlen (memaddr + len - 1) + 1 + hexnumlen (len) + 4;

  origlen = len;
  while (len > 0)
    {
      unsigned char *p, *plen;
      int todo;
      int i;

      /* construct "M"<memaddr>","<len>":" */
      /* sprintf (buf, "M%lx,%x:", (unsigned long) memaddr, todo); */
      memaddr = remote_address_masked (memaddr);
      p = buf;
      if (remote_binary_download)
	{
	  *p++ = 'X';
	  todo = min (len, max_buf_size);
	}
      else
	{
	  *p++ = 'M';
	  todo = min (len, max_buf_size / 2);	/* num bytes that will fit */
	}

      p += hexnumstr ((char *)p, (ULONGEST) memaddr);
      *p++ = ',';

      plen = p;			/* remember where len field goes */
      p += hexnumstr ((char *)p, (ULONGEST) todo);
      *p++ = ':';
      *p = '\0';

      /* We send target system values byte by byte, in increasing byte
	 addresses, each byte encoded as two hex characters (or one
	 binary character).  */
      if (remote_binary_download)
	{
	  int escaped = 0;
	  for (i = 0;
	       (i < todo) && (i + escaped) < (max_buf_size - 2);
	       i++)
	    {
	      switch (myaddr[i] & 0xff)
		{
		case '$':
		case '#':
		case 0x7d:
		  /* These must be escaped */
		  escaped++;
		  *p++ = 0x7d;
		  *p++ = (myaddr[i] & 0xff) ^ 0x20;
		  break;
		default:
		  *p++ = myaddr[i] & 0xff;
		  break;
		}
	    }

	  if (i < todo)
	    {
	      /* Escape chars have filled up the buffer prematurely,
		 and we have actually sent fewer bytes than planned.
		 Fix-up the length field of the packet.  */

	      /* FIXME: will fail if new len is a shorter string than
		 old len.  */

	      plen += hexnumstr ((char *)plen, (ULONGEST) i);
	      *plen++ = ':';
	    }
	}
      else
	{
	  for (i = 0; i < todo; i++)
	    {
	      *p++ = tohex ((myaddr[i] >> 4) & 0xf);
	      *p++ = tohex (myaddr[i] & 0xf);
	    }
	  *p = '\0';
	}

      putpkt_binary ((char *)buf, (int) (p - buf));
      getpkt ((char *)buf, 0);

      if (buf[0] == 'E')
	{
	  /* There is no correspondance between what the remote protocol uses
	     for errors and errno codes.  We would like a cleaner way of
	     representing errors (big enough to include errno codes, bfd_error
	     codes, and others).  But for now just return EIO.  */
	  errno = EIO;
	  return 0;
	}

      /* Increment by i, not by todo, in case escape chars
	 caused us to send fewer bytes than we'd planned.  */
      myaddr += i;
      memaddr += i;
      len -= i;

      if (verbose)
	putc('.', stderr);
    }
  return origlen;
}


/* Read a single character from the remote end, masking it down to 7 bits. */

static int
readchar (int timeout)
{
  int ch;

  ch = SERIAL_READCHAR (remote_desc, timeout);

  switch (ch)
    {
    case SERIAL_EOF:
      error ("Remote connection closed");
    case SERIAL_ERROR:
      perror_with_name ("Remote communication error");
    case SERIAL_TIMEOUT:
      return ch;
    default:
      return ch & 0x7f;
    }
}

static int
putpkt (buf)
     char *buf;
{
  return putpkt_binary (buf, strlen (buf));
}


static int
putpkt_binary (buf, cnt)
     char *buf;
     int cnt;
{
  int i;
  unsigned char csum = 0;
  char *buf2 = alloca (PBUFSIZ);
  char *junkbuf = alloca (PBUFSIZ);

  int ch;
  int tcount = 0;
  char *p;

  /* Copy the packet into buffer BUF2, encapsulating it
     and giving it a checksum.  */

  if (cnt > BUFSIZ - 5)		/* Prosanity check */
    abort ();

  p = buf2;
  *p++ = '$';

  for (i = 0; i < cnt; i++)
    {
      csum += buf[i];
      *p++ = buf[i];
    }
  *p++ = '#';
  *p++ = tohex ((csum >> 4) & 0xf);
  *p++ = tohex (csum & 0xf);

  /* Send it over and over until we get a positive ack.  */

  while (1)
    {
      int started_error_output = 0;

      if (remote_debug)
	{
	  *p = '\0';
	  fprintf_unfiltered (gdb_stdlog, "Sending packet: ");
	  fputstrn_unfiltered (buf2, p - buf2, 0, gdb_stdlog);
	  fprintf_unfiltered (gdb_stdlog, "...");
	  gdb_flush (gdb_stdlog);
	}
      if (SERIAL_WRITE (remote_desc, buf2, p - buf2))
	perror_with_name ("putpkt: write failed");

      /* read until either a timeout occurs (-2) or '+' is read */
      while (1)
	{
	  ch = readchar (remote_timeout);

	  if (remote_debug)
	    {
	      switch (ch)
		{
		case '+':
		case SERIAL_TIMEOUT:
		case '$':
		  if (started_error_output)
		    {
		      putchar_unfiltered ('\n');
		      started_error_output = 0;
		    }
		}
	    }

	  switch (ch)
	    {
	    case '+':
	      if (remote_debug)
		fprintf_unfiltered (gdb_stdlog, "Ack\n");
	      return 1;
	    case SERIAL_TIMEOUT:
	      tcount++;
	      if (tcount > 3)
		return 0;
	      break;		/* Retransmit buffer */
	    case '$':
	      {
		/* It's probably an old response, and we're out of sync.
		   Just gobble up the packet and ignore it.  */
		getpkt (junkbuf, 0);
		continue;	/* Now, go look for + */
	      }
	    default:
	      if (remote_debug)
		{
		  if (!started_error_output)
		    {
		      started_error_output = 1;
		      fprintf_unfiltered (gdb_stdlog, "putpkt: Junk: ");
		    }
		  fputc_unfiltered (ch & 0177, gdb_stdlog);
		}
	      continue;
	    }
	  break;		/* Here to retransmit */
	}

#if 0
      /* This is wrong.  If doing a long backtrace, the user should be
	 able to get out next time we call QUIT, without anything as
	 violent as interrupt_query.  If we want to provide a way out of
	 here without getting to the next QUIT, it should be based on
	 hitting ^C twice as in remote_wait.  */
      if (quit_flag)
	{
	  quit_flag = 0;
	  interrupt_query ();
	}
#endif
    }
}


static int
read_frame (char *buf)
{
  unsigned char csum;
  char *bp;
  int c;

  csum = 0;
  bp = buf;

  while (1)
    {
      c = readchar (remote_timeout);

      switch (c)
	{
	case SERIAL_TIMEOUT:
	  if (remote_debug)
	    fputs_filtered ("Timeout in mid-packet, retrying\n", gdb_stdlog);
	  return 0;
	case '$':
	  if (remote_debug)
	    fputs_filtered ("Saw new packet start in middle of old one\n",
			    gdb_stdlog);
	  return 0;		/* Start a new packet, count retries */
	case '#':
	  {
	    unsigned char pktcsum;

	    *bp = '\000';

	    pktcsum = fromhex (readchar (remote_timeout)) << 4;
	    pktcsum |= fromhex (readchar (remote_timeout));

	    if (csum == pktcsum)
	      {
		return 1;
	      }

	    if (remote_debug)
	      {
		fprintf_filtered (gdb_stdlog,
			      "Bad checksum, sentsum=0x%x, csum=0x%x, buf=",
				  pktcsum, csum);
		fputs_filtered (buf, gdb_stdlog);
		fputs_filtered ("\n", gdb_stdlog);
	      }
	    return 0;
	  }
	case '*':		/* Run length encoding */
	  csum += c;
	  c = readchar (remote_timeout);
	  csum += c;
	  c = c - ' ' + 3;	/* Compute repeat count */

	  if (c > 0 && c < 255 && bp + c - 1 < buf + PBUFSIZ - 1)
	    {
	      memset (bp, *(bp - 1), c);
	      bp += c;
	      continue;
	    }

	  *bp = '\0';
	  printf_filtered ("Repeat count %d too large for buffer: ", c);
	  puts_filtered (buf);
	  puts_filtered ("\n");
	  return 0;
	default:
	  if (bp < buf + PBUFSIZ - 1)
	    {
	      *bp++ = c;
	      csum += c;
	      continue;
	    }

	  *bp = '\0';
	  puts_filtered ("Remote packet too long: ");
	  puts_filtered (buf);
	  puts_filtered ("\n");

	  return 0;
	}
    }
}


static void
getpkt (buf, forever)
     char *buf;
     int forever;
{
  int c;
  int tries;
  int timeout;
  int val;

  strcpy (buf, "timeout");

  if (forever)
    {
      timeout = watchdog > 0 ? watchdog : -1;
    }

  else
    timeout = remote_timeout;

#define MAX_TRIES 3

  for (tries = 1; tries <= MAX_TRIES; tries++)
    {
      /* This can loop forever if the remote side sends us characters
	 continuously, but if it pauses, we'll get a zero from readchar
	 because of timeout.  Then we'll count that as a retry.  */

      /* Note that we will only wait forever prior to the start of a packet.
	 After that, we expect characters to arrive at a brisk pace.  They
	 should show up within remote_timeout intervals.  */

      do
	{
	  c = readchar (timeout);

	  if (c == SERIAL_TIMEOUT)
	    {
	      if (forever)	/* Watchdog went off.  Kill the target. */
		{
		  target_mourn_inferior ();
		  error ("Watchdog has expired.  Target detached.\n");
		}
	      if (remote_debug)
		fputs_filtered ("Timed out.\n", gdb_stdlog);
	      goto retry;
	    }
	}
      while (c != '$');

      /* We've found the start of a packet, now collect the data.  */

      val = read_frame (buf);

      if (val == 1)
	{
	  if (remote_debug)
	    {
	      fprintf_unfiltered (gdb_stdlog, "Packet received: ");
	      fputstr_unfiltered (buf, 0, gdb_stdlog);
	      fprintf_unfiltered (gdb_stdlog, "\n");
	    }
	  SERIAL_WRITE (remote_desc, "+", 1);
	  return;
	}

      /* Try the whole thing again.  */
    retry:
      SERIAL_WRITE (remote_desc, "-", 1);
    }

  /* We have tried hard enough, and just can't receive the packet.  Give up. */

  printf_unfiltered ("Ignoring packet error, continuing...\n");
  SERIAL_WRITE (remote_desc, "+", 1);
}

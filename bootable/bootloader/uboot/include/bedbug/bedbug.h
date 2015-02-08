
/* $Id$ */

#ifndef _BEDBUG_H
#define _BEDBUG_H

#ifndef NULL
#define NULL	0
#endif

#define _USE_PROTOTYPES

#ifndef isblank
#define isblank(c) isspace((int)(c))
#endif

#ifndef __P
#if defined(_USE_PROTOTYPES) && (defined(__STDC__) || defined(__cplusplus))
#define __P(protos)	protos		/* full-blown ANSI C */
#else
#define __P(protos)	()		/* traditional C preprocessor */
#endif
#endif

#define assert( condition ) if( (condition) ) _exit(0)

#endif /* _BEDBUG_H */



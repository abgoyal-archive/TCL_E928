


#define SREC_START	0	/* Start Record (module name)		    */
#define SREC_DATA2	1	/* Data  Record with 2 byte address	    */
#define SREC_DATA3	2	/* Data  Record with 3 byte address	    */
#define SREC_DATA4	3	/* Data  Record with 4 byte address	    */
#define SREC_COUNT	5	/* Count Record (previously transmitted)    */
#define SREC_END4	7	/* End   Record with 4 byte start address   */
#define SREC_END3	8	/* End   Record with 3 byte start address   */
#define SREC_END2	9	/* End   Record with 2 byte start address   */
#define SREC_EMPTY	10	/* Empty Record without any data	    */

#define SREC_REC_OK  SREC_EMPTY /* last code without error condition	    */

#define SREC_E_BADTYPE	-1	/* no valid S-Record		            */
#define SREC_E_NOSREC	-2	/* line format differs from s-record	    */
#define SREC_E_BADCHKS	-3	/* checksum error in an s-record line	    */

#define SREC_MAXRECLEN	(512 + 4)   /* max ASCII record length		    */
#define SREC_MAXBINLEN	255	    /* resulting binary length		    */

int srec_decode (char *input, int *count, ulong *addr, char *data);

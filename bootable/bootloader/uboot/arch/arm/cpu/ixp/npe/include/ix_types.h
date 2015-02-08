

#if !defined(__IX_TYPES_H__)
#define __IX_TYPES_H__


#if defined(__cplusplus)
extern "C"
{
#endif /* end defined(__cplusplus) */



typedef signed char ix_int8;


typedef unsigned char ix_uint8;


typedef signed short int ix_int16;


typedef unsigned short int ix_uint16;


typedef signed int ix_int32;


#ifndef __wince
typedef unsigned int ix_uint32;
#else
typedef unsigned long ix_uint32;
#endif

#ifndef __wince
__extension__ typedef signed long long int ix_int64;
#endif

#ifndef __wince
__extension__ typedef unsigned long long int ix_uint64;
#endif


typedef ix_uint8 ix_bit_mask8;


typedef ix_uint16 ix_bit_mask16;


typedef ix_uint32 ix_bit_mask32;


#ifndef __wince
typedef ix_uint64 ix_bit_mask64;
#endif


typedef ix_uint32 ix_handle;



#define IX_NULL_HANDLE   ((ix_handle)0) 


#if defined(__cplusplus)
}
#endif /* end defined(__cplusplus) */

#endif /* end !defined(__IX_TYPES_H__) */

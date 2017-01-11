#ifndef _DUCKLET_TYPES_H
#define _DUCKLET_TYPES_H

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRST  "\033[0m"

#define ARRAYLENGTH(x) (sizeof((x))/sizeof((x[0])))

/*typedef unsigned char  uchar;
#if CHAR_BIT == 8
typedef          uchar ubyte;
typedef signed   char  byte;
typedef          uchar uint8;
#else
typedef          char  wchar;
#endif
typedef unsigned int uint;
#if UINT_MAX == 0xffffffff
typedef unsigned int uint32;
typedef signed   int int32;
#elif UINT_MAX == 0xffff
typedef unsigned int uint16;
typedef signed   int int16;
#endif
typedef unsigned long int ulong;
#if ULONG_MAX == 0xffFFffFFffFFffFF
typedef unsigned long int uint64;
typedef signed   long int int64;
#elif ULONG_MAX == 0xffFFffFF
typedef unsigned long int uint32;
typedef signed   long int int32;
#endif
typedef unsigned short int ushort;
#if USHORT_MAX == 0xffFF
typedef unsigned short int uint16;
typedef signed   short int uint16;
#endif*/

typedef struct _http_request_t http_request_t;
typedef struct _connection_t connection_t;
typedef struct _ducklet_resource_t ducklet_resource_t;
typedef struct _ducklet_site_t ducklet_site_t;
#endif

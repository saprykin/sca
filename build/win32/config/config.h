/* Define to 1 if you have the <float.h> header file. */
#define HAVE_FLOAT_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the 'long double' type. */
#define HAVE_LONG_DOUBLE 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef _MSC_VER
#define HAVE_STDINT_H 1
#else /* _MSC_VER */
/* #undef HAVE_STDINT_H */
#endif /* _MSC_VER */

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#ifndef _MSC_VER
#define HAVE_SYS_TIME_H 1
#else /* _MSC_VER */
/* #undef HAVE_SYS_TIME_H */
#endif /* _MSC_VER */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef _MSC_VER
#define HAVE_UNISTD_H 1
#else /* _MSC_VER */
/* #undef HAVE_UNISTD_H */
#endif /* _MSC_VER */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

#if defined (_MSC_VER) && !defined (_USE_MATH_DEFINES)
#  define _USE_MATH_DEFINES
#endif /* _MSC_VER && _USE_MATH_DEFINES */

#if defined (_MSC_VER) && !defined (trunc)
#  define trunc(x) ((double)((__int64) (x)))
#endif /* _MSC_VER && trunc */

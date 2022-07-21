// Specific definitions for BSD  -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.


#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

#define _GLIBCXX_USE_C99_STDIO 1
#define _GLIBCXX_USE_C99_STDLIB 1
#define _GLIBCXX_USE_C99_WCHAR 1

#define _GLIBCXX_USE_C99_CHECK 1
#define _GLIBCXX_USE_C99_DYNAMIC (!(__ISO_C_VISIBLE >= 1999))
#define _GLIBCXX_USE_C99_LONG_LONG_CHECK 1
#define _GLIBCXX_USE_C99_LONG_LONG_DYNAMIC (_GLIBCXX_USE_C99_DYNAMIC || !defined __LONG_LONG_SUPPORTED)
#define _GLIBCXX_USE_C99_FLOAT_TRANSCENDENTALS_CHECK 1
#define _GLIBCXX_USE_C99_FLOAT_TRANSCENDENTALS_DYNAMIC defined _XOPEN_SOURCE

#endif

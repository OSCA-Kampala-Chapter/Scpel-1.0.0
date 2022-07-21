// Specific definitions for OpenBSD  -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/os_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */

#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

#define _GLIBCXX_USE_C99_DYNAMIC (!(__ISO_C_VISIBLE >= 1999))
#define _GLIBCXX_USE_C99_LONG_LONG_DYNAMIC _GLIBCXX_USE_C99_DYNAMIC
#define _GLIBCXX_USE_C99_FLOAT_TRANSCENDENTALS_DYNAMIC _GLIBCXX_USE_C99_DYNAMIC
#define _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC _GLIBCXX_USE_C99_DYNAMIC

#endif

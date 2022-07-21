// Specific definitions for TPF  -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/os_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */

#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

// TPF is a big endian OS, let it be known here.
#define _BIG_ENDIAN 1

// This keeps isanum, et al from being propagated as macros.
#define __NO_CTYPE 1

// We must not see the optimized string functions GNU libc defines.
#define __NO_STRING_INLINES

#endif

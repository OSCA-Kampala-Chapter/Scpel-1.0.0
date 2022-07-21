// SPDX-License-Identifier: GPL-3.0-or-later WITH GCC-exception-3.1
// Specific definitions for AIX  -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/os_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */

#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

// off64_t
#ifndef _LARGE_FILE_API
#define _LARGE_FILE_API
#endif

// atomic types
#ifndef _ALL_SOURCE
#define _ALL_SOURCE
#endif

// C99 math
#ifndef __COMPATMATH__
#define __COMPATMATH__
#endif

#ifndef __LIBC_NO_CPP_MATH_OVERLOADS__
#define __LIBC_NO_CPP_MATH_OVERLOADS__
#endif

// No support for referencing weak symbols without a definition.
#define _GLIBCXX_USE_WEAK_REF 0

#endif

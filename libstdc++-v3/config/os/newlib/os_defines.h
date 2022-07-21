// Specific definitions for newlib  -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/os_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */

#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

#ifdef __CYGWIN__
#define _GLIBCXX_GTHREAD_USE_WEAK 0

#if defined (_GLIBCXX_DLL)
#define _GLIBCXX_PSEUDO_VISIBILITY_default __attribute__ ((__dllimport__))
#else
#define _GLIBCXX_PSEUDO_VISIBILITY_default
#endif
#define _GLIBCXX_PSEUDO_VISIBILITY_hidden

#define _GLIBCXX_PSEUDO_VISIBILITY(V) _GLIBCXX_PSEUDO_VISIBILITY_ ## V

// See libstdc++/20806.
#define _GLIBCXX_HAVE_DOS_BASED_FILESYSTEM 1

// Enable use of GetModuleHandleEx (requires Windows XP/2003) in
// __cxa_thread_atexit to prevent modules from being unloaded before
// their dtors are called
#define _GLIBCXX_THREAD_ATEXIT_WIN32 1

// See libstdc++/69506
#define _GLIBCXX_USE_WEAK_REF 0

#endif

#endif

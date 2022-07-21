// Specific definitions for Darwin -*- C++ -*-

//Please review $(srcdir/SPL-README) for GNU licencing info.


#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

/* Darwin has the pthread routines in libSystem, which every program
   links to, so there's no need for weak-ness for that.  */
#define _GLIBCXX_GTHREAD_USE_WEAK 0

// On Darwin, in order to enable overriding of operator new and delete,
// GCC makes the definition of these functions weak, relies on the
// loader to implement weak semantics properly, and uses
// -flat_namespace to work around the way that it doesn't.
#define _GLIBCXX_WEAK_DEFINITION __attribute__ ((weak))

// Static initializer macro is buggy in darwin, see libstdc++/51906
#define _GTHREAD_USE_RECURSIVE_MUTEX_INIT_FUNC

// Configure checks for nanosleep fail on Darwin, but nanosleep and
// sched_yield are always available, so use them.
#define _GLIBCXX_USE_NANOSLEEP 1
#define _GLIBCXX_USE_SCHED_YIELD 1

// No support for referencing weak symbols without a definition.
#define _GLIBCXX_USE_WEAK_REF 0

#endif

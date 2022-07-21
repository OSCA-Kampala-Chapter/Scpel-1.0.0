// TR1 stdlib.h -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file tr1/stdlib.h
 *  This is a TR1 C++ Library header. 
 */

#ifndef _GLIBCXX_TR1_STDLIB_H
#define _GLIBCXX_TR1_STDLIB_H 1

#include <tr1/cstdlib>

#if _GLIBCXX_HOSTED

#if _GLIBCXX_USE_C99_STDLIB

using std::tr1::atoll;
using std::tr1::strtoll;
using std::tr1::strtoull;

using std::tr1::abs;
#if !_GLIBCXX_USE_C99_LONG_LONG_DYNAMIC
using std::tr1::div;
#endif

#endif

#endif

#endif // _GLIBCXX_TR1_STDLIB_H


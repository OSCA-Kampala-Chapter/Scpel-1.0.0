// -*- C++ -*- compatibility header.

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file stdbool.h
 *  This is a Standard C++ Library header.
 */

#include <bits/c++config.h>

#if __cplusplus >= 201103L
# include <cstdbool>
#else
# if _GLIBCXX_HAVE_STDBOOL_H
#  include_next <stdbool.h>
# endif
#endif

#ifndef _GLIBCXX_STDBOOL_H
#define _GLIBCXX_STDBOOL_H 1

#endif

// Base to std::allocator -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/c++allocator.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{memory}
 */

#ifndef _GLIBCXX_CXX_ALLOCATOR_H
#define _GLIBCXX_CXX_ALLOCATOR_H 1

#include <ext/malloc_allocator.h>

#if __cplusplus >= 201103L
namespace std
{
  /**
   *  @brief  An alias to the base class for std::allocator.
   *  @ingroup allocators
   *
   *  Used to set the std::allocator base class to
   *  __gnu_cxx::malloc_allocator.
   *
   *  @tparam  _Tp  Type of allocated object.
    */
  template<typename _Tp>
    using __allocator_base = __gnu_cxx::malloc_allocator<_Tp>;
}
#else
// Define malloc_allocator as the base class to std::allocator.
# define __allocator_base  __gnu_cxx::malloc_allocator
#endif

#ifndef _GLIBCXX_SANITIZE_STD_ALLOCATOR
# if defined(__SANITIZE_ADDRESS__)
#  define _GLIBCXX_SANITIZE_STD_ALLOCATOR 1
# elif defined __has_feature
#  if __has_feature(address_sanitizer)
#   define _GLIBCXX_SANITIZE_STD_ALLOCATOR 1
#  endif
# endif
#endif

#endif

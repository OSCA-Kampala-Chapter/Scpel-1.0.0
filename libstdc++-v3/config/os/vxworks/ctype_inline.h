// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/ctype_inline.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from target/h/ctype.h

// ctype bits to be inlined go here. Non-inlinable (ie virtual do_*)
// functions go in ctype.cc

#include <_vxworks-versions.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

#if _VXWORKS_MAJOR_LT(7) && !defined(__RTP__)
  bool
  ctype<char>::
  is(mask __m, char __c) const
  { return __ctype[static_cast<unsigned char>(__c)] & __m; }

  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    while (__low < __high)
      *__vec++ = __ctype[static_cast<unsigned char>(*__low++)];
    return __high;
  }

  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
	   && !(__ctype[static_cast<unsigned char>(*__low)] & __m))
      ++__low;
    return __low;
  }

  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
	   && (__ctype[static_cast<unsigned char>(*__low)] & __m))
      ++__low;
    return __low;
  }

#else
  bool
  ctype<char>::
  is(mask __m, char __c) const
  { return _Getpctype()[static_cast<int>(__c)] & __m; }

  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    while (__low < __high)
      *__vec++ = _Getpctype()[static_cast<int>(*__low++)];
    return __high;
  }

  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
	   && !(_Getpctype()[static_cast<int>(*__low)] & __m))
      ++__low;
    return __low;
  }

  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high
	   && (_Getpctype()[static_cast<int>(*__low)] & __m))
      ++__low;
    return __low;
  }
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

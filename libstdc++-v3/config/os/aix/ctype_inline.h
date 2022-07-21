// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/ctype_inline.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

//
// ISO C++ 14882: 22.1  Locales
//

// ctype bits to be inlined go here. Non-inlinable (ie virtual do_*)
// functions go in ctype.cc

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  bool
  ctype<char>::
  is(mask __m, char __c) const
  {
    if(_M_table)
      return _M_table[static_cast<unsigned char>(__c)] & __m;
    else
#ifdef _THREAD_SAFE
      return __OBJ_DATA((*__lc_ctype_ptr))->mask[static_cast<unsigned char>(__c)] & __m;
#else
      return __OBJ_DATA(__lc_ctype)->mask[static_cast<unsigned char>(__c)] & __m;
#endif
  }

  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    if(_M_table)
      while (__low < __high)
	*__vec++ = _M_table[static_cast<unsigned char>(*__low++)];
    else
      while (__low < __high)
#ifdef _THREAD_SAFE
	*__vec++ = __OBJ_DATA((*__lc_ctype_ptr))->mask[static_cast<unsigned char>(*__low++)];
#else
        *__vec++ = __OBJ_DATA(__lc_ctype)->mask[static_cast<unsigned char>(*__low++)];
#endif
    return __high;
  }

  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high && !this->is(__m, *__low))
      ++__low;
    return __low;
  }

  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    while (__low < __high && this->is(__m, *__low) != 0)
      ++__low;
    return __low;
  }

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

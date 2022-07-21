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
    if (_M_table)
      return _M_table[static_cast<unsigned char>(__c)] & __m;
    else
      return __istype(__c, __m);
  }

  const char*
  ctype<char>::
  is(const char* __low, const char* __high, mask* __vec) const
  {
    if (_M_table)
      while (__low < __high)
	*__vec++ = _M_table[static_cast<unsigned char>(*__low++)];
    else
      for (;__low < __high; ++__vec, ++__low)
	{
	  *__vec = __maskrune (*__low, upper | lower | alpha | digit | xdigit
			       | space | print | graph | cntrl | punct | alnum
			       | blank);
	}
    return __high;
  }

  const char*
  ctype<char>::
  scan_is(mask __m, const char* __low, const char* __high) const
  {
    if (_M_table)
      while (__low < __high
	     && !(_M_table[static_cast<unsigned char>(*__low)] & __m))
	++__low;
    else
      while (__low < __high && !this->is(__m, *__low))
	++__low;
    return __low;
  }

  const char*
  ctype<char>::
  scan_not(mask __m, const char* __low, const char* __high) const
  {
    if (_M_table)
      while (__low < __high
	     && (_M_table[static_cast<unsigned char>(*__low)] & __m) != 0)
	++__low;
    else
      while (__low < __high && this->is(__m, *__low) != 0)
	++__low;
    return __low;
  }

#ifdef _GLIBCXX_USE_WCHAR_T
  inline bool
  ctype<wchar_t>::
  do_is(mask __m, wchar_t __c) const
  {
    return __istype (__c, __m);
  }

  inline const wchar_t*
  ctype<wchar_t>::
  do_is(const wchar_t* __lo, const wchar_t* __hi, mask* __vec) const
  {
    for (; __lo < __hi; ++__vec, ++__lo)
      *__vec = __maskrune (*__lo, upper | lower | alpha | digit | xdigit
			   | space | print | graph | cntrl | punct | alnum
			   | blank);
    return __hi;
  }

  inline const wchar_t*
  ctype<wchar_t>::
  do_scan_is(mask __m, const wchar_t* __lo, const wchar_t* __hi) const
  {
    while (__lo < __hi && ! __istype (*__lo, __m))
      ++__lo;
    return __lo;
  }

  inline const wchar_t*
  ctype<wchar_t>::
  do_scan_not(mask __m, const char_type* __lo, const char_type* __hi) const
  {
    while (__lo < __hi && __istype (*__lo, __m))
      ++__lo;
    return __lo;
  }
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file ctype_configure_char.cc */

//
// ISO C++ 14882: 22.1  Locales
//

#include <locale>
#include <cstdlib>
#include <cstring>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

// Information as gleaned from /usr/include/ctype.h

  const ctype_base::mask*
  ctype<char>::classic_table() throw()
  {
    const ctype_base::mask* __ret;
    char* __old = setlocale(LC_CTYPE, NULL);
    const size_t __len = __builtin_strlen(__old) + 1;
    char* __sav = new char[__len];
    __builtin_memcpy(__sav, __old, __len);
    setlocale(LC_CTYPE, "C");
    __ret = *__ctype_b_loc();
    setlocale(LC_CTYPE, __sav);
    delete [] __sav;
    return __ret;
  }

  ctype<char>::ctype(__c_locale, const mask* __table, bool __del,
		     size_t __refs)
  : facet(__refs), _M_del(__table != 0 && __del)
  {
    char* __old = setlocale(LC_CTYPE, NULL);
    const size_t __len = __builtin_strlen(__old) + 1;
    char* __sav = new char[__len];
    __builtin_memcpy(__sav, __old, __len);
    setlocale(LC_CTYPE, "C");
    _M_toupper = *__ctype_toupper_loc();
    _M_tolower = *__ctype_tolower_loc();
    _M_table = __table ? __table : *__ctype_b_loc();
    setlocale(LC_CTYPE, __sav);
    delete [] __sav;
    _M_c_locale_ctype = _S_get_c_locale();
  }

  ctype<char>::ctype(const mask* __table, bool __del, size_t __refs)
  : facet(__refs), _M_del(__table != 0 && __del)
  {
    char* __old = setlocale(LC_CTYPE, NULL);
    const size_t __len = __builtin_strlen(__old) + 1;
    char* __sav = new char[__len];
    __builtin_memcpy(__sav, __old, __len);
    setlocale(LC_CTYPE, "C");
    _M_toupper = *__ctype_toupper_loc();
    _M_tolower = *__ctype_tolower_loc();
    _M_table = __table ? __table : *__ctype_b_loc();
    setlocale(LC_CTYPE, __sav);
    delete [] __sav;
    _M_c_locale_ctype = _S_get_c_locale();
  }

  char
  ctype<char>::do_toupper(char __c) const
  { return _M_toupper[static_cast<unsigned char>(__c)]; }

  const char*
  ctype<char>::do_toupper(char* __low, const char* __high) const
  {
    while (__low < __high)
      {
	*__low = _M_toupper[static_cast<unsigned char>(*__low)];
	++__low;
      }
    return __high;
  }

  char
  ctype<char>::do_tolower(char __c) const
  { return _M_tolower[static_cast<unsigned char>(__c)]; }

  const char*
  ctype<char>::do_tolower(char* __low, const char* __high) const
  {
    while (__low < __high)
      {
	*__low = _M_tolower[static_cast<unsigned char>(*__low)];
	++__low;
      }
    return __high;
  }

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

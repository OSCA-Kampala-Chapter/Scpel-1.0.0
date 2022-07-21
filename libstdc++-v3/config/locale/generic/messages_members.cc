// std::messages implementation details, generic version -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

//
// ISO C++ 14882: 22.2.7.1.2  messages virtual functions
//

// Written by Benjamin Kosnik <bkoz@redhat.com>

#include <locale>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  // Specializations
  template<>
    string
    messages<char>::do_get(catalog, int, int, const string& __dfault) const
    { return __dfault; }

#ifdef _GLIBCXX_USE_WCHAR_T
  template<>
    wstring
    messages<wchar_t>::do_get(catalog, int, int, const wstring& __dfault) const
    { return __dfault; }
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

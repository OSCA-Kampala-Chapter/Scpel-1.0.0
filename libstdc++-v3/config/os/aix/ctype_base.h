// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from /usr/include/ctype.h

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    // Non-standard typedefs.
    typedef const int* 		__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef unsigned int 	mask;
    static const mask upper    	= _ISUPPER;
    static const mask lower 	= _ISLOWER;
    static const mask alpha 	= _ISALPHA;
    static const mask digit 	= _ISDIGIT;
    static const mask xdigit 	= _ISXDIGIT;
    static const mask space 	= _ISSPACE;
    static const mask print 	= _ISPRINT;
    static const mask graph 	= _ISALPHA | _ISDIGIT | _ISPUNCT;
    static const mask cntrl 	= _ISCNTRL;
    static const mask punct 	= _ISPUNCT;
    static const mask alnum 	= _ISALPHA | _ISDIGIT;
#if __cplusplus >= 201103L
    static const mask blank	= _ISBLANK;
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

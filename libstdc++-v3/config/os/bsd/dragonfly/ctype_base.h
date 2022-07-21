// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from /usr/include/ctype.h on DragonFly.

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    // Non-standard typedefs.
    typedef const int*		__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef unsigned long	mask;
    static const mask upper	= _CTYPE_U;
    static const mask lower 	= _CTYPE_L;
    static const mask alpha 	= _CTYPE_A;
    static const mask digit 	= _CTYPE_D;
    static const mask xdigit 	= _CTYPE_X;
    static const mask space 	= _CTYPE_S;
    static const mask print 	= _CTYPE_R;
    static const mask graph 	= _CTYPE_A | _CTYPE_D | _CTYPE_P;
    static const mask cntrl 	= _CTYPE_C;
    static const mask punct 	= _CTYPE_P;
    static const mask alnum 	= _CTYPE_A | _CTYPE_D;
    static const mask blank	= _CTYPE_B;
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

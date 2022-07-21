// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from /usr/include/ctype.h on NetBSD.
// Full details can be found from the CVS files at:
//   anoncvs@anoncvs.netbsd.org:/cvsroot/basesrc/include/ctype.h
// See www.netbsd.org for details of access.

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    // Non-standard typedefs.
    typedef const unsigned char*	__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef unsigned short      	mask;

    static const mask upper	= _CTYPE_U;
    static const mask lower	= _CTYPE_L;
    static const mask alpha	= _CTYPE_A;
    static const mask digit	= _CTYPE_D;
    static const mask xdigit	= _CTYPE_X;
    static const mask space	= _CTYPE_S;
    static const mask print	= _CTYPE_R;
    static const mask graph	= _CTYPE_G;
    static const mask cntrl	= _CTYPE_C;
    static const mask punct	= _CTYPE_P;
    static const mask alnum	= _CTYPE_A | _CTYPE_D;
#if __cplusplus >= 201103L
    static const mask blank	= _CTYPE_BL;
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

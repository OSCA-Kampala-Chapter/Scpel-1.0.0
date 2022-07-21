// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/ctype_base.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

//
// ISO C++ 14882: 22.1  Locales
//

// Information as gleaned from /usr/include/ctype.h.

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
    typedef short		mask;
    static const mask upper    	= _UP;
    static const mask lower 	= _LO;
    static const mask alpha 	= _LO | _UP | _XA;
    static const mask digit 	= _DI;
    static const mask xdigit 	= _XD;
    static const mask space 	= _CN | _SP | _XS;
    static const mask print 	= _DI | _LO | _PU | _SP | _UP | _XA;
    static const mask graph 	= _DI | _LO | _PU | _UP | _XA;
    static const mask cntrl 	= _BB;
    static const mask punct 	= _PU;
    static const mask alnum 	= _DI | _LO | _UP | _XA;
#if __cplusplus >= 201103L
    static const mask blank	= _SP | _XB;
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

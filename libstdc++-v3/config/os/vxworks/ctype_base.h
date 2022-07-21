// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

//
// ISO C++ 14882: 22.1  Locales
//

// Information extracted from target/h/ctype.h.

#include <_vxworks-versions.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
#if _VXWORKS_MAJOR_LT(7) && !defined(__RTP__)
    // Non-standard typedefs.
    typedef const unsigned char* 	__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef unsigned char 	mask;
    static const mask upper    	= _C_UPPER;
    static const mask lower 	= _C_LOWER;
    static const mask alpha 	= _C_UPPER | _C_LOWER;
    static const mask digit 	= _C_NUMBER;
    static const mask xdigit 	= _C_HEX_NUMBER;
    static const mask space 	= _C_WHITE_SPACE | _C_CONTROL;
    static const mask print 	= (_C_UPPER | _C_LOWER | _C_NUMBER
				   | _C_WHITE_SPACE | _C_PUNCT);
    static const mask graph 	= _C_UPPER | _C_LOWER | _C_NUMBER | _C_PUNCT;
    static const mask cntrl 	= _C_CONTROL | _C_B;
    static const mask punct 	= _C_PUNCT;
    static const mask alnum 	= _C_UPPER | _C_LOWER | _C_NUMBER;
#if __cplusplus >= 201103L
    static const mask blank	= _C_WHITE_SPACE;
#endif
#else
    // Non-standard typedefs.
    typedef const short* 	__to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef short	mask;
    static const mask upper    	= _UP;
    static const mask lower 	= _LO;
    static const mask alpha 	= _UP|_LO|_XA;
    static const mask digit 	= _DI;
    static const mask xdigit 	= _XD;
    static const mask space 	= _CN|_SP|_XS;
    static const mask print 	= _DI|_LO|_PU|_SP|_UP|_XA;
    static const mask graph 	= _DI|_LO|_PU|_UP|_XA;
    static const mask cntrl 	= _BB;
    static const mask punct 	= _PU;
    static const mask alnum 	= _DI|_LO|_UP|_XA;
#if __cplusplus >= 201103L
    static const mask blank	= _SP|_XB;
#endif
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

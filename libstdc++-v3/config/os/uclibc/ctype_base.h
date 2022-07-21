// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/ctype_base.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

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
    // Note: In uClibc, the following two types depend on configuration.

    // Non-standard typedefs.
    typedef const __ctype_touplow_t* __to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    typedef __ctype_mask_t	mask;
    static const mask upper    	= _ISupper;
    static const mask lower 	= _ISlower;
    static const mask alpha 	= _ISalpha;
    static const mask digit 	= _ISdigit;
    static const mask xdigit 	= _ISxdigit;
    static const mask space 	= _ISspace;
    static const mask print 	= _ISprint;
    static const mask graph 	= _ISalpha | _ISdigit | _ISpunct;
    static const mask cntrl 	= _IScntrl;
    static const mask punct 	= _ISpunct;
    static const mask alnum 	= _ISalpha | _ISdigit;
#if __cplusplus >= 201103L
    static const mask blank	= _ISblank;
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

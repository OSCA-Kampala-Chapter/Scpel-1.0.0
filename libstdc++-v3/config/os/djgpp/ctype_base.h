// Locale support -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

//
// ISO C++ 14882: 22.1  Locales
//

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /// @brief  Base class for ctype.
  struct ctype_base
  {
    typedef unsigned short 	mask;

    // Non-standard typedefs.
    typedef unsigned char *     __to_type;

    // NB: Offsets into ctype<char>::_M_table force a particular size
    // on the mask type. Because of this, we don't use an enum.
    static const mask space = __dj_ISSPACE;	// Whitespace
    static const mask print = __dj_ISPRINT;	// Printing
    static const mask cntrl = __dj_ISCNTRL;	// Control character
    static const mask upper = __dj_ISUPPER;	// UPPERCASE
    static const mask lower = __dj_ISLOWER;	// lowercase
    static const mask alpha = __dj_ISALPHA;	// Alphabetic
    static const mask digit = __dj_ISDIGIT;	// Numeric
    static const mask punct = __dj_ISPUNCT;     // Punctuation
    static const mask xdigit = __dj_ISXDIGIT;   // Hexadecimal numeric
    static const mask alnum = __dj_ISALPHA | __dj_ISDIGIT;  // Alphanumeric
    static const mask graph = __dj_ISALPHA | __dj_ISDIGIT | __dj_ISPUNCT;  // Graphical
#if __cplusplus >= 201103L
    static const mask blank	= __dj_ISBLANK;
#endif
  };

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

// Wrapper for underlying C-language localization -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/c++locale.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{locale}
 */

//
// ISO C++ 14882: 22.8  Standard locale categories.
//

// Written by Benjamin Kosnik <bkoz@redhat.com>

#include <clocale>
#include <langinfo.h>		// For codecvt
#include <iconv.h>		// For codecvt using iconv, iconv_t
#include <nl_types.h> 		// For messages

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  typedef int*			__c_locale;

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace


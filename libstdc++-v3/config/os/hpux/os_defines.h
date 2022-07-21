// Specific definitions for HPUX  -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/os_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */

#ifndef _GLIBCXX_OS_DEFINES
#define _GLIBCXX_OS_DEFINES 1

// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

// Use macro form of ctype functions to ensure __SB_masks is defined.
#define _SB_CTYPE_MACROS 1

/* HP-UX, for reasons unknown choose to use a different name for
   the string to [unsigned] long long conversion routines.

   Furthermore, instead of having the prototypes in stdlib.h like
   everyone else, they put them into a non-standard header
   <inttypes.h>.  Ugh.

   <inttypes.h> defines a variety of things, some of which we
   probably do not want.  So we don't want to include it here.

   Luckily we can just declare strtoll and strtoull with the
   __asm extension which effectively renames calls at the
   source level without namespace pollution.

   Also note that the compiler defines _INCLUDE_LONGLONG for C++
   unconditionally, which makes intmax_t and uintmax_t long long
   types.

   We also force _GLIBCXX_USE_LONG_LONG here so that we don't have
   to bastardize configure to deal with this sillyness.  */

#ifdef __cplusplus
namespace std
{
  extern "C"
  {
#ifndef __LP64__
  __extension__ long long strtoll (const char *, char **, int)
    __asm  ("__strtoll");
  __extension__ unsigned long long strtoull (const char *, char **, int)
    __asm  ("__strtoull");
#else
  __extension__ long long strtoll (const char *, char **, int)
    __asm  ("strtol");
  __extension__ unsigned long long strtoull (const char *, char **, int)
    __asm  ("strtoul");
#endif
  }
} // namespace std
#endif // __cplusplus

#define _GLIBCXX_USE_LONG_LONG 1

// HPUX on IA64 requires vtable to be 64 bit aligned even at 32 bit
// mode.  We need to pad the vtable structure to achieve this.
#if !defined(_LP64) && defined (__ia64__)
#define _GLIBCXX_VTABLE_PADDING 8
typedef long int __padding_type;
#endif

// GCC on IA64 HP-UX uses the HP-UX system unwind library,
// it does not have the _Unwind_Resume_or_Rethrow entry point
// because that is not part of the standard IA64 Unwind ABI.
#if defined (__ia64__)
#define _LIBUNWIND_STD_ABI 1
#endif

/* Don't use pragma weak in gthread headers.  HP-UX rejects programs
   with unsatisfied external references even if all of those references
   are weak; gthread relies on such unsatisfied references being resolved
   to null pointers when weak symbol support is on.  */
#define _GLIBCXX_GTHREAD_USE_WEAK 0

// No support for referencing weak symbols without a definition.
#define _GLIBCXX_USE_WEAK_REF 0

// The strtold function is obsolete and not C99 conformant on PA HP-UX.
// It returns plus or minus _LDBL_MAX instead of plus or minus HUGE_VALL
// if the correct value would cause overflow.  It doesn't handle "inf",
// "infinity" and "nan".  It is not thread safe.
#if defined (__hppa__)
#define _GLIBCXX_HAVE_BROKEN_STRTOLD 1
#endif

// The vnsprintf function returns -1 when the buffer is too small.
// See PR libstdc++/68737.
#define _GLIBCXX_HAVE_BROKEN_VSNPRINTF 1

#endif

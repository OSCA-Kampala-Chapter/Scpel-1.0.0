// -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/**
 * @file detail/binomial_heap_/debug_fn_imps.hpp
 * Contains an implementation for binomial_heap_.
 */

#ifdef PB_DS_CLASS_C_DEC

#ifdef _GLIBCXX_DEBUG

PB_DS_CLASS_T_DEC
void
PB_DS_CLASS_C_DEC::
assert_valid(const char* __file, int __line) const
{ base_type::assert_valid(true, __file, __line); }

#endif 
#endif

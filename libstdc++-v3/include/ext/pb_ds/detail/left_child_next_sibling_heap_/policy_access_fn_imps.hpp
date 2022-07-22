// -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/**
 * @file left_child_next_sibling_heap_/policy_access_fn_imps.hpp
 * Contains an implementation class for left_child_next_sibling_heap_.
 */

#ifdef PB_DS_CLASS_C_DEC

PB_DS_CLASS_T_DEC
Cmp_Fn& 
PB_DS_CLASS_C_DEC::
get_cmp_fn()
{ return *this; }

PB_DS_CLASS_T_DEC
const Cmp_Fn& 
PB_DS_CLASS_C_DEC::
get_cmp_fn() const
{ return *this; }

#endif

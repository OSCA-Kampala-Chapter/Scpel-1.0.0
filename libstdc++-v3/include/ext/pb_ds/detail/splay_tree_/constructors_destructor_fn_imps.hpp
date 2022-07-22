// -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/**
 * @file splay_tree_/constructors_destructor_fn_imps.hpp
 * Contains an implementation class for splay_tree_.
 */

#ifdef PB_DS_CLASS_C_DEC

PB_DS_CLASS_T_DEC
template<typename It>
void
PB_DS_CLASS_C_DEC::
copy_from_range(It first_it, It last_it)
{
  while (first_it != last_it)
    insert(*(first_it++));
}

PB_DS_CLASS_T_DEC
PB_DS_CLASS_C_DEC::
PB_DS_S_TREE_NAME()
{
  initialize();
  PB_DS_ASSERT_VALID((*this))
}

PB_DS_CLASS_T_DEC
PB_DS_CLASS_C_DEC::
PB_DS_S_TREE_NAME(const Cmp_Fn& r_cmp_fn) :
  base_type(r_cmp_fn)
{
  initialize();
  PB_DS_ASSERT_VALID((*this))
}

PB_DS_CLASS_T_DEC
PB_DS_CLASS_C_DEC::
PB_DS_S_TREE_NAME(const Cmp_Fn& r_cmp_fn, const node_update& r_node_update) :
  base_type(r_cmp_fn, r_node_update)
{
  initialize();
  PB_DS_ASSERT_VALID((*this))
}

PB_DS_CLASS_T_DEC
PB_DS_CLASS_C_DEC::
PB_DS_S_TREE_NAME(const PB_DS_CLASS_C_DEC& other) :
  base_type(other)
{
  initialize();
  PB_DS_ASSERT_VALID((*this))
}

PB_DS_CLASS_T_DEC
void
PB_DS_CLASS_C_DEC::
swap(PB_DS_CLASS_C_DEC& other)
{
  PB_DS_ASSERT_VALID((*this))
  PB_DS_ASSERT_VALID(other)
  base_type::swap(other);
  PB_DS_ASSERT_VALID((*this))
  PB_DS_ASSERT_VALID(other)
}

PB_DS_CLASS_T_DEC
void
PB_DS_CLASS_C_DEC::
initialize()
{ base_type::m_p_head->m_special = true; }
#endif

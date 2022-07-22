// -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/**
 * @file bin_search_tree_/erase_fn_imps.hpp
 * Contains an implementation class for bin_search_tree_.
 */

#ifdef PB_DS_CLASS_C_DEC

PB_DS_CLASS_T_DEC
inline void
PB_DS_CLASS_C_DEC::
actual_erase_node(node_pointer p_z)
{
  _GLIBCXX_DEBUG_ASSERT(m_size > 0);
  --m_size;
  _GLIBCXX_DEBUG_ONLY(debug_base::erase_existing(PB_DS_V2F(p_z->m_value));)
  p_z->~node();
  s_node_allocator.deallocate(p_z, 1);
}

PB_DS_CLASS_T_DEC
inline void
PB_DS_CLASS_C_DEC::
update_min_max_for_erased_node(node_pointer p_z)
{
  if (m_size == 1)
    {
      m_p_head->m_p_left = m_p_head->m_p_right = m_p_head;
      return;
    }

  if (m_p_head->m_p_left == p_z)
    {
      iterator it(p_z);
      ++it;
      m_p_head->m_p_left = it.m_p_nd;
    }
  else if (m_p_head->m_p_right == p_z)
    {
      iterator it(p_z);
      --it;
      m_p_head->m_p_right = it.m_p_nd;
    }
}

PB_DS_CLASS_T_DEC
void
PB_DS_CLASS_C_DEC::
clear()
{
  PB_DS_STRUCT_ONLY_ASSERT_VALID((*this))
  clear_imp(m_p_head->m_p_parent);
  m_size = 0;
  initialize();
  _GLIBCXX_DEBUG_ONLY(debug_base::clear();)
  PB_DS_STRUCT_ONLY_ASSERT_VALID((*this))
}

PB_DS_CLASS_T_DEC
void
PB_DS_CLASS_C_DEC::
clear_imp(node_pointer p_nd)
{
  if (p_nd == 0)
    return;

  clear_imp(p_nd->m_p_left);
  clear_imp(p_nd->m_p_right);
  p_nd->~node();
  s_node_allocator.deallocate(p_nd, 1);
}
#endif

/* Header file for tree-ssa-coalesce.cc exports.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef GCC_TREE_SSA_COALESCE_H
#define GCC_TREE_SSA_COALESCE_H

extern void coalesce_ssa_name (var_map);
extern bool gimple_can_coalesce_p (tree, tree);

#endif /* GCC_TREE_SSA_COALESCE_H */

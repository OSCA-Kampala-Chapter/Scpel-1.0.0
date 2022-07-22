# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em.  It is used by targets for
# which relaxation is not just an optimization, but for correctness.

LDEMUL_BEFORE_ALLOCATION=need_relax_${EMULATION_NAME}_before_allocation

fragment <<EOF

static void
need_relax_${EMULATION_NAME}_before_allocation (void)
{
  /* Call main function; we're just extending it.  */
  gld${EMULATION_NAME}_before_allocation ();

  /* Force -relax on if not doing a relocatable link.  */
  if (!bfd_link_relocatable (&link_info))
    ENABLE_RELAXATION;
}
EOF

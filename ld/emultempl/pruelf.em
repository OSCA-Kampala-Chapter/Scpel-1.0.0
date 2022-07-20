# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em, and defines extra pru-elf
# specific routines.
#
fragment <<EOF

#include "ldctor.h"

/* This is called after the sections have been attached to output
   sections, but before any sizes or addresses have been set.  */

static void
pruelf_before_allocation (void)
{
  /* Call the default first.  */
  gld${EMULATION_NAME}_before_allocation ();

  /* Enable relaxation by default if the "--no-relax" option was not
     specified.  This is done here instead of in the before_parse hook
     because there is a check in main() to prohibit use of --relax and
     -r together.  */
  if (RELAXATION_DISABLED_BY_DEFAULT)
    ENABLE_RELAXATION;
}

EOF

# Put these extra pru-elf routines in ld_${EMULATION_NAME}_emulation
#
LDEMUL_BEFORE_ALLOCATION=pruelf_before_allocation

# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em, and defines extra crx-elf
# specific routines.
#
fragment <<EOF

#include "ldctor.h"

static void
crxelf_after_parse (void)
{
  /* Always behave as if called with --sort-common command line
     option.
     This is to emulate the CRTools' method of keeping variables
     of different alignment in separate sections.  */
  config.sort_common = true;

  /* Don't create a demand-paged executable, since this feature isn't
     meaninful in CRX embedded systems. Moreover, when magic_demand_paged
     is true the link sometimes fails.  */
  config.magic_demand_paged = false;

  ldelf_after_parse ();
}

/* This is called after the sections have been attached to output
   sections, but before any sizes or addresses have been set.  */

static void
crxelf_before_allocation (void)
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

# Put these extra crx-elf routines in ld_${EMULATION_NAME}_emulation
#
LDEMUL_AFTER_PARSE=crxelf_after_parse
LDEMUL_BEFORE_ALLOCATION=crxelf_before_allocation

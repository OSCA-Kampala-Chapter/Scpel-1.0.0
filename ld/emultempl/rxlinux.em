# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em, and defines extra rx-elf
# specific routines.
#
test -z "$TARGET2_TYPE" && TARGET2_TYPE="rel"
fragment <<EOF

#include "elf32-rx.h"

/* This is a convenient point to tell BFD about target specific flags.
   After the output has been created, but before inputs are read.  */
static void
rx_linux_create_output_section_statements (void)
{
  extern void bfd_elf32_rx_set_target_flags (bool, bool);

  bfd_elf32_rx_set_target_flags (false, false);
}

EOF
LDEMUL_CREATE_OUTPUT_SECTION_STATEMENTS=rx_linux_create_output_section_statements


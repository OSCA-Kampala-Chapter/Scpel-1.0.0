# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em, and defines extra ia64-elf
# specific routines.
#
# Define some shell vars to insert bits of code into the standard elf
# parse_args and list_options functions.
#
fragment <<EOF

#include "elfxx-ia64.h"

/* None zero if generating binary for Intel Itanium processor.  */
static int itanium = 0;

static void
ia64elf_after_parse (void)
{
  link_info.relax_pass = 2;
  bfd_elf${ELFSIZE}_ia64_after_parse (itanium);

  ldelf_after_parse ();
}

EOF

PARSE_AND_LIST_PROLOGUE='
#define OPTION_ITANIUM			300
'

PARSE_AND_LIST_LONGOPTS='
    { "itanium", no_argument, NULL, OPTION_ITANIUM},
'

PARSE_AND_LIST_OPTIONS='
  fprintf (file, _("\
  --itanium                   Generate code for Intel Itanium processor\n"
		   ));
'

PARSE_AND_LIST_ARGS_CASES='
    case OPTION_ITANIUM:
      itanium = 1;
      break;
'

LDEMUL_AFTER_PARSE=ia64elf_after_parse
source_em ${srcdir}/emultempl/needrelax.em

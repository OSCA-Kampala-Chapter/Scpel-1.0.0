# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf-generic.em, and defines S/390
# specific routines.
#
fragment <<EOF

#include "ldctor.h"
#include "elf-s390.h"

static struct s390_elf_params params = { 0 };

/* This is a convenient point to tell BFD about target specific flags.
   After the output has been created, but before inputs are read.  */
static void
s390_elf_create_output_section_statements (void)
{
  if (!bfd_elf_s390_set_options (&link_info, &params))
    einfo (_("%F%P: can not init BFD: %E\n"));
}

EOF

# Define some shell vars to insert bits of code into the standard elf
# parse_args and list_options functions.
#
PARSE_AND_LIST_PROLOGUE='
#define OPTION_PGSTE	301
'

PARSE_AND_LIST_LONGOPTS='
  { "s390-pgste", no_argument, NULL, OPTION_PGSTE},
'

PARSE_AND_LIST_OPTIONS='
  fprintf (file, _("  --s390-pgste                Tell the kernel to "
		   "allocate 4k page tables\n"));
'

PARSE_AND_LIST_ARGS_CASES='
    case OPTION_PGSTE:
      params.pgste = 1;
      break;
'

LDEMUL_CREATE_OUTPUT_SECTION_STATEMENTS=s390_elf_create_output_section_statements

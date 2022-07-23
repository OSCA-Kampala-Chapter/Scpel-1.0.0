# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em, and defines extra bfin-elf
# specific routines.
#
fragment <<EOF

#include "elf-bfd.h"
#include "elf32-bfin.h"

/* Whether to put code in Blackfin L1 SRAM.  */
extern bool elf32_bfin_code_in_l1;

/* Whether to put (writable) data in Blackfin L1 SRAM.  */
extern bool elf32_bfin_data_in_l1;

EOF


# Define some shell vars to insert bits of code into the standard elf
# parse_args and list_options functions.
#
PARSE_AND_LIST_PROLOGUE='
#define OPTION_CODE_IN_L1		300
#define OPTION_DATA_IN_L1		301
'

PARSE_AND_LIST_LONGOPTS='
  { "code-in-l1", no_argument, NULL, OPTION_CODE_IN_L1 },
  { "data-in-l1", no_argument, NULL, OPTION_DATA_IN_L1 },
'

PARSE_AND_LIST_OPTIONS='
  fprintf (file, _("\
  --code-in-l1                Put code in L1\n"));
  fprintf (file, _("\
  --data-in-l1                Put data in L1\n"));
'

PARSE_AND_LIST_ARGS_CASES='
    case OPTION_CODE_IN_L1:
      elf32_bfin_code_in_l1 = true;
      break;
    case OPTION_DATA_IN_L1:
      elf32_bfin_data_in_l1 = true;
      break;
'

# This shell script emits a C file. -*- C -*-
# It does some substitutions.
fragment <<EOF
/* A vanilla emulation with no defaults
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "sysdep.h"
#include "bfd.h"
#include "bfdlink.h"
#include "ctf-api.h"

#include "ld.h"
#include "ldmisc.h"
#include "ldmain.h"

#include "ldexp.h"
#include "ldlang.h"
#include "ldfile.h"
#include "ldemul.h"

static void vanilla_before_parse (void)
{
}

static void
vanilla_set_output_arch (void)
{
  /* Set the output architecture and machine if possible */
  unsigned long  machine = 0;
  bfd_set_arch_mach (link_info.output_bfd,
		     ldfile_output_architecture, machine);
}

static char *
vanilla_get_script (int *isfile)
{
  *isfile = 0;
  return "";
}

struct ld_emulation_xfer_struct ld_vanilla_emulation =
{
  vanilla_before_parse,
  syslib_default,
  hll_default,
  after_parse_default,
  after_open_default,
  after_check_relocs_default,
  before_place_orphans_default,
  after_allocation_default,
  vanilla_set_output_arch,
  ldemul_default_target,
  before_allocation_default,
  vanilla_get_script,
  "vanilla",
  "a.out-sunos-big",
  finish_default,
  NULL,	/* create output section statements */
  NULL,	/* open dynamic archive */
  NULL,	/* place orphan */
  NULL,	/* set symbols */
  NULL,	/* parse args */
  NULL,	/* add_options */
  NULL,	/* handle_option */
  NULL,	/* unrecognized file */
  NULL,	/* list options */
  NULL,	/* recognized file */
  NULL,	/* find_potential_libraries */
  NULL,	/* new_vers_pattern */
  NULL,	/* extra_map_file_text */
  NULL, /* emit_ctf_early */
  NULL, /* acquire_strings_for_ctf */
  NULL, /* new_dynsym_for_ctf */
  NULL  /* print_symbol */
};
EOF

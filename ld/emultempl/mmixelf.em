# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em and used to define MMIX and ELF
# specific things.  First include what we have in common with mmo.

source_em ${srcdir}/emultempl/mmix-elfnmmo.em

fragment <<EOF

static void
elfmmix_before_parse (void)
{
  mmix_before_parse ();

  /* Make sure we don't create a demand-paged executable.  Unfortunately
     this isn't changeable with a command-line option.  It makes no
     difference to mmo, but the sections in elf64mmix will be aligned to a
     page in the linked file, which is non-intuitive.  If there's ever a
     full system with shared libraries and demand paging, you will want to
     exclude this file.  */
  config.magic_demand_paged = false;

  config.separate_code = `if test "x${SEPARATE_CODE}" = xyes ; then echo true ; else echo false ; fi`;
}
EOF

LDEMUL_BEFORE_PARSE=elfmmix_before_parse

# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em, and defines extra irix specific
# functions.

fragment <<EOF

/* The native IRIX linker will always create a DT_SONAME for shared objects.
   While this shouldn't really be necessary for ABI conformance, some versions
   of the native linker will segfault if the tag is missing.  */

static void
irix_after_open (void)
{
  if (bfd_link_dll (&link_info) && command_line.soname == 0)
    command_line.soname
      = (char *) lbasename (bfd_get_filename (link_info.output_bfd));

  gld${EMULATION_NAME}_after_open ();
}
EOF

LDEMUL_AFTER_OPEN=irix_after_open
source_em "${srcdir}/emultempl/mipself.em"

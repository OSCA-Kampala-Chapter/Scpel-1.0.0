# This shell script emits C code -*- C -*-
# to keep track of the machine type of Z80 object files
# It does some substitutions.
# Please review $(srcdir/SPL-README) for GNU licencing info.

if [ x"${EMULATION_NAME}" = x"elf32z80" ]; then
  fragment <<EOF
#include "elf/z80.h"
EOF
else
  fragment <<EOF
static void
gld${EMULATION_NAME}_after_open (void)
{
}
EOF
fi

fragment <<EOF
/* --- \begin{z80.em} */

/* Set the machine type of the output file based on types of inputs.  */
static void
z80_after_open (void)
{
  bfd *abfd;

  /* For now, make sure all object files are of the same architecture.
     We may try to merge object files with different architecture together.  */
  for (abfd = link_info.input_bfds; abfd != NULL; abfd = abfd->link.next)
    {
      const bfd_arch_info_type *info;
      info = bfd_arch_get_compatible (link_info.output_bfd, abfd, false);
      if (info == NULL)
	einfo (_("%F%P: %pB: Instruction sets of object files incompatible\n"),
	       abfd);
      else
        bfd_set_arch_info (link_info.output_bfd, info);
    }

  /* Call the standard elf routine.  */
  gld${EMULATION_NAME}_after_open ();
}

/* --- \end{z80.em} */
EOF

LDEMUL_AFTER_OPEN=z80_after_open

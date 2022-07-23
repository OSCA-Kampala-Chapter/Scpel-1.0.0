# This shell script emits a C file. -*- C -*-
# Please review $(srcdir/SPL-README) for GNU licencing info.
#

# This file is sourced from elf.em and from ELF targets that use
# generic.em.
#
fragment <<EOF

EOF
# Put these extra routines in ld${EMULATION_NAME}_emulation
#
LDEMUL_EMIT_CTF_EARLY=ldelf_emit_ctf_early
LDEMUL_ACQUIRE_STRINGS_FOR_CTF=ldelf_acquire_strings_for_ctf
LDEMUL_NEW_DYNSYM_FOR_CTF=ldelf_new_dynsym_for_ctf

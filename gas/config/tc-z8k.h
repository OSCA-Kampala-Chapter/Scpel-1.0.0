/* This file is tc-z8k.h
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_Z8K
#define TARGET_BYTES_BIG_ENDIAN 1
#define TARGET_ARCH    bfd_arch_z8k
#define TARGET_FORMAT  "coff-z8k"

struct internal_reloc;

#define WORKING_DOT_WORD

#define COFF_MAGIC 0x8000
#define IGNORE_NONSTANDARD_ESCAPES
#undef WARN_SIGNED_OVERFLOW_WORD

#define tc_fix_adjustable(X)  0

#define LISTING_HEADER "Zilog Z8000 GAS "
#define RELOC_32 1234

#define md_operand(x)

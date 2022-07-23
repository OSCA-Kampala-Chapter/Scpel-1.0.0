/* tc-mn10200.h -- Header file for tc-mn10200.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_MN10200

#define TARGET_BYTES_BIG_ENDIAN 0

/* The target BFD architecture.  */
#define TARGET_ARCH bfd_arch_mn10200

#define TARGET_FORMAT "elf32-mn10200"

#define md_operand(x)

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define md_number_to_chars number_to_chars_littleendian

/* Don't bother to adjust relocs.  */
#define tc_fix_adjustable(FIX) 0

/* We do relaxing in the assembler as well as the linker.  */
extern const struct relax_type md_relax_table[];
#define TC_GENERIC_RELAX_TABLE md_relax_table


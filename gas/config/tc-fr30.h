/* tc-fr30.h -- Header file for tc-fr30.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_FR30

#define LISTING_HEADER "FR30 GAS "

/* The target BFD architecture.  */
#define TARGET_ARCH bfd_arch_fr30

#define TARGET_FORMAT "elf32-fr30"

#define TARGET_BYTES_BIG_ENDIAN 1

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

#define DIFF_EXPR_OK		/* .-foo gets turned into PC relative relocs.  */

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define md_apply_fix gas_cgen_md_apply_fix

#define tc_fix_adjustable(FIX) fr30_fix_adjustable (FIX)
struct fix;
extern bool fr30_fix_adjustable (struct fix *);

#define tc_gen_reloc gas_cgen_tc_gen_reloc

/* Call md_pcrel_from_section(), not md_pcrel_from().  */
#define MD_PCREL_FROM_SECTION(FIX, SEC) md_pcrel_from_section (FIX, SEC)

/* For 8 vs 16 vs 32 bit branch selection.  */
#define TC_GENERIC_RELAX_TABLE md_relax_table
extern const struct relax_type md_relax_table[];

/* We need a special version of the TC_START_LABEL macro so that we
   allow the LDI:8, LDI:20, LDI:32 and delay slot instructions to be
   parsed as such.  We need to be able to change the contents of the
   var storing what was at the NUL delimiter.  */
#define TC_START_LABEL(STR, NUL_CHAR, NEXT_CHAR)		\
  (NEXT_CHAR == ':' && !fr30_is_colon_insn (STR, &NUL_CHAR))
extern int fr30_is_colon_insn (char *, char *);

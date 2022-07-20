/* tc-mt.h -- Header file for tc-mt.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_MT

#define LISTING_HEADER "MT GAS "

/* The target BFD architecture.  */
#define TARGET_ARCH bfd_arch_mt

#define TARGET_FORMAT "elf32-mt"

#define TARGET_BYTES_BIG_ENDIAN 1

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

/* .-foo gets turned into PC relative relocs.  */
#define DIFF_EXPR_OK

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

/* All mt instructions are multiples of 32 bits.  */
#define DWARF2_LINE_MIN_INSN_LENGTH 4

#define LITERAL_PREFIXPERCENT_BIN

#define md_apply_fix mt_apply_fix
extern void mt_apply_fix (struct fix *, valueT *, segT);

/* Call md_pcrel_from_section(), not md_pcrel_from().  */
#define MD_PCREL_FROM_SECTION(FIXP, SEC) md_pcrel_from_section (FIXP, SEC)

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define tc_gen_reloc gas_cgen_tc_gen_reloc

#define md_operand(x) gas_cgen_md_operand (x)
extern void gas_cgen_md_operand (expressionS *);

#define TC_FORCE_RELOCATION(fixp) mt_force_relocation (fixp)
extern int mt_force_relocation (struct fix *);

#define tc_fix_adjustable(fixP) mt_fix_adjustable (fixP)
extern bool mt_fix_adjustable (struct fix *);


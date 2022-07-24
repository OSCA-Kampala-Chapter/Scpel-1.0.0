/* tc-iq2000.h -- Header file for tc-iq2000.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_IQ2000

#define LISTING_HEADER "IQ2000 GAS "

/* The target BFD architecture.  */
#define TARGET_ARCH bfd_arch_iq2000

#define TARGET_FORMAT "elf32-iq2000"

#define TARGET_BYTES_BIG_ENDIAN 1

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

/* .-foo gets turned into PC relative relocs.  */
#define DIFF_EXPR_OK

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define md_apply_fix gas_cgen_md_apply_fix

/* Call md_pcrel_from_section(), not md_pcrel_from().  */
#define MD_PCREL_FROM_SECTION(FIXP, SEC) md_pcrel_from_section (FIXP, SEC)

#define tc_frob_file() iq2000_frob_file ()

/* After creating a fixup for an instruction operand, we need to check
   for HI16 relocs and queue them up for later sorting.  */
#define md_cgen_record_fixup_exp  iq2000_cgen_record_fixup_exp

/* When relaxing, we need to emit various relocs we otherwise wouldn't.  */
#define TC_FORCE_RELOCATION(fix) iq2000_force_relocation (fix)

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define tc_gen_reloc gas_cgen_tc_gen_reloc

extern void iq2000_frob_file (void);
extern bool iq2000_fix_adjustable (struct fix *);
extern int iq2000_force_relocation (struct fix *);

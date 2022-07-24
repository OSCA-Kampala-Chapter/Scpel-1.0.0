/* tc-ip2k.h -- Header file for tc-ip2k.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_IP2K

#define LISTING_HEADER "IP2xxx GAS "

/* The target BFD architecture.  */
#define TARGET_ARCH bfd_arch_ip2k

#define TARGET_FORMAT "elf32-ip2k"

#define TARGET_BYTES_BIG_ENDIAN 1

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

/* .-foo gets turned into PC relative relocs.  */
#define DIFF_EXPR_OK

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define LITERAL_PREFIXPERCENT_BIN
#define DOUBLESLASH_LINE_COMMENTS

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define md_apply_fix ip2k_apply_fix

#define TC_HANDLES_FX_DONE

/* No shared lib support, so we don't need to ensure externally
   visible symbols can be overridden.  */
#define EXTERN_FORCE_RELOC 0

#define TC_FORCE_RELOCATION(FIX) ip2k_force_relocation (FIX)
extern int ip2k_force_relocation (struct fix *);

#define tc_gen_reloc gas_cgen_tc_gen_reloc

#define md_elf_section_flags ip2k_elf_section_flags
extern int ip2k_elf_section_flags (flagword, bfd_vma, int);

#define md_operand(x) gas_cgen_md_operand (x)
extern void gas_cgen_md_operand (expressionS *);

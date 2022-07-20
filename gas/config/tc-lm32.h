/* tc-lm32.h -- Header file for tc-lm32.c
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef TC_LM32_H
#define TC_LM32_H

#define TARGET_FORMAT "elf32-lm32"
#define TARGET_ARCH bfd_arch_lm32
#define TARGET_MACH bfd_mach_lm32

#define TARGET_BYTES_BIG_ENDIAN 1

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

#define WORKING_DOT_WORD

/* Values passed to md_apply_fix3 don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define md_operand(X)
#define tc_gen_reloc gas_cgen_tc_gen_reloc

/* Call md_pcrel_from_section(), not md_pcrel_from().  */
#define MD_PCREL_FROM_SECTION(FIXP, SEC) md_pcrel_from_section (FIXP, SEC)

extern bool lm32_fix_adjustable (struct fix *);
#define tc_fix_adjustable(FIX) lm32_fix_adjustable (FIX)

#endif /* TC_LM32_H */


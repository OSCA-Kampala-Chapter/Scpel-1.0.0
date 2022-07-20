/* tc-cr16.h -- Header file for tc-cr16.c, the CR16 GAS port.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef TC_CR16_H
#define TC_CR16_H

#define TC_CR16 1

#define TARGET_BYTES_BIG_ENDIAN 0

#define GLOBAL_OFFSET_TABLE_NAME "_GLOBAL_OFFSET_TABLE_"

#define TARGET_FORMAT "elf32-cr16"
#define TARGET_ARCH   bfd_arch_cr16

#define WORKING_DOT_WORD
#define LOCAL_LABEL_PREFIX '.'

#define md_number_to_chars      number_to_chars_littleendian

/* We do relaxing in the assembler as well as the linker.  */
extern const struct relax_type md_relax_table[];
#define TC_GENERIC_RELAX_TABLE md_relax_table

/* We do not want to adjust any relocations to make implementation of
   linker relaxations easier.  */
#define tc_fix_adjustable(fixP)  0

/* We need to force out some relocations when relaxing.  */
#define TC_FORCE_RELOCATION(FIXP) cr16_force_relocation (FIXP)
extern int cr16_force_relocation (struct fix *);

/* Fixup non-code sections since we will never relax them.  */
#define TC_LINKRELAX_FIXUP(seg) \
  ((seg->flags & (SEC_ALLOC | SEC_CODE)) == (SEC_ALLOC | SEC_CODE))

/* CR16 instructions, with operands included, are a multiple
   of two bytes long.  */
#define DWARF2_LINE_MIN_INSN_LENGTH 2

extern void cr16_cons_fix_new (struct frag *, int, int, struct expressionS *,
			       bfd_reloc_code_real_type);
/* This is called by emit_expr when creating a reloc for a cons.
   We could use the definition there, except that we want to handle
   the CR16 reloc type specially, rather than the BFD_RELOC type.  */
#define TC_CONS_FIX_NEW(FRAG, OFF, LEN, EXP, RELOC)	\
  cr16_cons_fix_new (FRAG, OFF, LEN, EXP, RELOC)

/* Give an error if a frag containing code is not aligned to a 2-byte
   boundary.  */
#define md_frag_check(FRAGP) \
  if ((FRAGP)->has_code                                                \
      && (((FRAGP)->fr_address + (FRAGP)->insn_addr) & 1) != 0)        \
     as_bad_where ((FRAGP)->fr_file, (FRAGP)->fr_line,                 \
                  _("instruction address is not a multiple of 2"));

#endif /* TC_CR16_H */

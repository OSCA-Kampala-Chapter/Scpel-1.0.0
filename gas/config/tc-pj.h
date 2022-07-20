/* This file is tc-pj.h
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define WORKING_DOT_WORD
#define IGNORE_NONSTANDARD_ESCAPES
#define TARGET_ARCH bfd_arch_pj
#define TARGET_FORMAT (target_big_endian ? "elf32-pj" : "elf32-pjl")
#define LISTING_HEADER                    				\
  (target_big_endian                      				\
   ? "Pico Java GAS Big Endian"           				\
   : "Pico Java GAS Little Endian")

void pj_cons_fix_new_pj (struct frag *, int, int, expressionS *,
			 bfd_reloc_code_real_type);
arelent *tc_gen_reloc (asection *, struct fix *);

#define md_section_align(SEGMENT, SIZE)     (SIZE)
#define md_convert_frag(B, S, F)            as_fatal (_("convert_frag\n"))
#define md_estimate_size_before_relax(A, B) (as_fatal (_("estimate size\n")),0)
#define md_undefined_symbol(NAME)           0

/* PC relative operands are relative to the start of the opcode, and
   the operand is always one byte into the opcode.  */

#define md_pcrel_from(FIX) 						\
	((FIX)->fx_where + (FIX)->fx_frag->fr_address - 1)

#define TC_CONS_FIX_NEW(FRAG, WHERE, NBYTES, EXP, RELOC)	\
	pj_cons_fix_new_pj (FRAG, WHERE, NBYTES, EXP, RELOC)

/* No shared lib support, so we don't need to ensure externally
   visible symbols can be overridden.  */
#define EXTERN_FORCE_RELOC 0

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define tc_fix_adjustable(FIX) 					\
          (! ((FIX)->fx_r_type == BFD_RELOC_VTABLE_INHERIT     	\
	   || (FIX)->fx_r_type == BFD_RELOC_VTABLE_ENTRY))

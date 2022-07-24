/* tc-vax.h -- Header file for tc-vax.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_VAX 1

#define TARGET_BYTES_BIG_ENDIAN 0

#ifdef OBJ_AOUT
#ifdef TE_NetBSD
#define TARGET_FORMAT "a.out-vax-netbsd"
#endif
#ifndef TARGET_FORMAT
#define TARGET_FORMAT "a.out-vax-bsd"
#endif
#endif

#ifdef OBJ_VMS
#define TARGET_FORMAT "vms-vax"
#endif

#ifdef OBJ_ELF
#define TARGET_FORMAT "elf32-vax"
#endif

#define TARGET_ARCH	bfd_arch_vax

#define NO_RELOC	BFD_RELOC_NONE
#define NOP_OPCODE	0x01

#define md_operand(x)

#ifdef OBJ_ELF
#define TC_PARSE_CONS_EXPRESSION(EXP, NBYTES) vax_cons (EXP, NBYTES)
#define TC_CONS_FIX_NEW vax_cons_fix_new
bfd_reloc_code_real_type vax_cons (expressionS *, int);
void vax_cons_fix_new (struct frag *, int, unsigned int, struct expressionS *,
		       bfd_reloc_code_real_type);
#endif

extern const struct relax_type md_relax_table[];
#define TC_GENERIC_RELAX_TABLE md_relax_table

/* Values passed to md_apply_fix don't include symbol values.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define tc_fix_adjustable(FIX)					\
	((FIX)->fx_r_type != BFD_RELOC_VTABLE_INHERIT		\
	 && (FIX)->fx_r_type != BFD_RELOC_32_PLT_PCREL		\
	 && (FIX)->fx_r_type != BFD_RELOC_32_GOT_PCREL		\
	 && (FIX)->fx_r_type != BFD_RELOC_VTABLE_ENTRY		\
	 && ((FIX)->fx_pcrel					\
	     || ((FIX)->fx_subsy != NULL			\
		 && (S_GET_SEGMENT ((FIX)->fx_subsy)		\
		     == S_GET_SEGMENT ((FIX)->fx_addsy)))	\
	     || S_IS_LOCAL ((FIX)->fx_addsy)))

/*
 * Local Variables:
 * comment-column: 0
 * fill-column: 131
 * End:
 */

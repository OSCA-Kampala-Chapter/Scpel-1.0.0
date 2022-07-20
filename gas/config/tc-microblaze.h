/* tc-microblaze.h -- Header file for tc-microblaze.c.

   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef	TC_MICROBLAZE
#define TC_MICROBLAZE 1

#define TARGET_ARCH	bfd_arch_microblaze
#ifndef TARGET_BYTES_BIG_ENDIAN
/* Used to initialise target_big_endian.  */
#define TARGET_BYTES_BIG_ENDIAN 1
#endif

#define IGNORE_NONSTANDARD_ESCAPES

#define TC_RELOC_MANGLE(a,b,c) tc_reloc_mangle (a, b, c)

/* We need to handle expressions of type "symbol op symbol" and create
   relocs for such expressions as -relax in linker can change the value
   of such expressions */
#define TC_CONS_FIX_NEW cons_fix_new_microblaze
#define TC_PARSE_CONS_EXPRESSION(EXP, NBYTES) \
  parse_cons_expression_microblaze (EXP, NBYTES)
extern bfd_reloc_code_real_type parse_cons_expression_microblaze
  (expressionS *, int);

#define TC_FORCE_RELOCATION_SECTION(FIXP,SEG) 1
#define UNDEFINED_DIFFERENCE_OK 1

#define TC_FORCE_RELOCATION_LOCAL(FIX)				\
  (GENERIC_FORCE_RELOCATION_LOCAL (FIX)				\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_64_GOT		\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_64_PLT		\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_64_GOTOFF	\
   || (FIX)->fx_r_type == BFD_RELOC_MICROBLAZE_32_GOTOFF)

#define TC_VALIDATE_FIX_SUB(FIX, SEG) \
  (md_register_arithmetic || (SEG) != reg_section)

#define tc_fix_adjustable(X)  tc_microblaze_fix_adjustable(X)
extern int tc_microblaze_fix_adjustable (struct fix *);

extern const struct relax_type md_relax_table[];
#define TC_GENERIC_RELAX_TABLE md_relax_table

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define LISTING_HEADER        	"Xilinx MicroBlaze GAS Listing"
#define LISTING_LHS_CONT_LINES	4

#define NEED_FX_R_TYPE	1

/* We want local label support.  */
#define LOCAL_LABELS_FB 1

/* Want the section information too... */
#define MD_PCREL_FROM_SECTION(FIXP, SEC) md_pcrel_from_section (FIXP, SEC)

#define MD_APPLY_FIX3  /* We want the segment as well.  */

/* We set the fx_done field appropriately in md_apply_fix.  */
#define TC_HANDLES_FX_DONE

#ifdef OBJ_ELF

#define TARGET_FORMAT (target_big_endian ? "elf32-microblaze" : "elf32-microblazeel")

#define ELF_TC_SPECIAL_SECTIONS \
  { ".sdata",		SHT_PROGBITS,	SHF_ALLOC + SHF_WRITE }, \
  { ".sbss",		SHT_NOBITS,	SHF_ALLOC + SHF_WRITE }, \
  { ".sdata2",		SHT_PROGBITS,	SHF_ALLOC }, \
  { ".sbss2",		SHT_PROGBITS,	SHF_ALLOC }, \
/* Other special sections not generated by the assembler: .reginfo,
   .liblist, .conflict, .gptab, .got, .dynamic, .rel.dyn.  */

#endif /* OBJ_ELF */

#ifndef TARGET_FORMAT
# error No target format specified.
#endif

extern void 	 cons_fix_new_microblaze       (fragS *, int, int,
						expressionS *,
						bfd_reloc_code_real_type);
#define EXTERN_FORCE_RELOC -1

#endif /* TC_MICROBLAZE */

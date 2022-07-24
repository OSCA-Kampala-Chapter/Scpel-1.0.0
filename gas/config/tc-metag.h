/* tc-metag.h -- Header file for tc-metag.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_METAG

#define LISTING_HEADER "META GAS "

/* The target BFD architecture.  */
#define TARGET_ARCH bfd_arch_metag

#define TARGET_FORMAT "elf32-metag"

#define TARGET_BYTES_BIG_ENDIAN 0

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

#define DIFF_EXPR_OK		/* foo-. gets turned into PC relative relocs */

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

#define tc_fix_adjustable(FIX) metag_fix_adjustable (FIX)
extern bool metag_fix_adjustable (struct fix *);

#define TC_FORCE_RELOCATION(fix) metag_force_relocation (fix)
extern int metag_force_relocation (struct fix *);

#define TC_HANDLES_FX_DONE

/* Call md_pcrel_from_section(), not md_pcrel_from().  */
#define MD_PCREL_FROM_SECTION(FIX, SEC) md_pcrel_from_section (FIX, SEC)

#define HANDLE_ALIGN(fragp) metag_handle_align (fragp)
extern void metag_handle_align (struct frag *);

#define DWARF2_LINE_MIN_INSN_LENGTH 1

#define md_parse_name(name, exprP, mode, nextcharP) \
  metag_parse_name ((name), (exprP), (mode), (nextcharP))
extern int metag_parse_name (char const *, expressionS *, enum expr_mode, char *);

/* This is used to construct expressions out of @GOTOFF, @PLT and @GOT
   symbols.  The relocation type is stored in X_md.  */
#define O_PIC_reloc O_md1

#define TC_CASE_SENSITIVE

extern const char       metag_symbol_chars[];
#define tc_symbol_chars metag_symbol_chars

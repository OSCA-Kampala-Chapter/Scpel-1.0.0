/* tc-310v.h -- Header file for tc-d30v.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_D30V

/* The target BFD architecture.  */
#define TARGET_ARCH              bfd_arch_d30v
#define TARGET_FORMAT            "elf32-d30v"
#define TARGET_BYTES_BIG_ENDIAN  1

#define md_operand(x)

/* Call md_pcrel_from_section, not md_pcrel_from.  */
#define MD_PCREL_FROM_SECTION(FIX, SEC) md_pcrel_from_section (FIX, SEC)

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

/* .-foo gets turned into PC relative relocs.  */
#define DIFF_EXPR_OK

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define md_number_to_chars           number_to_chars_bigendian

int d30v_cleanup (int);
#define md_cleanup()		     d30v_cleanup (false)
#define TC_START_LABEL(STR, NUL_CHAR, NEXT_CHAR)	\
  (NEXT_CHAR == ':' && d30v_cleanup (false))
void d30v_start_line (void);
#define md_start_line_hook()	     d30v_start_line ()

void d30v_frob_label (symbolS *);
#define tc_frob_label(sym)	     d30v_frob_label (sym)

void d30v_cons_align (int);
#define md_cons_align(nbytes)	     d30v_cons_align (nbytes)

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

/* No shared lib support, so we don't need to ensure externally
   visible symbols can be overridden.  */
#define EXTERN_FORCE_RELOC 0

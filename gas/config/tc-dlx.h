/* tc-dlx.h -- Assemble for the DLX
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_DLX

/* The target BFD architecture.  */
#define TARGET_ARCH              bfd_arch_dlx
#define TARGET_FORMAT            "elf32-dlx"
#define TARGET_BYTES_BIG_ENDIAN	 1

#define WORKING_DOT_WORD

#define LEX_DOLLAR 1

#include "bit_fix.h"

#define TC_FIX_TYPE bit_fixS *
#define tc_fix_data fx_bit_fixP
#define TC_INIT_FIX_DATA(FIX) do (FIX)->fx_bit_fixP = NULL; while (0)

extern void dlx_pop_insert         (void);
extern int dlx_unrecognized_line   (int);
extern bool md_dlx_fix_adjustable  (struct fix *);

#define md_pop_insert()		        dlx_pop_insert ()

#define md_convert_frag(b,s,f)		as_fatal ("convert_frag called\n")
#define md_estimate_size_before_relax(f,s) \
			(as_fatal ("estimate_size_before_relax called"),1)

#define tc_unrecognized_line(c) dlx_unrecognized_line (c)

/* No shared lib support, so we don't need to ensure externally
   visible symbols can be overridden.  */
#define EXTERN_FORCE_RELOC 0

#define tc_fix_adjustable(FIX) md_dlx_fix_adjustable (FIX)

/* Values passed to md_apply_fix don't include the symbol value.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

/* Zero Based Segment?? sound very dangerous to me!     */
#define ZERO_BASED_SEGMENTS

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

#undef  LOCAL_LABELS_DOLLAR
#define LOCAL_LABELS_DOLLAR 0

/* .-foo gets turned into PC relative relocs.  */
#define DIFF_EXPR_OK

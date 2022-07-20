/* tc-moxie.h -- Header file for tc-moxie.c.

   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_MOXIE 1
#ifndef TARGET_BYTES_BIG_ENDIAN
#define TARGET_BYTES_BIG_ENDIAN 1
#endif
#define WORKING_DOT_WORD

/* This macro is the BFD architecture to pass to `bfd_set_arch_mach'.  */
#define TARGET_FORMAT (target_big_endian ? "elf32-bigmoxie" : "elf32-littlemoxie")

#define TARGET_ARCH bfd_arch_moxie

#define md_undefined_symbol(NAME)           0

/* These macros must be defined, but is will be a fatal assembler
   error if we ever hit them.  */
#define md_estimate_size_before_relax(A, B) (as_fatal (_("estimate size\n")), 0)
#define md_convert_frag(B, S, F)            as_fatal (_("convert_frag\n"))

#define md_section_align(SEGMENT, SIZE)     (SIZE)

/* tc-pdp11.h -- Header file for tc-pdp11.c.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TC_PDP11 1

#define TARGET_FORMAT "a.out-pdp11"
#define TARGET_ARCH bfd_arch_pdp11
#define TARGET_BYTES_BIG_ENDIAN 0

#define LEX_TILDE (LEX_BEGIN_NAME | LEX_NAME)

#define md_operand(x)

long md_chars_to_number (unsigned char *, int);

/* end of tc-pdp11.h */

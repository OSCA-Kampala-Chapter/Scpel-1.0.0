/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TE_GO32

#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

/* GAS should treat '.align value' as an alignment of 2**value.  */
#define USE_ALIGN_PTWO

#define COFF_LONG_SECTION_NAMES

/* These define interfaces.  */
#include "obj-format.h"

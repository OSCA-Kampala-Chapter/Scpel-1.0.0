/* te-haiku.h -- Haiku target environment declarations.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/* Target environment for BeOS/Haiku.  It is the same as the generic
   target, except that it arranges via the TE_BeOS define to
   suppress the use of "/" as a comment character.  Some code in the
   haiku kernel uses "/" to mean division.  (What a concept!)  */
#define TE_Haiku 1

#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

#include "obj-format.h"

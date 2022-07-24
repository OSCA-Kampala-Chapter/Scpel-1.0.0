/* te-dragonfly.h -- DragonFlyBSD target environment declarations.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/* Target environment for DragonFlyBSD.  It is the same as the generic
   target, except that it arranges via the TE_DragonFly define to
   suppress the use of "/" as a comment character.  Some code in the
   DragonFlyBSD kernel uses "/" to mean division.  (What a concept!)  */
#define TE_DragonFly 1

#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

#include "obj-format.h"

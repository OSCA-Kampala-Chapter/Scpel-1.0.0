/* Please review $(srcdir/SPL-README) for GNU licencing info. */

/* The EABI requires the use of VFP.  */
#define FPU_DEFAULT FPU_ARCH_VFP
#define EABI_DEFAULT EF_ARM_EABI_VER5

#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

#include "obj-format.h"

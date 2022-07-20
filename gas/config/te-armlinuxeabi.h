/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "te-linux.h"

/* The EABI requires the use of VFP.  */
#define FPU_DEFAULT FPU_ARCH_VFP
#define EABI_DEFAULT EF_ARM_EABI_VER5

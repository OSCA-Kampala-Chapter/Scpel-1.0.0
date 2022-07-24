/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TE_NACL

#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

/* These are for ARM but don't hurt other CPU targets.
   They match the settings from te-armeabi.h; NaCl/ARM is based on EABI.  */
#define FPU_DEFAULT FPU_ARCH_VFP
#define EABI_DEFAULT EF_ARM_EABI_VER5

#include "obj-format.h"

/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TARGET_FORMAT		"a.out-ns32k-netbsd"

#include "obj-format.h"

/* Maybe these should be more like TC_NS32532 and TC_NS32381 in case
   of conflicts. NS32381 is used in opcode/ns32k.h and that is also
   used by GDB. Need to check.  */
#define NS32532
#define NS32381

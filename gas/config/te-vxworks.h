/* te-vxworks.h -- VxWorks target environment declarations.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TE_VXWORKS	1
#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

/* these define interfaces */
#ifdef OBJ_HEADER
#include OBJ_HEADER
#else
#include "obj-format.h"
#endif

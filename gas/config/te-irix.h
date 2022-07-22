/* IRIX targets
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/* This file is te-irix.h and is intended to provide support for
   IRIX targets.  Created by Alexandre Oliva <aoliva@redhat.com>.  */

#define TE_IRIX 1

/* these define interfaces */
#ifdef OBJ_HEADER
#include OBJ_HEADER
#else
#include "obj-format.h"
#endif

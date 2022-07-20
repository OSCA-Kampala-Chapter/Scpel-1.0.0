/* Traditional MIPS targets
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/* This file is te-tmips.h and is intended to provide support for
   traditional mips targets like mips-dde-sysv4.2MP (Supermax ) ,
   mips-sni-sysv4* (Sinix) etc. The base for this file is te-generic.h.
   Created by Koundinya.K < kk@ddeorg.soft.net > with the help of
   Ian Lance Taylor, Cygnus Support, <ian@cygnus.com>.  */

/* Added these, because if we don't know what we're targeting we may
   need an assembler version of libgcc, and that will use local
   labels.  */

#define TE_TMIPS 1
#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

/* these define interfaces */
#ifdef OBJ_HEADER
#include OBJ_HEADER
#else
#include "obj-format.h"
#endif

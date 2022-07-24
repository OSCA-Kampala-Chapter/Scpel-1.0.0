/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TE_SOLARIS

#define LOCAL_LABELS_DOLLAR 1
#define LOCAL_LABELS_FB 1

#include "obj-format.h"

/* The Sun linker doesn't merge read-only and read-write sections into
   a single section so we must force all EH frame sections to use the
   same flags.  For SPARC and 32-bit i386 this is read-write, whilst
   for x86_64 this is read-only, matching GCC behavior.

   See the definition of EH_TABLES_CAN_BE_READ_ONLY in
   gcc/config/i386/sol2.h in the GCC sources and the thread starting at
   http://sourceware.org/ml/binutils/2010-01/msg00401.html.  */
#ifdef TC_SPARC
#define DWARF2_EH_FRAME_READ_ONLY SEC_NO_FLAGS
#else
#define DWARF2_EH_FRAME_READ_ONLY \
  (bfd_get_arch_size (stdoutput) == 64 ? SEC_READONLY : SEC_NO_FLAGS)
#endif

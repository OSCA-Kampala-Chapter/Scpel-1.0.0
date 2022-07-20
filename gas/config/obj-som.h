/* SOM object file format.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef _OBJ_SOM_H
#define _OBJ_SOM_H

#define OBJ_SOM 1

#include "bfd/som.h"
#include "som/reloc.h"
#include "targ-cpu.h"

/* should be conditional on address size!  */
#define som_symbol(asymbol) ((som_symbol_type *) (&(asymbol)->the_bfd))

extern void som_file_symbol           (char *);
extern void som_frob_file             (void);
extern void obj_som_version           (int);
extern void obj_som_init_stab_section (segT);
extern void obj_som_copyright         (int);
extern void obj_som_compiler          (int);

#define obj_symbol_new_hook(s) {;}

/* SOM has several attributes for spaces/subspaces which can not
   be easily expressed in BFD.  We use these macros to trigger calls
   into the SOM BFD backend to set these attributes.  */
#define obj_set_section_attributes  bfd_som_set_section_attributes
#define obj_set_subsection_attributes bfd_som_set_subsection_attributes

/* Likewise for symbol types.  */
#define obj_set_symbol_type bfd_som_set_symbol_type

/* Stabs go in a separate sections.  GDB expects to find them in sections
   with the names $GDB_SYMBOLS$ and $GDB_STRINGS$ rather than .stab and
   .stabstr.  */
#define SEPARATE_STAB_SECTIONS 1
#define STAB_SECTION_NAME "$GDB_SYMBOLS$"
#define STAB_STRING_SECTION_NAME "$GDB_STRINGS$"

/* We use INIT_STAB_SECTION to record the space/subspace relationships
   for the various debugging sections.  */
#define INIT_STAB_SECTION(seg) obj_som_init_stab_section (seg)

/* We'll be updating the magic 1st stab entry once the entire assembly
   fail has been processed.  */
#define obj_frob_file() som_frob_file()

#endif /* _OBJ_SOM_H */

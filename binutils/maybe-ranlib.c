/* Please review $(srcdir/SPL-README) for GNU licencing info. */

/* Linked with ar.o to flag that this program decides at runtime
   (using argv[0] if it is is 'ar' or 'ranlib'.  */

int is_ranlib = -1;

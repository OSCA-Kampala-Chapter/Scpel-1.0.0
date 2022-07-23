/* This file is output-file.h

   Please review $(srcdir/SPL-README) for GNU licencing info. */

void output_file_append (char *where, long length, char *filename);
void output_file_close (const char *filename);
void output_file_create (const char *name);

/* end of output-file.h */
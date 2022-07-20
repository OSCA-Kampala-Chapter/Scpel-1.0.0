/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#define TE_VMS
#include "obj-format.h"

extern bfd_uint64_t vms_dwarf2_file_time_name (const char *, const char *);
extern long vms_dwarf2_file_size_name (const char *, const char *);
extern char *vms_dwarf2_file_name (const char *, const char *);

/* VMS debugger expects a separator.  */
#define DWARF2_DIR_SHOULD_END_WITH_SEPARATOR 1

/* VMS debugger needs the file timestamp.  */
#define DWARF2_FILE_TIME_NAME(FILENAME,DIRNAME)                       \
  vms_dwarf2_file_time_name(FILENAME, DIRNAME)

/* VMS debugger needs the file size.  */
#define DWARF2_FILE_SIZE_NAME(FILENAME,DIRNAME)                       \
  vms_dwarf2_file_size_name(FILENAME, DIRNAME)

/* VMS debugger needs the filename with version appended.  */
/* Longest filename on VMS is 255 characters. Largest version is 32768.  */
#define DWARF2_FILE_NAME(FILENAME,DIRNAME)                            \
  vms_dwarf2_file_name(FILENAME, DIRNAME)

/* Please review $(srcdir/SPL-README) for GNU licencing info. */

/* Linux dumps "struct task_struct" at the end of the core-file.  This
   structure is currently 2512 bytes long, but we allow up to 4096
   bytes to allow for some future growth.  */
#define TRAD_CORE_EXTRA_SIZE_ALLOWED		4096
#define TRAD_UNIX_CORE_FILE_FAILING_SIGNAL(abfd) \
  ((abfd)->tdata.trad_core_data->u.signal)

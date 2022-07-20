/* Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "as.h"
#include "emul.h"

static const char *crisaout_bfd_name (void);

static const char *
crisaout_bfd_name (void)
{
  abort ();
  return NULL;
}

#define emul_bfd_name	crisaout_bfd_name
#define emul_format	&aout_format_ops

#define emul_name	"crisaout"
#define emul_struct_name crisaout
#define emul_default_endian 0
#include "emul-target.h"

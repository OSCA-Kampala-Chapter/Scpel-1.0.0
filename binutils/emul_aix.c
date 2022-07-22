/* Binutils emulation layer.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "binemul.h"
#include "bfdlink.h"
#include "coff/internal.h"
#include "coff/xcoff.h"
#include "libcoff.h"
#include "libxcoff.h"

/* Default to <bigaf>.  */
/* FIXME: write only variable.  */
static bool big_archive = true;

/* Whether to include 32 bit objects.  */
static bool X32 = true;

/* Whether to include 64 bit objects.  */
static bool X64 = false;

static void
ar_emul_aix_usage (FILE *fp)
{
  AR_EMUL_USAGE_PRINT_OPTION_HEADER (fp);
  /* xgettext:c-format */
  fprintf (fp, _("  [-g]         - 32 bit small archive\n"));
  fprintf (fp, _("  [-X32]       - ignores 64 bit objects\n"));
  fprintf (fp, _("  [-X64]       - ignores 32 bit objects\n"));
  fprintf (fp, _("  [-X32_64]    - accepts 32 and 64 bit objects\n"));
}

static bool
check_aix (bfd *try_bfd)
{
  extern const bfd_target rs6000_xcoff_vec;
  extern const bfd_target rs6000_xcoff64_vec;
  extern const bfd_target rs6000_xcoff64_aix_vec;

  if (bfd_check_format (try_bfd, bfd_object))
    {
      if (!X32 && try_bfd->xvec == &rs6000_xcoff_vec)
	return false;

      if (!X64 && (try_bfd->xvec == &rs6000_xcoff64_vec
		   || try_bfd->xvec == &rs6000_xcoff64_aix_vec))
	return false;
    }
  return true;
}

static bool
ar_emul_aix_append (bfd **after_bfd, bfd *new_bfd,
		    bool verbose, bool flatten)
{
  return do_ar_emul_append (after_bfd, new_bfd, verbose, flatten, check_aix);
}

static bool
ar_emul_aix_replace (bfd **after_bfd, bfd *new_bfd,
		     bool verbose)
{
  if (!check_aix (new_bfd))
    return false;

  AR_EMUL_REPLACE_PRINT_VERBOSE (verbose, bfd_get_filename (new_bfd));

  new_bfd->archive_next = *after_bfd;
  *after_bfd = new_bfd;

  return true;
}

static bool
ar_emul_aix_parse_arg (char *arg)
{
  if (startswith (arg, "-X32_64"))
    {
      big_archive = true;
      X32 = true;
      X64 = true;
    }
  else if (startswith (arg, "-X32"))
    {
      big_archive = true;
      X32 = true;
      X64 = false;
    }
  else if (startswith (arg, "-X64"))
    {
      big_archive = true;
      X32 = false;
      X64 = true;
    }
  else if (startswith (arg, "-g"))
    {
      big_archive = false;
      X32 = true;
      X64 = false;
    }
  else
    return false;

  return true;
}

struct bin_emulation_xfer_struct bin_aix_emulation =
{
  ar_emul_aix_usage,
  ar_emul_aix_append,
  ar_emul_aix_replace,
  ar_emul_aix_parse_arg,
};

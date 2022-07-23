/* Like sprintf but provides a pointer to malloc'd storage, which must
   be freed by the caller.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "ansidecl.h"
#include "libiberty.h"

#include <stdarg.h>

/*

@deftypefn Extension int asprintf (char **@var{resptr}, const char *@var{format}, ...)

Like @code{sprintf}, but instead of passing a pointer to a buffer, you
pass a pointer to a pointer.  This function will compute the size of
the buffer needed, allocate memory with @code{malloc}, and store a
pointer to the allocated memory in @code{*@var{resptr}}.  The value
returned is the same as @code{sprintf} would return.  If memory could
not be allocated, minus one is returned and @code{NULL} is stored in
@code{*@var{resptr}}.

@end deftypefn

*/

int
asprintf (char **buf, const char *fmt, ...)
{
  int status;
  va_list ap;
  va_start (ap, fmt);
  status = vasprintf (buf, fmt, ap);
  va_end (ap);
  return status;
}

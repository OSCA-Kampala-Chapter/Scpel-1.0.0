/* Implement the snprintf function.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental int snprintf (char *@var{buf}, size_t @var{n}, @
  const char *@var{format}, ...)

This function is similar to @code{sprintf}, but it will write to
@var{buf} at most @code{@var{n}-1} bytes of text, followed by a
terminating null byte, for a total of @var{n} bytes.
On error the return value is -1, otherwise it returns the number of
bytes, not including the terminating null byte, that would have been
written had @var{n} been sufficiently large, regardless of the actual
value of @var{n}.  Note some pre-C99 system libraries do not implement
this correctly so users cannot generally rely on the return value if
the system version of this function is used.

@end deftypefn

*/

#include "ansidecl.h"

#include <stdarg.h>
#include <stddef.h>

int vsnprintf (char *, size_t, const char *, va_list);

int
snprintf (char *s, size_t n, const char *format, ...)
{
  int result;
  va_list ap;
  va_start (ap, format);
  result = vsnprintf (s, n, format, ap);
  va_end (ap);
  return result;
}

/* Implement the strndup function.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Extension char* strndup (const char *@var{s}, size_t @var{n})

Returns a pointer to a copy of @var{s} with at most @var{n} characters
in memory obtained from @code{malloc}, or @code{NULL} if insufficient
memory was available.  The result is always NUL terminated.

@end deftypefn

*/

#include "ansidecl.h"
#include <stddef.h>

extern size_t	strnlen (const char *s, size_t maxlen);
extern void *malloc (size_t);
extern void *memcpy (void *, const void *, size_t);

char *
strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strnlen (s, n);

  result = (char *) malloc (len + 1);
  if (!result)
    return 0;

  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}

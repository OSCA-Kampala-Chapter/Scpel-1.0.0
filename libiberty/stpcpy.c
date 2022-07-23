/* Implement the stpcpy function.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental char* stpcpy (char *@var{dst}, const char *@var{src})

Copies the string @var{src} into @var{dst}.  Returns a pointer to
@var{dst} + strlen(@var{src}).

@end deftypefn

*/

#include <ansidecl.h>
#include <stddef.h>

extern size_t strlen (const char *);
extern void *memcpy (void *, const void *, size_t);

char *
stpcpy (char *dst, const char *src)
{
  const size_t len = strlen (src);
  return (char *) memcpy (dst, src, len + 1) + len;
}

/* Implement the stpncpy function.
    Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental char* stpncpy (char *@var{dst}, const char *@var{src}, @
  size_t @var{len})

Copies the string @var{src} into @var{dst}, copying exactly @var{len}
and padding with zeros if necessary.  If @var{len} < strlen(@var{src})
then return @var{dst} + @var{len}, otherwise returns @var{dst} +
strlen(@var{src}).

@end deftypefn

*/

#include <ansidecl.h>
#include <stddef.h>

extern size_t strlen (const char *);
extern char *strncpy (char *, const char *, size_t);

char *
stpncpy (char *dst, const char *src, size_t len)
{
  size_t n = strlen (src);
  if (n > len)
    n = len;
  return strncpy (dst, src, len) + n;
}

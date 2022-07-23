/* Implement the mempcpy function.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental void* mempcpy (void *@var{out}, const void *@var{in}, @
  size_t @var{length})

Copies @var{length} bytes from memory region @var{in} to region
@var{out}.  Returns a pointer to @var{out} + @var{length}.

@end deftypefn

*/

#include <ansidecl.h>
#include <stddef.h>

extern void *memcpy (void *, const void *, size_t);

void *
mempcpy (void *dst, const void *src, size_t len)
{
  return (char *) memcpy (dst, src, len) + len;
}

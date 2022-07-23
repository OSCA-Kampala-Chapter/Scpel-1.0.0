/* Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental void* memmem (const void *@var{haystack}, @
  size_t @var{haystack_len} const void *@var{needle}, size_t @var{needle_len})

Returns a pointer to the first occurrence of @var{needle} (length
@var{needle_len}) in @var{haystack} (length @var{haystack_len}).
Returns @code{NULL} if not found.

@end deftypefn

*/

#ifndef _LIBC
# include <config.h>
#endif

#include <stddef.h>
#include <string.h>

#ifndef _LIBC
# define __builtin_expect(expr, val)   (expr)
#endif

#undef memmem

/* Return the first occurrence of NEEDLE in HAYSTACK.  */
void *
memmem (const void *haystack, size_t haystack_len, const void *needle,
	size_t needle_len)
{
  const char *begin;
  const char *const last_possible
    = (const char *) haystack + haystack_len - needle_len;

  if (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    return (void *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  if (__builtin_expect (haystack_len < needle_len, 0))
    return NULL;

  for (begin = (const char *) haystack; begin <= last_possible; ++begin)
    if (begin[0] == ((const char *) needle)[0] &&
	!memcmp ((const void *) &begin[1],
		 (const void *) ((const char *) needle + 1),
		 needle_len - 1))
      return (void *) begin;

  return NULL;
}

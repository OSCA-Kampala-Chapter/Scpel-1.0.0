/* Implement the vsnprintf function.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental int vsnprintf (char *@var{buf}, size_t @var{n}, @
  const char *@var{format}, va_list @var{ap})

This function is similar to @code{vsprintf}, but it will write to
@var{buf} at most @code{@var{n}-1} bytes of text, followed by a
terminating null byte, for a total of @var{n} bytes.  On error the
return value is -1, otherwise it returns the number of characters that
would have been printed had @var{n} been sufficiently large,
regardless of the actual value of @var{n}.  Note some pre-C99 system
libraries do not implement this correctly so users cannot generally
rely on the return value if the system version of this function is
used.

@end deftypefn

*/

#include "config.h"
#include "ansidecl.h"

#include <stdarg.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "libiberty.h"

/* This implementation relies on a working vasprintf.  */
int
vsnprintf (char *s, size_t n, const char *format, va_list ap)
{
  char *buf = 0;
  int result = vasprintf (&buf, format, ap);

  if (!buf)
    return -1;
  if (result < 0)
    {
      free (buf);
      return -1;
    }

  result = strlen (buf);
  if (n > 0)
    {
      if ((long) n > result)
	memcpy (s, buf, result+1);
      else
        {
	  memcpy (s, buf, n-1);
	  s[n - 1] = 0;
	}
    }
  free (buf);
  return result;
}

#ifdef TEST
/* Set the buffer to a known state.  */
#define CLEAR(BUF) do { memset ((BUF), 'X', sizeof (BUF)); (BUF)[14] = '\0'; } while (0)
/* For assertions.  */
#define VERIFY(P) do { if (!(P)) abort(); } while (0)

static int ATTRIBUTE_PRINTF_3
checkit (char *s, size_t n, const char *format, ...)
{
  int result;
  va_list ap;
  va_start (ap, format);
  result = vsnprintf (s, n, format, ap);
  va_end (ap);
  return result;
}

extern int main (void);
int
main (void)
{
  char buf[128];
  int status;
  
  CLEAR (buf);
  status = checkit (buf, 10, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "foobar:9\0XXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 9, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "foobar:9\0XXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 8, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "foobar:\0XXXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 7, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "foobar\0XXXXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 6, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "fooba\0XXXXXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 2, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "f\0XXXXXXXXXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 1, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "\0XXXXXXXXXXXXX\0", 15) == 0);

  CLEAR (buf);
  status = checkit (buf, 0, "%s:%d", "foobar", 9);
  VERIFY (status==8 && memcmp (buf, "XXXXXXXXXXXXXX\0", 15) == 0);

  return 0;
}
#endif /* TEST */

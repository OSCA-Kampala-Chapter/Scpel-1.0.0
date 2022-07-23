/* Provide a version vfprintf in terms of _doprnt.
 */

#include "ansidecl.h"
#include <stdarg.h>
#include <stdio.h>
#undef vfprintf

int
vfprintf (FILE *stream, const char *format, va_list ap)
{
  return _doprnt (format, ap, stream);
}

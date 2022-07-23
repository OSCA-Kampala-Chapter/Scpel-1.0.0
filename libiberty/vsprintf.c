/* Simple implementation of vsprintf for systems without it.
   Highly system-dependent, but should work on most "traditional"
   implementations of stdio; newer ones should already have vsprintf.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include <ansidecl.h>
#include <stdarg.h>
#include <stdio.h>
#undef vsprintf

#if defined _IOSTRG && defined _IOWRT

int
vsprintf (char *buf, const char *format, va_list ap)
{
  FILE b;
  int ret;
#ifdef VMS
  b->_flag = _IOWRT|_IOSTRG;
  b->_ptr = buf;
  b->_cnt = 12000;
#else
  b._flag = _IOWRT|_IOSTRG;
  b._ptr = buf;
  b._cnt = 12000;
#endif
  ret = _doprnt(format, ap, &b);
  putc('\0', &b);
  return ret;

}

#endif

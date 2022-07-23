/* ANSI-compatible clock function.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

/*

@deftypefn Supplemental long clock (void)

Returns an approximation of the CPU time used by the process as a
@code{clock_t}; divide this number by @samp{CLOCKS_PER_SEC} to get the
number of seconds used.

@end deftypefn

*/

#include "config.h"

#ifdef HAVE_GETRUSAGE
#include <sys/time.h>
#include <sys/resource.h>
#endif

#ifdef HAVE_TIMES
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#include <sys/times.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef _SC_CLK_TCK
#define GNU_HZ  sysconf(_SC_CLK_TCK)
#else
#ifdef HZ
#define GNU_HZ  HZ
#else
#ifdef CLOCKS_PER_SEC
#define GNU_HZ  CLOCKS_PER_SEC
#endif
#endif
#endif

/* FIXME: should be able to declare as clock_t. */

long
clock (void)
{
#ifdef HAVE_GETRUSAGE
  struct rusage rusage;

  getrusage (0, &rusage);
  return (rusage.ru_utime.tv_sec * 1000000 + rusage.ru_utime.tv_usec
	  + rusage.ru_stime.tv_sec * 1000000 + rusage.ru_stime.tv_usec);
#else
#ifdef HAVE_TIMES
  struct tms tms;

  times (&tms);
  return (tms.tms_utime + tms.tms_stime) * (1000000 / GNU_HZ);
#else
#ifdef VMS
  struct
    {
      int proc_user_time;
      int proc_system_time;
      int child_user_time;
      int child_system_time;
    } vms_times;

  times (&vms_times);
  return (vms_times.proc_user_time + vms_times.proc_system_time) * 10000;
#else
  /* A fallback, if nothing else available. */
  return 0;
#endif /* VMS */
#endif /* HAVE_TIMES */
#endif /* HAVE_GETRUSAGE */
}


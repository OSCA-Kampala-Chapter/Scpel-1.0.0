/*
 * Please review $(srcdir/SPL-README) for GNU licencing info.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#include <errno.h>
#ifdef NEED_DECLARATION_ERRNO
extern int errno;
#endif
#if 0
#include <stdlib.h>
#endif
#include "ansidecl.h"
#include "safe-ctype.h"

#ifdef HAVE_LONG_LONG

__extension__
typedef unsigned long long ullong_type;

#ifndef ULLONG_MAX
#define ULLONG_MAX (~(ullong_type)0) /* 0xFFFFFFFFFFFFFFFF */
#endif

/*
 * Convert a string to an unsigned long long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
ullong_type
strtoull(const char *nptr, char **endptr, register int base)
{
	register const char *s = nptr;
	register ullong_type acc;
	register int c;
	register ullong_type cutoff;
	register int neg = 0, any, cutlim;

	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (ISSPACE(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else if (c == '+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = (ullong_type)ULLONG_MAX / (ullong_type)base;
	cutlim = (ullong_type)ULLONG_MAX % (ullong_type)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (ISDIGIT(c))
			c -= '0';
		else if (ISALPHA(c))
			c -= ISUPPER(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0) {
		acc = ULLONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : nptr);
	return (acc);
}

#endif /* ifdef HAVE_LONG_LONG */

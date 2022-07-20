/* tc-tic30.h -- Header file for tc-tic30.c
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef _TC_TIC30_H_
#define _TC_TIC30_H_

#define TC_TIC30 1

#define TARGET_ARCH		bfd_arch_tic30
#define TARGET_BYTES_BIG_ENDIAN	1
#define WORKING_DOT_WORD
#define END_OF_INSN 		'\0'
#define MAX_OPERANDS 		6
#define DIRECT_REFERENCE 	'@'
#define INDIRECT_REFERENCE 	'*'
#define PARALLEL_SEPARATOR 	'|'
#define INSN_SIZE 		4

/* Define this to 1 if you want the debug output to be on stdout,
   otherwise stderr will be used.  If stderr is used, there will be a
   better synchronisation with the as_bad outputs, but you can't
   capture the output.  */
#define USE_STDOUT 		0

#define tc_unrecognized_line tic30_unrecognized_line

extern int tic30_unrecognized_line (int);

#endif

/* tc-score.h -- Score specific file for assembler
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef TC_SCORE
#define TC_SCORE

#define TARGET_ARCH 	            bfd_arch_score
#define WORKING_DOT_WORD
#define DIFF_EXPR_OK
#define RELOC_EXPANSION_POSSIBLE
#define MAX_RELOC_EXPANSION         2
#define MAX_MEM_FOR_RS_ALIGN_CODE  (3 + 4)

#define md_undefined_symbol(name)  NULL

#define TARGET_FORMAT  (target_big_endian ? "elf32-bigscore" : "elf32-littlescore")

#define md_relax_frag(segment, fragp, stretch)  score_relax_frag (segment, fragp, stretch)
extern int score_relax_frag (asection *, struct frag *, long);

/* #define md_frag_check(fragp)  score_frag_check (fragp) */
extern void score_frag_check (fragS *);

#define TC_VALIDATE_FIX(FIXP, SEGTYPE, SKIP)  score_validate_fix (FIXP)
extern void score_validate_fix (struct fix *);

#define TC_FORCE_RELOCATION(FIXP)  score_force_relocation (FIXP)
extern int score_force_relocation (struct fix *);

#define tc_fix_adjustable(fixp)  score_fix_adjustable (fixp)
extern bool score_fix_adjustable (struct fix *);

#define elf_tc_final_processing  score_elf_final_processing
extern void score_elf_final_processing (void);

struct score_tc_frag_data
{
  unsigned int is_insn;
  struct fix *fixp;
};

#define TC_FRAG_TYPE struct score_tc_frag_data

#define TC_FRAG_INIT(FRAGP, MAX_BYTES) \
  do \
    { \
      (FRAGP)->tc_frag_data.is_insn = (((FRAGP)->fr_type == rs_machine_dependent) ? 1 : 0); \
    } \
  while (0)

#ifdef OBJ_ELF
#define GLOBAL_OFFSET_TABLE_NAME "_GLOBAL_OFFSET_TABLE_"
#else
#define GLOBAL_OFFSET_TABLE_NAME "__GLOBAL_OFFSET_TABLE_"
#endif

#endif /*TC_SCORE */

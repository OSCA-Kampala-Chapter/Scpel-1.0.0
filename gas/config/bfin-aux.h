/* bfin-aux.h ADI Blackfin Header file for gas
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "bfin-defs.h"

#define REG_T Register *

INSTR_T bfin_gen_dsp32mac (int, int, int, int, int, int, int, int, int, int, REG_T, REG_T, REG_T, int);
INSTR_T bfin_gen_dsp32mult (int, int, int, int, int, int, int, int, int, int, REG_T, REG_T, REG_T, int);
INSTR_T bfin_gen_dsp32alu (int, int, int, int, int, REG_T, REG_T, REG_T, REG_T);
INSTR_T bfin_gen_dsp32shift (int, REG_T, REG_T, REG_T, int, int);
INSTR_T bfin_gen_dsp32shiftimm (int, REG_T, int, REG_T, int, int);
INSTR_T bfin_gen_ldimmhalf (REG_T, int, int, int, Expr_Node *, int);
INSTR_T bfin_gen_ldstidxi (REG_T, REG_T, int, int, int, Expr_Node *);
INSTR_T bfin_gen_ldst (REG_T, REG_T, int, int, int, int);
INSTR_T bfin_gen_ldstii (REG_T, REG_T, Expr_Node *, int, int);
INSTR_T bfin_gen_ldstiifp (REG_T, Expr_Node *, int);
INSTR_T bfin_gen_ldstpmod (REG_T, REG_T, int, int, REG_T);
INSTR_T bfin_gen_dspldst (REG_T, REG_T, int, int, int);
INSTR_T bfin_gen_alu2op (REG_T, REG_T, int);
INSTR_T bfin_gen_compi2opd (REG_T, int, int);
INSTR_T bfin_gen_compi2opp (REG_T, int, int);
INSTR_T bfin_gen_dagmodik (REG_T, int);
INSTR_T bfin_gen_dagmodim (REG_T, REG_T, int, int);
INSTR_T bfin_gen_ptr2op (REG_T, REG_T, int);
INSTR_T bfin_gen_logi2op (int, int, int);
INSTR_T bfin_gen_comp3op (REG_T, REG_T, REG_T, int);
INSTR_T bfin_gen_ccmv (REG_T, REG_T, int);
INSTR_T bfin_gen_ccflag (REG_T, int, int, int, int);
INSTR_T bfin_gen_cc2stat (int, int, int);
INSTR_T bfin_gen_regmv (REG_T, REG_T);
INSTR_T bfin_gen_cc2dreg (int, REG_T);
INSTR_T bfin_gen_brcc (int, int, Expr_Node *);
INSTR_T bfin_gen_ujump (Expr_Node *);
INSTR_T bfin_gen_cactrl (REG_T, int, int);
INSTR_T bfin_gen_progctrl (int, int);
INSTR_T bfin_gen_loopsetup (Expr_Node *, REG_T, int, Expr_Node *, REG_T);
INSTR_T bfin_gen_loop (Expr_Node *, REG_T, int, REG_T);
void bfin_loop_attempt_create_label (Expr_Node *, int);
void bfin_loop_beginend (Expr_Node *, int);
INSTR_T bfin_gen_pushpopmultiple (int, int, int, int, int);
INSTR_T bfin_gen_pushpopreg (REG_T, int);
INSTR_T bfin_gen_calla (Expr_Node *, int);
INSTR_T bfin_gen_linkage (int, int);
INSTR_T bfin_gen_pseudodbg (int, int, int);
INSTR_T bfin_gen_pseudodbg_assert (int, REG_T, int);
INSTR_T bfin_gen_pseudochr (int);
bool bfin_resource_conflict (INSTR_T, INSTR_T, INSTR_T);
INSTR_T bfin_gen_multi_instr (INSTR_T, INSTR_T, INSTR_T);

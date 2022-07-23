/* Declarations for stacks of tokenized Xtensa instructions.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#ifndef XTENSA_ISTACK_H
#define XTENSA_ISTACK_H

#include "xtensa-isa.h"

#define MAX_ISTACK 12
#define MAX_INSN_ARGS 64

enum itype_enum
{
  ITYPE_INSN,
  ITYPE_LITERAL,
  ITYPE_LABEL
};


/* Literals have 1 token and no opcode.
   Labels have 1 token and no opcode.  */

typedef struct tinsn_struct
{
  enum itype_enum insn_type;

  xtensa_opcode opcode;	/* Literals have an invalid opcode.  */
  bool is_specific_opcode;
  bool keep_wide;
  int ntok;
  expressionS tok[MAX_INSN_ARGS];
  bool loc_directive_seen;
  struct dwarf2_line_info debug_line;

  /* This field is used for two types of special pseudo ops:
     1. TLS-related operations.  Eg:  callx8.tls
     2. j.l  label, a2

     For the tls-related operations, it will hold a tls-related opcode
     and info to be used in a fixup.  For j.l it will hold a
     register to be used during relaxation.  */
  expressionS extra_arg;

  /* Filled out by relaxation_requirements:  */
  enum xtensa_relax_statesE subtype;
  int literal_space;

  /* Filled out by vinsn_to_insnbuf:  */
  symbolS *symbol;
  offsetT offset;
  fragS *literal_frag;
} TInsn;


/* tinsn_stack:  This is a stack of instructions to  be placed.  */

typedef struct tinsn_stack
{
  int ninsn;
  TInsn insn[MAX_ISTACK];
} IStack;


void istack_init (IStack *);
bool istack_empty (IStack *);
bool istack_full (IStack *);
TInsn *istack_top (IStack *);
void istack_push (IStack *, TInsn *);
TInsn *istack_push_space (IStack *);
void istack_pop (IStack *);

/* TInsn utilities.  */
void tinsn_init (TInsn *);


/* vliw_insn: bundles of TInsns.  */

typedef struct vliw_insn
{
  xtensa_format format;
  int num_slots;
  unsigned int inside_bundle;
  TInsn slots[MAX_SLOTS];
  xtensa_insnbuf insnbuf;
  xtensa_insnbuf slotbuf[MAX_SLOTS];
} vliw_insn;

#endif /* !XTENSA_ISTACK_H */

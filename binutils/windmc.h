/* windmc.h -- header file for windmc program.
   Please review $(srcdir/SPL-README) for GNU licencing info. */

#include "ansidecl.h"

/* This is the header file for the windmc program.  It defines
   structures and declares functions used within the program.  */

#include "winduni.h"

#ifndef WINDMC_HXX
#define WINDMC_HXX

/* Global flag variables (set by windmc.c file.  */
extern int mcset_custom_bit;
extern int mcset_out_values_are_decimal;
extern rc_uint_type mcset_max_message_length;
extern unichar *mcset_msg_id_typedef;

/* Lexer keyword definition and internal memory structures.  */

typedef struct mc_keyword
{
  struct mc_keyword *next;
  const char *group_name;
  size_t len;
  unichar *usz;
  int rid;
  rc_uint_type nval;
  unichar *sval;
  wind_language_t lang_info;
} mc_keyword;

typedef struct mc_node_lang
{
  struct mc_node_lang *next;
  rc_uint_type vid;
  const mc_keyword *lang;
  unichar *message;
} mc_node_lang;

typedef struct mc_node
{
  struct mc_node *next;
  unichar *user_text;
  const mc_keyword *facility;
  const mc_keyword *severity;
  unichar *symbol;
  rc_uint_type id;
  rc_uint_type vid;
  unichar *id_typecast;
  mc_node_lang *sub;
} mc_node;

extern mc_node *mc_nodes;

void mc_add_keyword (unichar *, int, const char *, rc_uint_type, unichar *);
const mc_keyword *enum_facility (int);
const mc_keyword *enum_severity (int);

mc_node_lang *mc_add_node_lang (mc_node *, const mc_keyword *, rc_uint_type);
mc_node *mc_add_node (void);

/* Standard yacc/flex stuff.  */
void yyerror (const char *);
int yylex (void);
int yyparse (void);

/* mclex.c  */
void mc_set_inputfile (const char *);
void mc_set_content (const unichar *);

/* Lexer control variables. Used by mcparser.y file.  */
extern bool mclex_want_nl;
extern bool mclex_want_line;
extern bool mclex_want_filename;

void mc_fatal (const char *, ...);
void mc_warn (const char *, ...);

#endif

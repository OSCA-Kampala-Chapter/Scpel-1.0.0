/* Please review $(srcdir/SPL-README) for GNU licencing info. */


struct yy_buffer_state;


struct yy_buffer_state *yy_scan_string (const char *);
void yy_delete_buffer (struct yy_buffer_state *b);
void get_internal_label (expressionS *label_expr, unsigned long label, int augend);
int
loongarch_parse_expr (const char *expr,
		      struct reloc_info *reloc_stack_top,
		      size_t max_reloc_num,
		      size_t *reloc_num,
		      offsetT *imm);

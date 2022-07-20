%option noyywrap
/* Please review $(srcdir/SPL-README) for GNU licencing info. */
%{
#include "as.h"
#include "loongarch-parse.h"

/* Flex generates static functions "input" & "unput" which are not used.  */
#define YY_NO_INPUT
#define YY_NO_UNPUT
%}

D	[0-9]
/* We consider anything greater than \x7f to be a "letter" for UTF-8
   support.  See the lex_type array in ../read.c.  */
L	[a-zA-Z_\.\$\x80-\xff]
H	[0-9A-Fa-f]

hex	0[xX]{H}+
oct	0[0-7]+
bin	0[bB][01]+
dec	([1-9]{D}*)|0
id	({D}+[fb])|({L}({D}|{L})*)|(:{dec}[bf])
ws	[ \t\v\f]+

%%

{dec}	{ yylval.imm = strtoull (yytext, 0, 0); return INTEGER; }
{hex}	{ yylval.imm = strtoull (yytext + 2, 0, 16); return INTEGER; }
{bin}	{ yylval.imm = strtoull (yytext + 2, 0, 2); return INTEGER; }
{oct}	{ yylval.imm = strtoull (yytext + 1, 0, 8); return INTEGER; }
{id}	{ yylval.c_str = strdup (yytext);return IDENTIFIER; }
{ws}	{ }

">>"	{ return RIGHT_OP; }
"<<"	{ return LEFT_OP; }
"&&"	{ return AND_OP; }
"||"	{ return OR_OP; }
"<="	{ return LE_OP; }
">="	{ return GE_OP; }
"=="	{ return EQ_OP; }
"!="	{ return NE_OP; }
.	{ return yytext[0];}

%%

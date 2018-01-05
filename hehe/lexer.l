%{
#include <stdio.h>
#pragma warning(disable : 4996)
%}


%e  1019
%p  2807
%n  371
%k  284
%a  1213
%o  1117

O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]
mnote \/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*\/
%{
#include <stdio.h>
#include "parser.tab.h"

extern void yyerror(const char *);  /* prints grammar violation message */

extern int sym_type(const char *);  /* returns type from symbol table */

#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

static void comment(void);
static int check_type(void);
%}

%%
{mnote}                 {  }
"//".*                  { /* consume //-comment */ }

"break"					{ return(BREAK); }
"case"					{ return(CASE); }
"char"					{ return(CHAR); }
"continue"				{ return(CONTINUE); }
"do"					{ return(DO); }
"double"				{ return(DOUBLE); }
"else"					{ return(ELSE); }
"enum"					{ return(ENUM); }
"float"					{ return(FLOAT); }
"for"					{ return(FOR); }
"if"					{ return(IF); }
"int"					{ return(INT); }
"long"					{ return(LONG); }
"return"				{ return(RETURN); }
"short"					{ return(SHORT); }
"signed"				{ return(SIGNED); }
"sizeof"				{ return(SIZEOF); }
"struct"				{ return(STRUCT); }
"switch"				{ return(SWITCH); }
"typedef"				{ return(TYPEDEF); }
"union"					{ return(UNION); }
"void"					{ return(VOID); }
"while"					{ return(WHILE); }
"Bool"                  { return BOOL; }

"read"					{return READ;}
"write"					{return WRITE;}

{L}{A}*					{ return check_type(); }

{HP}{H}+{IS}?				 {yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return I_CONSTANT; }
{NZ}{D}*{IS}?				 {yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return I_CONSTANT; }
"0"{O}*{IS}?				 {yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return I_CONSTANT; }
{CP}?"'"([^'\\\n]|{ES})+"'"	 {yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return C_CONSTANT; }

{D}+{E}{FS}?				{yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return F_CONSTANT; }
{D}*"."{D}+{E}?{FS}?			{yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return F_CONSTANT; }
{D}+"."{E}?{FS}?			{yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return F_CONSTANT; }
{HP}{H}+{P}{FS}?			{yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return F_CONSTANT; }
{HP}{H}*"."{H}+{P}{FS}?			{yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext); return F_CONSTANT; }
{HP}{H}+"."{P}{FS}?			{yylval.str=new char[strlen(yytext)];strcpy(yylval.str,yytext);  return F_CONSTANT; }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{ return STRING_LITERAL; }

">>="					{ return RIGHT_ASSIGN; }
"<<="					{ return LEFT_ASSIGN; }
"+="					{ return ADD_ASSIGN; }
"-="					{ return SUB_ASSIGN; }
"*="					{ return MUL_ASSIGN; }
"/="					{ return DIV_ASSIGN; }
"%="					{ return MOD_ASSIGN; }
"&="					{ return AND_ASSIGN; }
"^="					{ return XOR_ASSIGN; }
"|="					{ return OR_ASSIGN; }
">>"					{ return RIGHT_OP; }
"<<"					{ return LEFT_OP; }
"++"					{ return INC_OP; }
"--"					{ return DEC_OP; }
"->"					{ return PTR_OP; }
"&&"					{ return AND_OP; }
"||"					{ return OR_OP; }
"<="					{ return LE_OP; }
">="					{ return GE_OP; }
"=="					{ return EQ_OP; }
"!="					{ return NE_OP; }
";"					{ return ';'; }
("{"|"<%")				{ return '{'; }
("}"|"%>")				{ return '}'; }
","					{ return ','; }
":"					{ return ':'; }
"="					{ return '='; }
"("					{ return '('; }
")"					{ return ')'; }
("["|"<:")				{ return '['; }
("]"|":>")				{ return ']'; }
"."					{ return '.'; }
"&"					{ return '&'; }
"!"					{ return '!'; }
"~"					{ return '~'; }
"-"					{ return '-'; }
"+"					{ return '+'; }
"*"					{ return '*'; }
"/"					{ return '/'; }
"%"					{ return '%'; }
"<"					{ return '<'; }
">"					{ return '>'; }
"^"					{ return '^'; }
"|"					{ return '|'; }
"?"					{ return '?'; }

{WS}+					{ /* whitespace separates tokens */ }
.					{ /* discard bad characters */ }

%%

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}


static int check_type(void)
{
	yylval.str=new char[strlen(yytext)];
	strcpy(yylval.str,yytext);
	return IDENTIFIER;
}
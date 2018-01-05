%{
#include <stdio.h>
#include<vector>
#include<iostream>
#include <stdlib.h>
#include<string.h>
#include<string>
#include<map>
#include<list>
#include<fstream>
#include<sstream>
using namespace std;
int yylex(void);
void yyerror(const char *);
#pragma warning(disable : 4996)
class symbol;
class parameterlist
{
public:
	vector<symbol*> param;
	parameterlist(){};
};


class symbol {
public:
	char *name;
	int type;
	vector<int> list;
	parameterlist* child;
	int ty;
	void* val;
	bool beleft;
	bool iftemp;
	symbol();
	symbol(char *a);
};

symbol::symbol()
{
	name =	NULL; type = -1;child = NULL;
	ty = 0; val = NULL;beleft = 0;iftemp = 0;
}
symbol::symbol(char *a)
{
	child = NULL;
	type = -1;
	name = a;
	strcpy(name, a);
	ty = 0; val = NULL;
	beleft = 0;iftemp = 0;
}


class expression
{
public:
	expression *left;
	expression *right;
	expression *rr;		// 3元运算符
	expression *rrr;
	expression *next;   //表示同级表达式
	expression *last;
	expression *comstmt; //表示语句块 或者初始化列表
	char *opera;
	int size;	//  0表示 标识符或常量 1-3表示几元运算符
	int type;   // 1字符型 2整数 3 浮点数
	int arraysize;
	symbol *sym;
	void *val;
	vector<int> list;
	int canbeleft;
	int op;	//判断是否为运算操作
	int count;	
	expression() {count = 0; op = 0; val = NULL; type = 0;left = NULL; right = NULL; rr = NULL; opera = NULL;  size = 0; sym = NULL; val = NULL; next = NULL; last = this; comstmt =NULL; rrr = NULL; canbeleft = 0; arraysize = 1;};
	int compare(int *q,int size, int *count)
	{
		if(size == 0 && comstmt != NULL)
			return 1;
		if(val != NULL)
		{
			if(arraysize > *(count-1))
				return 1;
			else
			{
				expression *e = next;
				while (e != NULL)
				{
					if(e->comstmt != NULL)
						return 1;
					e = e->next;
				}
				return 0;
			}
		}
		else
		{
			expression *e = comstmt;
			while(e != NULL)
			{
				if(e->compare(q+1, size-1, count+1))
					return 1;
				e = e->next;
			}
			return 0;
		}
	}
};

expression *start = NULL;
int curtype;
map<string, symbol*> ss;
list<map<string, symbol*>> symboltable;
bool iferror = 0;
map<string, int>checktable;
vector<symbol*> sv;
%}

%union {
  char * str;
  class symbol  *sym;
  class parameterlist *parm;
  class expression *expr;
  class declarator *decl;
  int num;
}

%token<str> IDENTIFIER I_CONSTANT F_CONSTANT STRING_LITERAL  SIZEOF  C_CONSTANT
%token	PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token	AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token	SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token	XOR_ASSIGN OR_ASSIGN
%token	TYPEDEF_NAME ENUMERATION_CONSTANT

%token READ WRITE

%token	TYPEDEF
%token	BOOL CHAR SHORT INT LONG SIGNED FLOAT DOUBLE VOID
%token	STRUCT UNION ENUM 

%token	CASE IF ELSE SWITCH WHILE DO FOR CONTINUE BREAK RETURN

%type<expr> constant  primary_expression postfix_expression unary_expression cast_expression multiplicative_expression additive_expression shift_expression
%type<expr> relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type<expr> conditional_expression assignment_expression initializer  init_declarator init_declarator_list expression declaration initializer_list
%type<expr> statement block_item_list labeled_statement compound_statement expression_statement selection_statement iteration_statement jump_statement
%type<expr> block_item function_definition external_declaration translation_unit argument_expression_list
%type<str>  unary_operator assignment_operator struct_or_union  struct_or_union_specifier
%type<sym> declarator  direct_declarator  parameter_declaration struct_declarator type_name
%type<parm> parameter_type_list  parameter_list struct_declarator_list  struct_declaration struct_declaration_list 
%type<num> pointer abstract_declarator type_specifier  declaration_specifiers specifier_qualifier_list
%start translation_unit
%%

primary_expression
	: IDENTIFIER {string a = $1; map<string, symbol*>::iterator iter = symboltable.front().find(a); $$ = new expression();
				  list<map<string, symbol*>>::iterator v; int bb = 0;$$->opera = "ID";
				  for(v = symboltable.begin(); v != symboltable.end(); ++v)
				  {
					map<string, symbol*>::iterator iter = (*v).find(a);
					if(iter == (*v).end())
					{
						continue;
					}
					else
					{
					  $$->sym = iter->second;
					  for(int i = 0; i < iter->second->list.size(); ++i)
					  {
						$$->list.push_back(iter->second->list[i]);
					  }
					  $$->type = iter->second->ty;
					  $$->canbeleft = 1;
					  bb = 1;
					  break;
					 }
				  }
				  if (!bb)
				  {
					$$->opera = "未定义的变量";
					iferror = 1;
				  }
				 }
	| constant    {$$ = $1;}
	| string    {printf("字符串  ");}
	| '(' expression ')' {$$ = $2;}
	;

constant
	: I_CONSTANT	{$$ = new expression(); $$->size = 0; $$->type = 2; $$->size = -1; $$->val = malloc(sizeof(int));
					char te[3];
					if(strlen($1) > 2)
					{
						strncpy(te, $1, 2);te[2] = '\0';
						if(strcmp(te, "0x") ==0) 
							*(int*)$$->val = strtol($1, NULL, 16);
						else
							*(int*)$$->val = strtol($1, NULL, 10);
					}
					else
						*(int*)$$->val = strtol($1, NULL, 10);
					$$->opera = "VAL";
					}
	| F_CONSTANT    {$$ = new expression(); $$->size = 0; $$->type = 3; $$->size = -1; $$->val = malloc(sizeof(double)); *(double*)$$->val = atof($1); $$->opera = "VAL";}
	| C_CONSTANT    {$$ = new expression(); $$->size = 0; $$->type = 1; $$->size = -1; $$->val = malloc(sizeof(int));*(int*)$$->val = $1[1];$$->opera = "VAL";}
	| ENUMERATION_CONSTANT	  {printf("enum常量  ");}/* after it has been defined as such */
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER   
	;

string
	: STRING_LITERAL   {}
	;


postfix_expression
	: primary_expression  {$$ = $1;}
	| postfix_expression '[' expression ']'  {$$ = new expression(); $$->size = 2; $$->opera = "ARRAY"; $$->left = $1; $$->right = $3;$$->type = $1->type;
											  $$->count = $1->count + $3->count + 1;
											  for(int i= 1; i< $1->list.size(); ++i)
											  {
												$$->list.push_back($1->list[i]);
											  }
											  if($$->list.size() == 0 || $$->list[0] == 0)
												$$->canbeleft = 1;
											 }
	| postfix_expression '(' ')'     {$$ = new expression(); $$->size = 1; $$->opera = "FUNC_CALL"; $$->right = $1;}
	| postfix_expression '(' argument_expression_list ')'  {$$ = new expression(); $$->size = 1; $$->opera = "FUNC_CALL"; $$->right = $1; $$->comstmt = $3;}
	| READ '(' argument_expression_list ')'	{$$ = new expression(); $$->size = 0; $$->opera = "READ"; $$->comstmt = $3; $$->count = $3->count + 1;}
	| WRITE '(' argument_expression_list ')' {$$ = new expression(); $$->size = 0; $$->opera = "WRITE"; $$->comstmt = $3; $$->count = $3->count + 1;}
	| postfix_expression '.' IDENTIFIER 
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP    {$$ = new expression(); $$->size = 1; $$->opera = "PINC"; $$->right = $1;$$->op = 1;$$->count = $1->count + 1;
									if(!$1->canbeleft)
									{
										$$->opera = "POST_INC_OP  运算符必须是左值";
										iferror = 1;
									}
									$$->type = $1->type;
								   }
	| postfix_expression DEC_OP   {$$ = new expression(); $$->size = 1; $$->opera = "PDEC"; $$->right = $1; $$->op = 1;$$->count = $1->count + 1;
								   if(!$1->canbeleft)
								   {
										$$->opera = "POST_DEC_OP  运算符必须是左值";
										iferror = 1;
								   }
								   $$->type = $1->type;
								  }
	| '(' type_name ')' '{' initializer_list '}'    {printf("强制类型转换   ");}
	| '(' type_name ')' '{' initializer_list ',' '}'
	;

argument_expression_list
	: assignment_expression  {$$ = $1;}
	| argument_expression_list ',' assignment_expression {$$ = $1; $$->last->next = $3; $$->last = $3;}
	;

unary_expression
	: postfix_expression {$$ = $1;}
	| INC_OP unary_expression {$$ = new expression(); $$->size = 1; $$->opera = "FINC"; $$->right = $2;$$->count = $2->count + 1;
								if(!$2->canbeleft)
								{
									$$->opera = "FRONT_INC_OP  运算符必须是左值";iferror = 1;
								}
								$$->type = $2->type;$$->sym = $2->sym;$$->canbeleft = 1;$$->op = 2;
							  }
	| DEC_OP unary_expression  {$$ = new expression(); $$->size = 1; $$->opera = "FDEC"; $$->right = $2;$$->count = $2->count + 1;
								if(!$2->canbeleft)
								{
									$$->opera = "FRONT_DEC_OP  运算符必须是左值";iferror = 1;
								}
								$$->type = $2->type;$$->sym = $2->sym;
								$$->canbeleft = 1;$$->op = 2;
							   }
	| unary_operator cast_expression {$$ = new expression(); $$->size = 1; $$->opera = $1; $$->right = $2; $$->type = $2->type;
									  $$->count = $2->count + 1;
									  if(strcmp($1, "ADDR") == 0)
									  {
										$$->list.push_back(0);
										for(int i = 0; i < $2->list.size(); ++i)
										{
											$$->list.push_back($2->list[i]);
										}
									  }
									  if(strcmp($1, "STAR") == 0)
									  {
										if($2->list.size() != 0)
										{
											for(int i = 1; i < $2->list.size(); ++i)
											{
												$$->list.push_back($2->list[i]);
											}
											if($$->list.size() == 0 || $2->list[0] == 0)
												$$->canbeleft = 1;
										}
										else
											iferror = 1;
									  }
										if(strcmp($1, "FEI") == 0)
										{
											$$->type = 2;
										}
									 }
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&' {$$ = "ADDR";}
	| '*' {$$ = "STAR";}
	| '+' {$$ = "POSI";}
	| '-' {$$ = "FU";}
	| '~' {$$ = "QUFAN";}
	| '!' {$$ = "FEI";}
	;

cast_expression
	: unary_expression {$$ = $1;}
	| '(' type_name ')' cast_expression {
											$$ = new expression(); $$->opera = "TYPE_CHANGE"; $$->size = 1; $$->sym = $2;
											$$->right = $4;$$->type = $2->ty;
											for(int i = 0; i < $2->list.size(); ++i)
											{
												$$->list.push_back($2->list[i]);
											}
										}
	;

multiplicative_expression
	: cast_expression {$$ = $1;}
	| multiplicative_expression '*' cast_expression  {$$ = new expression(); $$->size = 2; $$->left = $1;$$->right = $3; $$->opera = "*";
														$$->type = $1->type > $3->type ? $1->type : $3->type;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
													 }
	| multiplicative_expression '/' cast_expression  {$$ = new expression(); $$->size = 2; $$->left = $1;$$->right = $3; $$->opera = "/";
													  $$->type = $1->type > $3->type ? $1->type : $3->type;$$->op = 1;
													  $$->count = $1->count + $3->count + 1;
													 }
	| multiplicative_expression '%' cast_expression  {$$ = new expression(); $$->size = 2; $$->left = $1;$$->right = $3; $$->opera = "%";
														if($1->type == 3 || $3->type == 3)
														{
															$$->opera = "MOD_OP  运算符必须为整数";iferror = 1;
														}
														$$->type = 2;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
													 }
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression '+' multiplicative_expression  {$$ = new expression(); $$->size = 2; $$->left = $1;$$->right = $3; $$->opera = "+";
															if($1->list.size() == 0 && $3->list.size() == 0)
															{
																$$->type = $1->type > $3->type ? $1->type : $3->type;
															}
															else
															{
																$$->type = 2;
																expression *temp;
																if($1->list.size() != 0)
																	temp = $1;
																else
																	temp = $3;
																for(int i = 0; i < temp->list.size(); ++i)
																	$$->list.push_back(temp->list[i]);
															}
															$3->type;$$->op = 1;
															$$->count = $1->count + $3->count + 1;
														 }
	| additive_expression '-' multiplicative_expression  {$$ = new expression(); $$->size = 2; $$->left = $1;$$->right = $3; $$->opera = "-";
															$$->type = $1->type > $3->type ? $1->type : $3->type;$$->op = 1;
															$$->count = $1->count + $3->count + 1;
														 }
	;

shift_expression
	: additive_expression {$$ = $1;}
	| shift_expression LEFT_OP additive_expression   {$$ = new expression(); $$->size = 2; $$->opera = "<<"; $$->left = $1; $$->right = $3;
														$$->type = 2;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
													  if($1->type == 3 || $3->type == 3)
													  {
															$$->opera = "LEFT_OP  运算符必须为整数";iferror = 1;
													  }
													 }
	| shift_expression RIGHT_OP additive_expression  {$$ = new expression(); $$->size = 2; $$->opera = ">>"; $$->left = $1; $$->right = $3;
														$$->type = 2;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
													  if($1->type == 3 || $3->type == 3)
														{
															$$->opera = "RIGHT_OP  运算符必须为整数";iferror = 1;
														}
													 }
	;

relational_expression
	: shift_expression {$$ = $1;}
	| relational_expression '<' shift_expression   {$$ = new expression(); $$->size = 2; $$->opera = "<"; $$->left = $1; $$->right = $3;
														$$->type = 2;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
												   }
	| relational_expression '>' shift_expression   {$$ = new expression(); $$->size = 2; $$->opera = ">"; $$->left = $1; $$->right = $3;
														$$->type = 2;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
												   }
	| relational_expression LE_OP shift_expression  {$$ = new expression(); $$->size = 2; $$->opera = "<="; $$->left = $1; $$->right = $3;
														 $$->type = 2;$$->op = 1;
														 $$->count = $1->count + $3->count + 1;
													}
	| relational_expression GE_OP shift_expression  {$$ = new expression(); $$->size = 2; $$->opera = ">="; $$->left = $1; $$->right = $3;
														 $$->type = 2;$$->op = 1;
														 $$->count = $1->count + $3->count + 1;
													}
	;

equality_expression
	: relational_expression {$$ = $1;}
	| equality_expression EQ_OP relational_expression  {$$ = new expression(); $$->size = 2; $$->opera = "=="; $$->left = $1; $$->right = $3;
															$$->type = 2;$$->op = 1;
															$$->count = $1->count + $3->count + 1;
													   }
	| equality_expression NE_OP relational_expression  {$$ = new expression(); $$->size = 2; $$->opera = "+="; $$->left = $1; $$->right = $3;
															$$->type = 2;$$->op = 1;
															$$->count = $1->count + $3->count + 1;
													   }
	;

and_expression
	: equality_expression {$$ = $1;}
	| and_expression '&' equality_expression  {$$ = new expression(); $$->size = 2; $$->opera = "&"; $$->left = $1; $$->right = $3;
													$$->type = 2;$$->op = 1;
													$$->count = $1->count + $3->count + 1;
											   if($1->type == 3 || $3->type == 3)
												{
													$$->opera = "BIT_AND  运算符必须为整数";iferror = 1;
												}
											  }
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	| exclusive_or_expression '^' and_expression  {$$ = new expression(); $$->size = 2; $$->opera = "^"; $$->left = $1; $$->right = $3;
														$$->type = 2;$$->op = 1;
														$$->count = $1->count + $3->count + 1;
												   	if($1->type == 3 || $3->type == 3)
													{
														$$->opera = "BIT_XOR  运算符必须为整数";iferror = 1;
													}
												  }
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression  {$$ = new expression(); $$->size = 2; $$->opera = "|"; $$->left = $1; $$->right = $3;
															   	$$->type = 2;$$->op = 1;
																$$->count = $1->count + $3->count + 1;
															if($1->type == 3 || $3->type == 3)
															{
																$$->opera = "BIT_OR  运算符必须为整数";iferror = 1;
															}
														   }
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression  {$$ = new expression(); $$->size = 2; $$->opera = "&&"; $$->left = $1; $$->right = $3;
																$$->type = 2;$$->op = 1;
																$$->count = $1->count + $3->count + 1;
															 }
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression {$$ = new expression(); $$->size = 2; $$->opera = "||"; $$->left = $1; $$->right = $3;
															$$->type = 2;$$->op = 1;
															$$->count = $1->count + $3->count + 1;
														 }
	;

conditional_expression
	: logical_or_expression {$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression {$$ = new expression(); $$->size = 3; $$->opera = "QUES"; 
																	   $$->left = $1; $$->right = $3; $$->rr = $5;
																	  }
	;

assignment_expression
	: conditional_expression {$$ = $1;}
	| unary_expression assignment_operator assignment_expression   {$$ = new expression(); $$->size = 2; $$->opera = $2; $$->left = $1; $$->right = $3;
																	$$->count = $1->count + $3->count + 1;
																	if(strcmp($2,"=") == 0)
																	{
																		if($1->list.size() != 0 || $3->list.size() != 0)
																		{
																			if($1->list.size() != $3->list.size())
																			{
																				$$->opera = "ASSIGN_OP  类型不匹配";iferror = 1;
																			}
																			else
																			{
																				//除了第一个指针可以指向数组 剩下的都要相等
																				for(int i = 1; i < $1->list.size(); ++i)
																				{
																					if($1->list[i] != $3->list[i])
																					{
																						$$->opera = "ASSIGN_OP  类型不匹配";iferror = 1;
																						break;
																					}
																				}
																			}
																		}
																		if(!$1->canbeleft)
																		{
																			$$->opera = "ASSIGN_OP  运算符必须为左值";iferror = 1;
																		}
																	}
																	$$->type = $1->type;$$->op = 2;
																   }
	;

assignment_operator
	: '='  {$$ = "=";}
	| MUL_ASSIGN  {$$ = "*=";}
	| DIV_ASSIGN  {$$ = "/=";}
	| MOD_ASSIGN  {$$ = "%=";}
	| ADD_ASSIGN  {$$ = "+=";}
	| SUB_ASSIGN  {$$ = "-=";}
	| LEFT_ASSIGN  {$$ = "<<=";}
	| RIGHT_ASSIGN  {$$ = ">>=";}
	| AND_ASSIGN   {$$ = "&=";}
	| XOR_ASSIGN  {$$ = "^=";}
	| OR_ASSIGN   {$$ = "|=";}
	;

expression
	: assignment_expression  {$$ = $1;}
	| expression ',' assignment_expression {$$ = new expression(); $$->opera = "COMMA"; $$->size = 2; $$->left = $1; $$->right = $3;
											$$->count = $1->count + $3->count;
											$$->type = $3->type;
											$$->canbeleft = $3->canbeleft;
										   }
	;

constant_expression
	: conditional_expression	/* with constraints */
	;

declaration
	: declaration_specifiers ';'   {printf("声明   ");}
	| declaration_specifiers  init_declarator_list ';'  {$$ = new expression();
														 $$->opera = "DECL";
														 $$->type = $1;
														 $$->size = -1;
														 $$->comstmt = $2;
														 $$->count = $2->count;
														}
	;

declaration_specifiers     /*类型符   用来声明类型*/
	: storage_class_specifier declaration_specifiers   {printf("typedef操作   ");}
	| type_specifier declaration_specifiers
	| type_specifier   {$$=$1;}
	;

init_declarator_list
	: init_declarator {$$ = new expression(); $$->opera = "INITLIST"; $$->size = -1; $$->comstmt = $1; $$->count = $1->count;}
	| init_declarator_list ',' init_declarator {$$ = $1; $$->comstmt->last->next = $3; $$->comstmt->last = $3; $$->count += $3->count;}
	;

init_declarator
	: declarator '=' initializer    { $$ = new expression();$$->size = 2; $$->sym = $1; $$->opera = "INITDEF"; $$->right = $3; $$->type = curtype;
									  $$->count = $3->count;
									  if($1->list.size() != 0)
									  {
										if($1->list[0] == 0)
										{
											if($1->ty != $3->type)
											{
												$$->opera = "无法类型转换";
												iferror = 1;
											}
											else
											{
												if($1->list.size() != $3->list.size())
												{
													$$->opera = "类型不匹配";
													iferror = 1;
												}
											}
										}
										else if($3->comstmt != NULL)
										{
											$$->opera = "ARRAYDEF";
											if($1->list[0] == -2)
											{
												$1->list[0] = $3->comstmt->arraysize;
											}
											int *size = new int[$1->list.size() + 1];
											int *q = new int[$1->list.size()];
											size[$1->list.size()] = 1;
											int check = 0;
											for(int i = $1->list.size()-1; i >= 0; --i )
											{
												if($1->list[i] == -2)
												{
													check = 1;iferror = 1;
													$$->opera = "只能第一项为空";
													break;
												}
												size[i] = size[i+1] * $1->list[i];
												q[i] = $1->list[i];
											}
											if(!check)
											{
												expression *e = $3->comstmt;
													
												if( e != NULL && e->arraysize > size[0])
													$$->opera = "初始项太多";
												else
												{
													while(e != NULL)
													{
														if(e->compare(q + 1,$1->list.size() - 1, size + 1))
														{
															$$->opera = "初始项太多";
															break;
														}
														e = e->next;
													}
												}
											}
										}
									  }
									  else
									  {
										if($3->comstmt != NULL || $1->type != $3->type)
										{
											$$->opera = "类型不匹配";
											iferror = 1;
										}
									  }
									}
	| declarator  {$$ = new expression(); $$->size = 0; $$->sym = $1; $$->opera = "INITDECL"; $$->count = 1; $$->type = $1->type;}
	;

storage_class_specifier
	: TYPEDEF	/* identifiers must be flagged as TYPEDEF_NAME */
	;

type_specifier
	: VOID   {$$=0; curtype = $$;}
	| CHAR   {$$=1; curtype = $$;}
	| INT    {$$=2; curtype = $$;}
	| LONG
	| FLOAT   {$$=3; curtype = $$;}
	| DOUBLE  {$$ = 3; curtype = $$;}
	| SIGNED
	| BOOL
	| struct_or_union_specifier {$$ = curtype;}
	| enum_specifier
	| TYPEDEF_NAME		/* after it has been defined as such */
	;

struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'   {}
	| struct_or_union IDENTIFIER '{' struct_declaration_list '}'  {
																  }
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT {$$ = "STRUCT";}
	| UNION {$$ = "UNION";}
	;

struct_declaration_list
	: struct_declaration  {$$ = $1;}
	| struct_declaration_list struct_declaration  {
												  }
	;

struct_declaration
	: specifier_qualifier_list ';'	/* for anonymous struct/union */
	| specifier_qualifier_list struct_declarator_list ';'  {
															}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier  {$$ = $1;}
	;

struct_declarator_list
	: struct_declarator  {}
	| struct_declarator_list ',' struct_declarator  {}
	;

struct_declarator
	: ':' constant_expression
	| declarator ':' constant_expression
	| declarator  {$$ = $1;}
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator	/* identifiers must be flagged as ENUMERATION_CONSTANT */
	: enumeration_constant '=' constant_expression
	| enumeration_constant
	;


declarator     /*标识修饰符*/
	: pointer direct_declarator {
									for(int i=0; i< $1; ++i)
									{
										$2->list.push_back(0);
									}
									$$ = $2;
								}
	| direct_declarator   {$$ = $1;}
	;

direct_declarator
	: IDENTIFIER   {$$ = new symbol($1); $$->type = curtype; string a = (char*)$1;
					if (strcmp($1, "main") != 0)
					{
						sv.push_back($$);
					}
					map<string, symbol*>::iterator iter;
					iter = (symboltable.front()).find(a);
					if(iter == (symboltable.front()).end())
					{
						(symboltable.front()).insert(pair<string, symbol*>(a,$$));
						$$->ty = curtype;
					}
					else
					{
						yyerror("变量重定义");
					}
				   }
	| '(' declarator ')' {$$ = $2;}
	| direct_declarator '[' ']'	{ $1->list.push_back(-2); $$ = $1;}
	| direct_declarator '[' '*' ']'
	| direct_declarator '[' assignment_expression ']'  { $1->list.push_back(*(int*)$3->val); $$ = $1;}
	| direct_declarator '(' parameter_type_list ')'   {}
	| direct_declarator '(' ')'
	| direct_declarator '(' identifier_list ')'
	;

pointer
	: '*' pointer { $$ = $2 + 1;}
	| '*' {$$ = 1;}
	;


parameter_type_list
	: parameter_list    {$$ = $1;}
	;

parameter_list
	: parameter_declaration  {$$ = new parameterlist(); $$->param.push_back($1);}
	| parameter_list ',' parameter_declaration  {$1->param.push_back($3); $$ = $1;}
	;

parameter_declaration
	: declaration_specifiers declarator  {$$ = $2; $$->type = $1;}  
	| declaration_specifiers abstract_declarator
	| declaration_specifiers  {$$ = new symbol(); $$->type = $1;}
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list abstract_declarator {$$ = new symbol();$$->ty = $1;
													for(int i = 0; i < $2; ++i)
													{
														$$->list.push_back(0);
													}
												   }
	| specifier_qualifier_list
	;

abstract_declarator
	: pointer direct_abstract_declarator
	| pointer
	| direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' '*' ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: '{' initializer_list '}'  {$$ = new expression(); $$->comstmt = $2; $$->opera = "LIST"; $$->count = $2->count;}
	| '{' initializer_list ',' '}'
	| '{' '}'	{$$ = new expression(); $$->opera = "LIST";}
	| assignment_expression   {$$ = $1; ++$$->count;}
	;

initializer_list
	: designation initializer
	| initializer	{$$ = $1;}
	| initializer_list ',' designation initializer
	| initializer_list ',' initializer {$$ = $1; $$->last->next = $3; $$->last = $3; ++$$->arraysize; $$->count += $3->count;}
	;

designation
	: designator_list '='
	;

designator_list
	: designator
	| designator_list designator
	;

designator
	: '[' constant_expression ']'
	| '.' IDENTIFIER
	;


statement
	: labeled_statement 
	| compound_statement  {$$ = $1;}
	| expression_statement {$$ = $1;}
	| selection_statement  {$$ = $1;}
	| iteration_statement  {$$ = $1;}
	| jump_statement {$$ = $1;}
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	;

compound_statement
	: '{' '}'
	| '{'  block_item_list '}'  {$$ = new expression(); $$->opera = "COM"; $$->size = -1; $$->comstmt = $2; $$->count = $2->count;}
	;

block_item_list
	: block_item  {$$ = $1; $$->count = $1->count;}
	| block_item_list block_item  {$$ = $1; $$->last->next = $2; $$->last = $2; $$->count += $2->count;}
	;

block_item
	: declaration {$$ = $1;}
	| statement  {$$ = $1;}
	;

expression_statement
	: ';'  {$$ = new expression(); $$->opera = "NULL"; $$->size = -1; $$->count = 1;}
	| expression ';'  {$$ = $1;}
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement  {$$ = new expression(); $$->size = 3; $$->opera = "IFELSE"; $$->left = $3; $$->right = $5;
													   $$->rr = $7;
													   $$->count = $3->count + $5->count + $7->count + 2;
													  }
	| IF '(' expression ')' statement  {$$ = new expression(); $$->size = 2; $$->opera = "IF"; $$->left = $3; $$->right = $5;
										$$->count = $3->count + $5->count + 1;
									   }
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: m WHILE '(' expression ')' statement  {$$ = new expression(); $$->opera = "WHILE"; $$->size = 2; $$->left = $4; $$->right = $6; symboltable.pop_front(); $$->count = $4->count + $6->count + 2;}
	| m DO statement WHILE '(' expression ')' ';' {$$ = new expression(); $$->opera = "DOWHILE"; $$->size = 2; $$->left = $3; $$->right = $6; symboltable.pop_front();}
	| m FOR '(' expression_statement expression_statement ')' statement   {$$ = new expression(); $$->size = 3; $$->opera = "FOR"; $$->left = $4; $$->right = $5; $$->rrr = $7; symboltable.pop_front(); $$->count = $4->count + $5->count + $7->count + 2;}
	| m FOR '(' expression_statement expression_statement expression ')' statement {$$ = new expression(); $$->size = 4; $$->opera = "FOR"; $$->left = $4; $$->right = $5; $$->rr = $6; $$->rrr = $8; symboltable.pop_front();$$->count = $4->count + $5->count + $6->count + $8->count + 2;}
	| m FOR '(' declaration expression_statement ')' statement    {$$ = new expression(); $$->opera = "FOR"; $$->size = 3; $$->left = $4; $$->right = $5; $$->rrr = $7; symboltable.pop_front(); $$->count = $4->count + $5->count + $7->count + 2;}
	| m FOR '(' declaration expression_statement expression ')' statement {$$ = new expression(); $$->opera = "FOR"; $$->size = 4; $$->left = $4; $$->right = $5; $$->rr = $6; $$->rrr = $8; symboltable.pop_front(); $$->count = $4->count + $5->count + $6->count + $8->count + 2;}
	;

m : {map<string,symbol*> *p = new map<string,symbol*>; symboltable.push_front(*p);}
  ;
jump_statement
	: CONTINUE ';'
	| BREAK ';'
	| RETURN ';'  {$$ = new expression(); $$->size = -1; $$->opera = "RETURN";}
	| RETURN expression ';'   {$$ = new expression(); $$->size = 1; $$->opera = "RETURN"; $$->right = $2;}
	;

translation_unit
	: external_declaration {start = $1; $$ = $1;}
	| translation_unit external_declaration {$$ = $1;$$->last->next = $2; $$->last = $2;}
	;

external_declaration
	: function_definition {$$ = $1;}
	| declaration     {$$ = $1;} /* 这的声明可以放在全局符号表里*/
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement    {printf("带参数函数声明   ");}
	| declaration_specifiers  declarator compound_statement { $$ = new expression(); $$->sym = $2;  $2->type = $1;
															  $$->opera = "FUNC";
															  $$->comstmt = $3;
															}
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

%%
ofstream out("zhongjian.txt");
ofstream outfile("end.txt");
map<int, int> tiaozhuan;
int countconst = 1, countarray = 1;
map<string, symbol*> realtable;

void arraydef(symbol *sym, expression *exp, int base, int cur, int depth, int &label, int &temp, int length);
string func(expression *p, int &label, int &temp)
{
	string s;
	if(p->op == 1)
	{
		if(p->size == 1)
		{
			string s1 = func(p->right,label,temp);
			out<<label++<<"\t"<<p->opera<<"\t"<<s1<<"\t"<<""<<"\t"<<"_t"<<temp<<endl;
		}
		else
		{
			string s1 = func(p->left,label,temp);
			string s2 = func(p->right,label,temp);
			out<<label++<<"\t"<<p->opera<<"\t"<<s1<<"\t"<<s2<<"\t"<<"_t"<<temp<<endl;
		}
		//把临时变量存入符号表
		char *o = new char[10];
		sprintf(o,"_t%d",temp);
		symbol *ss = new symbol(o);
		ss->type = p->type;ss->iftemp=1;
		for(int kk = 0; kk < p->list.size(); ++kk)
			ss->list.push_back(p->list[kk]);
		string sname = o;
		realtable.insert(pair<string, symbol*>(sname, ss));

		char *w = ss->type == 3 ? " dq 0" : " dd 0";
		outfile<<"		"<< ss->name << w <<endl;
		
		ostringstream os;
		os<<"_t"<<temp++;
		return os.str();
	}
	if(p->op == 2)	//前加加减减和赋值
	{
		if(p->size == 2)
		{
			string s1 = func(p->left,label,temp);
			string s2 = func(p->right,label,temp);
			out<<label++<<"\t"<<p->opera<<"\t"<<s2<<"\t"<<""<<"\t"<<s1<<endl;
			return s1;
		}
		else
		{
			string s1 = func(p->right,label,temp);
			out<<label++<<"\t"<<p->opera<<"\t"<<s1<<"\t"<<""<<"\t"<<s1<<endl;
			return s1;
		}
	}
	if(strcmp(p->opera, "FU") == 0)
	{
		string s1 = func(p->right, label, temp);
		out<<label++<<"\t"<<p->opera<<"\t"<<s1<<"\t"<<""<<"\t"<<"_t"<<temp<<endl;
		char *o = new char[10];
		sprintf(o,"_t%d",temp);
		symbol *ss = new symbol(o);
		ss->type = p->right->type;
		string sname = o;
		realtable.insert(pair<string, symbol*>(sname, ss));
		char *w = ss->type == 3 ? " dq 0" : " dd 0";
		outfile<<"		"<< ss->name << w <<endl;
		
		ostringstream os;
		os<<"_t"<<temp++;
		return os.str();
	}
	if(strcmp(p->opera,"ID") == 0)
	{
		string s1(p->sym->name);
		return s1;
	}
	if(strcmp(p->opera, "VAL") == 0)		//把常量存入符号表
	{
		char *constname = new char[10];
		sprintf(constname, "_const%d", countconst++);
		symbol *ss = new symbol(constname);
		ss->type = p->type;
		ss->val = p->val;
		string sname = constname;

		char *w = new char[10];
		if(ss->type == 3)
			sprintf(w, " dq %f", *(double*)ss->val);
		else
			sprintf(w, " dd %d", *(int*)ss->val);
		outfile<<"		"<< ss->name << w <<endl;

		realtable.insert(pair<string, symbol*>(sname, ss));
		return constname;
	}
	if(strcmp(p->opera, "DECL")==0 || strcmp(p->opera, "INITLIST") == 0)
	{
		expression *q = p->comstmt;
		while(q != NULL)
		{
			func(q,label,temp);
			q = q->next;
		}
		return s;
	}
	if(strcmp(p->opera, "ADDR") == 0)
	{
		string s1 = func(p->right, label, temp);
		out<<label++<<"\t"<<"ADDR"<<"\t"<<s1<<"\t"<<""<<"\t"<<"_t"<<temp<<endl;
		char *o = new char[10];
		sprintf(o,"_t%d",temp);
		symbol *ss = new symbol(o);
		ss->type = p->type;ss->iftemp=1;
		for(int kk = 0; kk < p->list.size(); ++kk)
			ss->list.push_back(p->list[kk]);
		outfile<<"		"<< ss->name <<" dd 0"<<endl;
		string sname = o;
		realtable.insert(pair<string, symbol*>(sname, ss));
		ostringstream os;
		os<<"_t"<<temp++;
		return os.str();
	}
	if(strcmp(p->opera, "STAR") == 0)
	{
		string s1 = func(p->right, label, temp);
		out<<label++<<"\t"<<"STAR"<<"\t"<<s1<<"\t"<<""<<"\t"<<"_t"<<temp<<endl;
		char *o = new char[10];
		sprintf(o,"_t%d",temp);
		symbol *ss = new symbol(o);
		ss->type = p->type;ss->iftemp=1;
		for(int kk = 0; kk < p->list.size(); ++kk)
			ss->list.push_back(p->list[kk]);
		ss->beleft = p->canbeleft;
		outfile<<"		"<< ss->name <<" dd 0"<<endl;
		string sname = o;
		realtable.insert(pair<string, symbol*>(sname, ss));
		ostringstream os;
		os<<"_t"<<temp++;
		return os.str();
	}
	if(strcmp(p->opera, "ARRAY") == 0)
	{
		string s1 = func(p->left, label, temp);
		string s2 = func(p->right, label, temp);
		if(strcmp(p->left->opera, "ID") == 0  && p->left->list[0] != 0)
		{
			out<<label++<<"\t"<<"lea"<<"\t"<<s1<<"\t"<<s2<<"\t"<<"_t"<<temp<<endl;
		}
		else
		{
			out<<label++<<"\t"<<"ARRAY"<<"\t"<<s1<<"\t"<<s2<<"\t"<<"_t"<<temp<<endl;
		}
		char *o = new char[10];
		sprintf(o,"_t%d",temp);
		symbol *ss = new symbol(o);
		for(int it = 0; it < p->list.size(); ++it)
			ss->list.push_back(p->list[it]);
		ss->beleft = p->canbeleft;
		outfile<<"		"<< ss->name <<" dd 0"<<endl;
		ss->type = p->type;ss->iftemp=1;
		string sname = o;
		realtable.insert(pair<string, symbol*>(sname, ss));
		ostringstream os;
		os<<"_t"<<temp++;
		return os.str();
	}
	if(strcmp(p->opera, "ARRAYDEF") == 0)
	{
		bool checktype = 0;int base = 4;int length = p->sym->list.size();
		for(int it = p->sym->list.size()-1; it >=0; --it)
		{
			if(p->sym->list[it] == 0)	//说明中间有个修饰符是指针
			{
				length = it+1;
				checktype = 1;break;
			}
		}
		if(!checktype)	//说明是一个数组 中间没出现指针
			base = p->sym->type == 3 ? 8 : 4;
		arraydef(p->sym, p->right, base, 0, 0, label, temp, length);
	}
	if(strcmp(p->opera, "FUNC") == 0)
	{
		func(p->comstmt, label, temp);
	}
	if(strcmp(p->opera, "INITDEF") == 0)
	{
		string s1 = func(p->right,label,temp);
		out<<label++<<"\t"<<"="<<"\t"<<s1<<"\t"<<""<<"\t"<<p->sym->name<<endl;
	}
	if(strcmp(p->opera, "INITDECL") == 0)
	{
		out<<label++<<"\t"<<"DECL"<<"\t"<<p->sym->name<<"\t"<<""<<"\t"<<p->sym->name<<endl;
	}
	if(strcmp(p->opera, "IF") == 0)
	{
		string s1 = func(p->left,label,temp);
		out<<label++<<"\t"<<"IFF"<<"\t"<<s1<<"\t"<<""<<"\t"<<label+p->right->count<<endl;
		map<int, int>::iterator iter;
		iter = tiaozhuan.find(label+p->right->count);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(label+p->right->count, 1));
		func(p->right,label,temp);
	}
	if(strcmp(p->opera, "IFELSE") == 0)
	{
		string s1 = func(p->left, label, temp);
		out<<label++<<"\t"<<"IFF"<<"\t"<<s1<<"\t"<<""<<"\t"<<label+p->right->count+1<<endl;
		map<int, int>::iterator iter;
		iter = tiaozhuan.find(label+p->right->count+1);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(label+p->right->count + 1, 1));
		func(p->right,label,temp);
		out<<label++<<"\t"<<"GOTO"<<"\t"<<""<<"\t"<<""<<"\t"<<label+p->rr->count<<endl;
		iter = tiaozhuan.find(label+p->rr->count);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(label+p->rr->count, 1));
		func(p->rr, label, temp);
	}
	if(strcmp(p->opera,"COM") == 0)	//复合语句
	{
		expression *q = p->comstmt;
		while(q != NULL)
		{
			func(q,label,temp);
			q = q->next;
		}
	}
	if(strcmp(p->opera, "COMMA") == 0)	//逗号表达式
	{
		func(p->left, label, temp);
		string s1 = func(p->right, label, temp);
		return s1;
	}
	if(strcmp(p->opera, "FOR") == 0)
	{
		func(p->left,label,temp);
		int ll = label;
		string s1 = func(p->right,label,temp);
		int co;
		if(p->rr != NULL)
			co = label+p->rr->count + p->rrr->count + 2;//加上下面两句
		else
			co = label + + p->rrr->count + 2;
		out<<label++<<"\t"<<"IFF"<<"\t"<<s1<<"\t"<<""<<"\t"<<co<<endl;
		map<int, int>::iterator iter;
		iter = tiaozhuan.find(co);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(co, 1));
		func(p->rrr,label,temp);
		if(p->rr != NULL)
			func(p->rr,label,temp);
		out<<label++<<"\t"<<"GOTO"<<"\t"<<""<<"\t"<<""<<"\t"<<ll<<endl;
		iter = tiaozhuan.find(ll);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(ll, 1));
	}
	if(strcmp(p->opera, "WHILE") == 0)
	{
		int ll = label;
		string s1 = func(p->left,label,temp);
		out<<label++<<"\t"<<"IFF"<<"\t"<<s1<<"\t"<<""<<"\t"<<label+p->right->count + 1<<endl;
		map<int, int>::iterator iter;
		iter = tiaozhuan.find(label+p->right->count + 1);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(label+p->right->count + 1, 1));
		func(p->right,label,temp);
		out<<label++<<"\t"<<"GOTO"<<"\t"<<""<<"\t"<<""<<"\t"<<ll<<endl;
		iter = tiaozhuan.find(ll);
		if(iter == tiaozhuan.end())
			tiaozhuan.insert(pair<int, int>(ll, 1));
	}
	if(strcmp(p->opera, "READ") == 0)
	{
		string s1 = func(p->comstmt, label, temp);
		out<<label++<<"\t"<<"READ"<<"\t"<<s1<<"\t"<<""<<"\t"<<""<<endl;
	}
	if(strcmp(p->opera, "WRITE") == 0)
	{
		string s1 = func(p->comstmt, label, temp);
		out<<label++<<"\t"<<"WRITE"<<"\t"<<s1<<"\t"<<""<<"\t"<<""<<endl;
	}
	if(strcmp(p->opera, "RETURN") == 0)
	{
		out<<label++<<"\t"<<"RETURN"<<"\t"<<""<<"\t"<<""<<"\t"<<""<<endl;
	}
	return s;
}

void arraydef(symbol *sym, expression *exp, int base, int cur, int depth, int &label, int &temp, int length)
{
	if(strcmp(exp->opera, "LIST") == 0)
	{
		int step = 1;
		for(int qq = length - 1; qq > depth; --qq)
		{
			step *= sym->list[qq];
		}
		expression *p = exp->comstmt;
		while(p != NULL)
		{
			if(strcmp(p->opera, "LIST") == 0)
			{
				arraydef(sym, p, base, cur, depth + 1, label, temp, length);
				p = p->next;
				cur += base * step;
			}
			else
			{
				arraydef(sym, p, base, cur, depth + 1, label, temp, length);break;
			}
		}
	}
	else
	{
		expression *p = exp;
		while(p != NULL)
		{
			string ss = func(p, label, temp);
			out<<label++<<"\t"<<"arydef"<<"\t"<<ss<<"\t"<<sym->name<<"\t"<<sym->name<<"["<<cur<<"]"<<endl;
			cur += base;
			p = p->next;
		}
	}
}
int main()
{
  freopen("a.txt","r",stdin);
  symboltable.push_front(ss);
  yyparse();
  if(!iferror)
  {
	out<<"Label"<<"\t"<<"op"<<"\t"<<"arg1"<<"\t"<<"arg2"<<"\t"<<"result"<<endl;
	int label = 1, temp = 1;
	outfile << ".386" << endl;
	outfile << ".model flat, stdcall" << endl;
	outfile << "option casemap : none" << endl;
	outfile << "include \\masm32\\include\\windows.inc" << endl;
	outfile << "include \\masm32\\include\\masm32.inc" << endl;
	outfile << "include \\masm32\\include\\msvcrt.inc" << endl;
	outfile << "include \\masm32\\include\\kernel32.inc" << endl;
	outfile << "includelib \\masm32\\lib\\masm32.lib" << endl;
	outfile << "includelib \\masm32\\lib\\msvcrt.lib" << endl;
	outfile << "includelib \\masm32\\lib\\kernel32.lib" << endl;
	outfile << ".data"<<endl;
	outfile<<"		_changemode dw 3710"<<endl;	//将fistp从四舍五入变成向下取整
	for(int i = 0; i < sv.size(); ++i)		//把重名的变量名字给区分开 
	{
		strcat(sv[i]->name, "v");
		string a = sv[i]->name;
		map<string, int>::iterator iter;
		iter = checktable.find(a);
		if(iter == checktable.end())
		{
			checktable.insert(pair<string, int>(a,1));
			realtable.insert(pair<string, symbol*>(a, sv[i]));
		}
		else
		{
			int co = iter->second;
			ostringstream os;
			os<<a<<co;
			++iter->second;
			char num[5];
			sprintf(num, "%d", co);
			strcat(sv[i]->name, num);
			checktable.insert(pair<string, int>(os.str(), co+1));
			realtable.insert(pair<string, symbol*>(os.str(), sv[i]));
		}
		if(sv[i]->list.size() == 0)
		{
			char *w = sv[i]->type == 3 ? " dq 0" : " dd 0";
			outfile<<"		"<< sv[i]->name << w <<endl;
		}
		else
		{
			char *w = sv[i]->type == 3 ? " dq " : " dd ";
			if(sv[i]->list[0] == 0)
			{
				outfile<<"		"<<sv[i]->name<<" dd 0"<<endl;
			}
			else
			{
				int sum = 1;bool ifprint = 0;
				for(int it = 0; it < sv[i]->list.size(); ++it)
				{
					if(sv[i]->list[it] == 0)
					{
						outfile<<"		"<<sv[i]->name<<" dd "<<sum<<" dup (0)"<<endl;
						ifprint = 1;
						break;
					}
					else
						sum *= sv[i]->list[it];
				}
				if(!ifprint)
					outfile<<"		"<<sv[i]->name<<w<<sum<<" dup (0)"<<endl;
			}
		}
	}
	expression *p = start;
	while(p != NULL)
	{
		func(p, label,temp);
		p = p->next;
	}
	out.close();
	outfile<<"		_laji dq 0"<<endl;
	//outfile<<"		_constint dd 4"<<endl;
	//outfile<<"		_constdou dd 8"<<endl;
	outfile<<"		data db '%d',0"<<endl<<"		data1 db '%c',0"<<endl<<"		data2 db '%lf', 0"<<endl;
	outfile<<".code"<<endl<<"start:"<<endl;
	outfile<<"		fldcw _changemode"<<endl;
	ifstream in("zhongjian.txt");
	char tmp[10];
	in>>tmp>>tmp>>tmp>>tmp>>tmp;
	int xuhao = 0;char op[10];
	char arg1[20], arg2[20];
	char result[20];
	int bijiao = 1;
	for(int i = 1; i < label; ++i)
	{
		in>>xuhao>>op;
		map<int, int>::iterator iter;
		iter = tiaozhuan.find(xuhao);
		if(iter != tiaozhuan.end())
			outfile<<"L"<<xuhao<<":"<<endl;
		if(strcmp(op, "IFF") == 0)
		{
			int hh;
			in>>arg1>>hh;
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		cmp eax, 0"<<endl;
			outfile<<"		je L"<<hh<<endl;
		}
		if(strcmp(op, "DECL") == 0)
		{
			in>>tmp>>tmp;
		}
		if(strcmp(op, "READ") == 0)
		{
			in>>arg1;
			map<string, symbol*>::iterator it;
			it = realtable.find(arg1);
			if(it->second->type == 3)
				outfile<< "		invoke crt_scanf,addr data2,addr " << arg1 << endl;
			else if(it->second->type == 2)
				outfile<< "		invoke crt_scanf,addr data,addr " << arg1 << endl;
			else
				outfile<< "		invoke crt_scanf,addr data1,addr " << arg1 << endl;
		}
		if(strcmp(op, "WRITE") == 0)
		{
			in>>arg1;
			map<string, symbol*>::iterator it;
			it = realtable.find(arg1);
			if(it->second->beleft)
			{	
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it->second->type == 1)
				outfile << "		invoke crt_printf,addr data1, " << arg1 << endl;
			else if(it->second->type ==2)
				outfile << "		invoke crt_printf,addr data, " << arg1 << endl;
			else
				outfile << "		invoke crt_printf,addr data2, " << arg1 << endl;
		}
		if(strcmp(op, "RETURN") == 0)
		{
			outfile<<"		jmp lend"<<endl;
		}

		if(strcmp(op, "lea") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			int step = 1;bool ifptr = 0;
			for(int k = 1; k < it1->second->list.size(); ++k)
			{
				if(it1->second->list[k] == 0)
				{
					step *= 4;ifptr = 1;break;
				}
				else
					step *= it1->second->list[k];
			}
			if(!ifptr)
				step *= it1->second->type == 3 ? 8 : 4;
			outfile<<"		mov eax, "<<step<<endl;
			outfile<<"		imul "<<arg2<<endl;
			outfile<<"		lea eax, "<<arg1<<"[eax]"<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "ADDR") == 0)
		{
			in>>arg1>>result;
			outfile<<"		lea eax, "<<arg1<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "STAR") == 0)
		{
			in>>arg1>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "ARRAY") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			int step = 1;bool ifptr = 0;
			for(int k = 1; k < it1->second->list.size(); ++k)
			{
				if(it1->second->list[k] == 0)
				{
					step *= 4;ifptr = 1;break;
				}
				else
					step *= it1->second->list[k];
			}
			if(!ifptr)
				step *= it1->second->type == 3 ? 8 : 4;
			outfile<<"		mov eax, "<<step<<endl;
			outfile<<"		imul "<<arg2<<endl;
			outfile<<"		add eax, "<<arg1<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "arydef") == 0)	//数组初始化
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->type < 3 && it2->second->type < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
			else if(it1->second->type == 3)
			{
				outfile<<"		fld "<<arg1<<endl;
				if(it2->second->type == 3)
					outfile<<"		fstp "<<result<<endl;
				else
					outfile<<"		fistp "<<result<<endl;
			}
			else
			{
				outfile<<"		fild "<<arg1<<endl;
				outfile<<"		fstp "<<result<<endl;
			}
		}
		if(strcmp(op, "FINC") == 0)
		{
			in>>arg1>>tmp;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			outfile<<"		inc "<<arg1<<endl;
		}
		if(strcmp(op, "FDEC") == 0)
		{
			in>>arg1>>temp;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			outfile<<"		dec "<<arg1<<endl;
		}
		if(strcmp(op, "PDEC") == 0)
		{
			in>>arg1>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
			outfile<<"		dec "<<arg1<<endl;
		}
		if(strcmp(op, "PINC") == 0)
		{
			in>>arg1>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
			outfile<<"		inc "<<arg1<<endl;
		}
		if(strcmp(op, "FU") == 0)
		{
			in>>arg1>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it1->second->type < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		neg eax"<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
			else
			{
				outfile<<"		fld"<<arg1<<endl;
				outfile<<"		fchs"<<endl;
				outfile<<"		fstp "<<result<<endl;
			}

		}
		if(strcmp(op, "GOTO") == 0)
		{
			int hh;
			in>>hh;
			outfile<<"		jmp L"<<hh<<endl;
		}
		if(strcmp(op, "*") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			int ch = it1->second->type > it2->second->type ? it1->second->type : it2->second->type;
			if(ch < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		mov ebx, "<<arg2<<endl;
				outfile<<"		mul ebx"<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
			else if(it1->second->type < 3 || it2->second->type < 3)
			{
				if(it1->second->type < 3)
				{
					outfile<<"		fild "<<arg1<<endl;
					outfile<<"		fmul "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
				else
				{
					outfile<<"		fld "<<arg1<<endl;
					outfile<<"		fimul "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
			}
			else
			{
				outfile<<"		fld "<<arg1<<endl;
				outfile<<"		fmul "<<arg2<<endl;
				outfile<<"		fstp "<<result<<endl;
			}
		}
		if(strcmp(op, "%") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		xor edx, edx"<<endl;
			outfile<<"		div "<<arg2<<endl;
			outfile<<"		mov "<<result<<", edx"<<endl;
		}
		if(strcmp(op, "/") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			int ch = it1->second->type > it2->second->type ? it1->second->type : it2->second->type;
			if(ch < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		mov ebx, "<<arg2<<endl;
				outfile<<"		xor edx, edx"<<endl;	//清空edx 不然会出现 integer overflow 报错
				outfile<<"		div ebx"<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
			else if(it1->second->type < 3 || it2->second->type < 3)
			{
				if(it1->second->type < 3)
				{
					outfile<<"		fild "<<arg1<<endl;
					outfile<<"		fdiv "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
				else
				{
					outfile<<"		fld "<<arg1<<endl;
					outfile<<"		fidiv "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
			}
			else
			{
				outfile<<"		fld "<<arg1<<endl;
				outfile<<"		fdiv "<<arg2<<endl;
				outfile<<"		fstp "<<result<<endl;
			}
		}
		if(strcmp(op, "-") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			int ch = it1->second->type > it2->second->type ? it1->second->type : it2->second->type;
			if(ch < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		sub eax, "<<arg2<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
			else if(it1->second->type < 3 || it2->second->type < 3)
			{
				if(it1->second->type < 3)
				{
					outfile<<"		fild "<<arg1<<endl;
					outfile<<"		fsub "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
				else
				{
					outfile<<"		fld "<<arg1<<endl;
					outfile<<"		fisub "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
			}
			else
			{
				outfile<<"		fld "<<arg1<<endl;
				outfile<<"		fsub "<<arg2<<endl;
				outfile<<"		fstp "<<result<<endl;
			}
		}
		if(strcmp(op, "+") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			int ch = it1->second->type > it2->second->type ? it1->second->type : it2->second->type;
			if(ch < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		add eax, "<<arg2<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
			else if(it1->second->type < 3 || it2->second->type < 3)
			{
				if(it1->second->type < 3)
				{
					outfile<<"		fild "<<arg1<<endl;
					outfile<<"		fadd "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
				else
				{
					outfile<<"		fld "<<arg1<<endl;
					outfile<<"		fiadd "<<arg2<<endl;
					outfile<<"		fstp "<<result<<endl;
				}
			}
			else
			{
				outfile<<"		fld "<<arg1<<endl;
				outfile<<"		fadd "<<arg2<<endl;
				outfile<<"		fstp "<<result<<endl;
			}
		}
		if(strcmp(op, ">>") == 0 || strcmp(op, "<<") == 0)
		{
			char ww[2][4] = {"sar", "shl"};
			int t = 0;
			if(strcmp(op, "<<") == 0)
				t = 1;
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		mov ecx, "<<arg2<<endl;
			outfile<<"		"<<ww[t]<<" eax, cl"<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "&") == 0 || strcmp(op, "|") == 0 || strcmp(op, "^") == 0)
		{
			char ww[3][4] = {"and", "or", "xor"};
			int t = 0;
			if(strcmp(op, "&") == 0)
				t = 0;
			else if(strcmp(op, "|") == 0)
				t = 1;
			else
				t = 2;
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<arg2<<endl;
				if(it1->second->type < 3)
					strcpy(arg2, "DWORD ptr [ebx]");
				else
					strcpy(arg2, "QWORD ptr [ebx]");
			}
			outfile<<"		mov eax, "<<arg1<<endl;
			outfile<<"		"<<ww[t]<<" eax, "<<arg2<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "&=") == 0 || strcmp(op, "|=") == 0 || strcmp(op, "^=") == 0)
		{
			char ww[3][4] = {"and", "or", "xor"};
			int t = 0;
			if(strcmp(op, "&=") == 0)
				t = 0;
			else if(strcmp(op, "|=") == 0)
				t = 1;
			else
				t = 2;
			in>>arg1>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			outfile<<"		mov eax, "<<result<<endl;
			outfile<<"		"<<ww[t]<<" eax, "<<arg1<<endl;
			outfile<<"		mov "<<result<<", eax"<<endl;
		}
		if(strcmp(op, "=") == 0)
		{
			in>>arg1>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(result);
			if(it1->second->beleft == 1)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				if(it1->second->type < 3)
					strcpy(arg1, "DWORD ptr [eax]");
				else
					strcpy(arg1, "QWORD ptr [eax]");
			}
			if(it2->second->beleft == 1)
			{
				outfile<<"		mov ebx, "<<result<<endl;
				if(it1->second->type < 3)
					strcpy(result, "DWORD ptr [ebx]");
				else
					strcpy(result, "QWORD ptr [ebx]");
			}
			if(it1->second->list.size() == 0)
			{
				if(it1->second->type < 3)
				{
					outfile<<"		mov eax, "<<arg1<<endl;
					if(it2->second->type < 3)
						outfile<<"		mov "<<result<<", eax"<<endl;
					else
					{
						outfile<<"		fild eax"<<endl;
						outfile<<"		fstp "<<result<<endl;
					}
				}
				else
				{
					outfile<<"		fld "<<arg1<<endl;
					if(it2->second->type == 3)
						outfile<<"		fstp "<<result<<endl;
					else
						outfile<<"		fistp "<<result<<endl;
				}
			}
			else
			{
				if(it1->second->iftemp)
					outfile<<"		mov eax, "<<arg1<<endl;
				else
					outfile<<"		lea eax, "<<arg1<<endl;
				outfile<<"		mov "<<result<<", eax"<<endl;
			}
		}
		if(strcmp(op, "&&") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			bool iftrue = 0;
			if(it1->second->type < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		cmp eax, 0"<<endl;
			}
			outfile<<"		jne "<<"LL"<<bijiao<<endl;		//bijiao 等于1
			outfile<<"		mov "<<result<<", 0"<<endl;
			outfile<<"		jmp LL"<<bijiao+2<<endl;
			outfile<<"LL"<<bijiao++<<":"<<endl;		//bijiao 等于2
			if(it2->second->type < 3)
			{
				outfile<<"		mov eax, "<<arg2<<endl;
				outfile<<"		cmp eax, 0"<<endl;
			}
			outfile<<"		jne "<<"LL"<<bijiao<<endl;
			outfile<<"		mov "<<result<<", 0"<<endl;
			outfile<<"		jmp LL"<<bijiao+1<<endl;
			outfile<<"LL"<<bijiao++<<":"<<endl;		//bijiao 等于3
			outfile<<"		mov "<<result<<", 1"<<endl;
			outfile<<"		jmp LL"<<bijiao<<endl;
			outfile<<"LL"<<bijiao++<<":"<<endl;
		}
		if(strcmp(op, "||") == 0)
		{
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			bool iftrue = 0;
			if(it1->second->type < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		cmp eax, 0"<<endl;
			}
			outfile<<"		je "<<"LL"<<bijiao<<endl;		//bijiao 等于1
			outfile<<"		mov "<<result<<", 1"<<endl;
			outfile<<"		jmp LL"<<bijiao+2<<endl;
			outfile<<"LL"<<bijiao++<<":"<<endl;		//bijiao 等于2
			if(it2->second->type < 3)
			{
				outfile<<"		mov eax, "<<arg2<<endl;
				outfile<<"		cmp eax, 0"<<endl;
			}
			outfile<<"		je "<<"LL"<<bijiao<<endl;
			outfile<<"		mov "<<result<<", 1"<<endl;
			outfile<<"		jmp LL"<<bijiao+1<<endl;
			outfile<<"LL"<<bijiao++<<":"<<endl;		//bijiao 等于3
			outfile<<"		mov "<<result<<", 0"<<endl;
			outfile<<"		jmp LL"<<bijiao<<endl;
			outfile<<"LL"<<bijiao++<<":"<<endl;
		}
		if(strcmp(op, "==") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0 || strcmp(op, "<") == 0 || strcmp(op, ">") == 0 || strcmp(op, "!=") == 0)
		{
			char ww[6][4] = {"jne", "ja", "jb", "jae", "jbe", "je"};
			int t = 0;
			if(strcmp(op, "<=") == 0)
				t = 1;
			else if(strcmp(op, ">=") == 0)
				t = 2;
			else if(strcmp(op, "<") == 0)
				t = 3;
			else if(strcmp(op, ">") == 0)
				t = 4;
			else if(strcmp(op, "!=") == 0)
				t = 5;
			in>>arg1>>arg2>>result;
			map<string, symbol*>::iterator it1;
			it1 = realtable.find(arg1);
			map<string, symbol*>::iterator it2;
			it2 = realtable.find(arg2);
			int ch = it1->second->type > it2->second->type ? it1->second->type : it2->second->type;
			if(ch < 3)
			{
				outfile<<"		mov eax, "<<arg1<<endl;
				outfile<<"		mov ecx, eax"<<endl;
				outfile<<"		mov eax, "<<arg2<<endl;
				outfile<<"		mov ebx, eax"<<endl;
				outfile<<"		cmp ecx, ebx"<<endl;
				outfile<<"		"<<ww[t]<<" LL"<<bijiao<<endl;		//表示不等于时跳转
				outfile<<"		mov "<<result<<", 1"<<endl;
				outfile<<"		jmp LL"<<bijiao+1<<endl;
				outfile<<"LL"<<bijiao++<<":"<<endl;
				outfile<<"		mov "<<result<<", 0"<<endl;
				outfile<<"LL"<<bijiao++<<":"<<endl;
			}
			else if(it1->second->type < 3 || it2->second->type < 3)
			{
				if(it1->second->type < 3)
				{
					outfile<<"		fild "<<arg1<<endl;
					outfile<<"		fcom "<<arg2<<endl;
					outfile<<"		fstp _laji"<<endl;	//清空寄存器
					outfile<<"		fstsw ax"<<endl;		//将浮点数的标志位保存在寄存器中
					outfile<<"		fwait"<<endl;		//等待上一条指令完成
					outfile<<"		sahf"<<endl;		//将标志位转换成cpu标志位
					outfile<<"		"<<ww[t]<<" LL"<<bijiao<<endl;
					outfile<<"		mov "<<result<<", 1"<<endl;
					outfile<<"		jmp LL"<<bijiao+1<<endl;
					outfile<<"LL"<<bijiao++<<":"<<endl;
					outfile<<"		mov "<<result<<", 0"<<endl;
					outfile<<"LL"<<bijiao++<<":"<<endl;
				}
				else
				{
					outfile<<"		fld "<<arg1<<endl;
					outfile<<"		ficom "<<arg2<<endl;
					outfile<<"		fstp _laji"<<endl;	//清空寄存器
					outfile<<"		fstsw ax"<<endl;		//将浮点数的标志位保存在寄存器中
					outfile<<"		fwait"<<endl;		//等待上一条指令完成
					outfile<<"		sahf"<<endl;		//将标志位转换成cpu标志位
					outfile<<"		"<<ww[t]<<" LL"<<bijiao<<endl;
					outfile<<"		mov "<<result<<", 1"<<endl;
					outfile<<"		jmp LL"<<bijiao+1<<endl;
					outfile<<"LL"<<bijiao++<<":"<<endl;
					outfile<<"		mov "<<result<<", 0"<<endl;
					outfile<<"LL"<<bijiao++<<":"<<endl;
				}
			}
			else
			{
				outfile<<"		fld "<<arg1<<endl;
				outfile<<"		fcom "<<arg2<<endl;
				outfile<<"		fstp _laji"<<endl;	//清空寄存器
				outfile<<"		fstsw ax"<<endl;		//将浮点数的标志位保存在寄存器中
				outfile<<"		fwait"<<endl;		//等待上一条指令完成
				outfile<<"		sahf"<<endl;		//将标志位转换成cpu标志位
				outfile<<"		"<<ww[t]<<" LL"<<bijiao<<endl;
				outfile<<"		mov "<<result<<", 1"<<endl;
				outfile<<"		jmp LL"<<bijiao+1<<endl;
				outfile<<"LL"<<bijiao++<<":"<<endl;
				outfile<<"		mov "<<result<<", 0"<<endl;
				outfile<<"LL"<<bijiao++<<":"<<endl;
			}
		}
	}
	map<int, int>::iterator iter;
	iter = tiaozhuan.find(label);
	if(iter != tiaozhuan.end())
		outfile<<"L"<<label<<":"<<endl;
	outfile<<"lend:"<<endl;
  }
  outfile<<"		invoke crt__getch"<<endl;
  outfile<<"		ret"<<endl<<"end start";
  outfile.close();
  return 0;
}
void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}
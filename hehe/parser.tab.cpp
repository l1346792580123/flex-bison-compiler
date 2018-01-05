/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

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

#line 184 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    I_CONSTANT = 259,
    F_CONSTANT = 260,
    STRING_LITERAL = 261,
    SIZEOF = 262,
    C_CONSTANT = 263,
    PTR_OP = 264,
    INC_OP = 265,
    DEC_OP = 266,
    LEFT_OP = 267,
    RIGHT_OP = 268,
    LE_OP = 269,
    GE_OP = 270,
    EQ_OP = 271,
    NE_OP = 272,
    AND_OP = 273,
    OR_OP = 274,
    MUL_ASSIGN = 275,
    DIV_ASSIGN = 276,
    MOD_ASSIGN = 277,
    ADD_ASSIGN = 278,
    SUB_ASSIGN = 279,
    LEFT_ASSIGN = 280,
    RIGHT_ASSIGN = 281,
    AND_ASSIGN = 282,
    XOR_ASSIGN = 283,
    OR_ASSIGN = 284,
    TYPEDEF_NAME = 285,
    ENUMERATION_CONSTANT = 286,
    READ = 287,
    WRITE = 288,
    TYPEDEF = 289,
    BOOL = 290,
    CHAR = 291,
    SHORT = 292,
    INT = 293,
    LONG = 294,
    SIGNED = 295,
    FLOAT = 296,
    DOUBLE = 297,
    VOID = 298,
    STRUCT = 299,
    UNION = 300,
    ENUM = 301,
    CASE = 302,
    IF = 303,
    ELSE = 304,
    SWITCH = 305,
    WHILE = 306,
    DO = 307,
    FOR = 308,
    CONTINUE = 309,
    BREAK = 310,
    RETURN = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 119 "parser.y" /* yacc.c:355  */

  char * str;
  class symbol  *sym;
  class parameterlist *parm;
  class expression *expr;
  class declarator *decl;
  int num;

#line 290 "parser.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 307 "parser.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1352

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  218
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  375

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    70,     2,     2,     2,    72,    65,     2,
      57,    58,    66,    67,    64,    68,    61,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    80,
      73,    79,    74,    77,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,    75,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    76,    63,    69,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   156,   156,   184,   185,   186,   190,   204,   205,   206,
     210,   214,   219,   220,   229,   230,   231,   232,   233,   234,
     235,   243,   251,   252,   256,   257,   261,   262,   269,   277,
     306,   307,   311,   312,   313,   314,   315,   316,   320,   321,
     332,   333,   337,   341,   352,   353,   372,   379,   380,   388,
     399,   400,   404,   408,   412,   419,   420,   424,   431,   432,
     443,   444,   455,   456,   467,   468,   475,   476,   483,   484,
     490,   491,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   538,   539,   547,   551,   552,   562,   563,
     564,   568,   569,   573,   645,   649,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   662,   663,   667,   668,   670,
     674,   675,   679,   680,   685,   686,   691,   692,   696,   697,
     701,   702,   703,   707,   708,   709,   710,   711,   715,   716,
     720,   721,   726,   733,   737,   754,   755,   756,   757,   758,
     759,   760,   764,   765,   770,   774,   775,   779,   780,   781,
     785,   786,   790,   796,   800,   801,   802,   806,   807,   808,
     809,   810,   811,   812,   813,   814,   815,   816,   820,   821,
     822,   823,   827,   828,   829,   830,   834,   838,   839,   843,
     844,   849,   850,   851,   852,   853,   854,   858,   859,   863,
     864,   868,   869,   873,   874,   878,   879,   883,   887,   890,
     894,   895,   896,   897,   898,   899,   902,   905,   906,   907,
     908,   912,   913,   917,   918,   922,   923,   930,   931
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "I_CONSTANT", "F_CONSTANT",
  "STRING_LITERAL", "SIZEOF", "C_CONSTANT", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPEDEF_NAME", "ENUMERATION_CONSTANT", "READ", "WRITE",
  "TYPEDEF", "BOOL", "CHAR", "SHORT", "INT", "LONG", "SIGNED", "FLOAT",
  "DOUBLE", "VOID", "STRUCT", "UNION", "ENUM", "CASE", "IF", "ELSE",
  "SWITCH", "WHILE", "DO", "FOR", "CONTINUE", "BREAK", "RETURN", "'('",
  "')'", "'['", "']'", "'.'", "'{'", "'}'", "','", "'&'", "'*'", "'+'",
  "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'",
  "':'", "'='", "';'", "$accept", "primary_expression", "constant",
  "enumeration_constant", "string", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "declarator", "direct_declarator", "pointer", "parameter_type_list",
  "parameter_list", "parameter_declaration", "identifier_list",
  "type_name", "abstract_declarator", "direct_abstract_declarator",
  "initializer", "initializer_list", "designation", "designator_list",
  "designator", "statement", "labeled_statement", "compound_statement",
  "block_item_list", "block_item", "expression_statement",
  "selection_statement", "iteration_statement", "m", "jump_statement",
  "translation_unit", "external_declaration", "function_definition",
  "declaration_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,    40,    41,    91,
      93,    46,   123,   125,    44,    38,    42,    43,    45,   126,
      33,    47,    37,    60,    62,    94,   124,    63,    58,    61,
      59
};
# endif

#define YYPACT_NINF -273

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-273)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1306,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,    20,  -273,    13,  1306,  1306,  -273,    26,
    -273,   333,  -273,  -273,   -12,    66,  -273,    44,    18,  -273,
     -16,  -273,  1198,    86,    38,  -273,  -273,    58,   461,  -273,
    -273,    66,  -273,    56,    -2,  -273,    74,  -273,    44,  -273,
     282,   794,  -273,    13,  -273,  1281,  1177,   862,    86,   461,
     461,   529,  -273,    43,   192,  1020,  -273,    39,  -273,  -273,
     115,   128,  -273,  -273,  -273,  1088,  -273,  1102,  1102,  -273,
     158,   163,  1020,   186,   212,   146,   184,   530,   614,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
     189,   162,  1020,  -273,    68,   185,   250,    40,   260,   209,
     174,   205,   265,    41,  -273,  -273,     7,  -273,  -273,  -273,
    -273,   350,  -273,  -273,  -273,  -273,   207,  -273,  -273,   630,
    -273,  -273,  -273,  -273,  -273,  -273,   109,   233,   236,  -273,
      53,  -273,   245,   246,  1255,  -273,  -273,  -273,  1020,  -273,
      61,  -273,   232,  -273,    42,  -273,  -273,  -273,  -273,  -273,
     462,   614,  -273,   614,  -273,  -273,  1020,  1020,   241,  1020,
    1020,  -273,  -273,  -273,   116,   143,    15,   253,   328,  -273,
    -273,   876,  1020,   331,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  1020,  -273,  1020,  1020,  1020,
    1020,  1020,  1020,  1020,  1020,  1020,  1020,  1020,  1020,  1020,
    1020,  1020,  1020,  1020,  1020,  1020,  1020,  -273,  -273,  -273,
     278,   462,   283,  1020,   338,  -273,  -273,   203,   794,    -3,
    -273,  1143,   893,  -273,    72,  -273,   117,  -273,  1306,  -273,
     339,  -273,  -273,  -273,  -273,    11,  -273,  1020,  -273,  -273,
     285,   288,   145,  -273,   147,   462,   150,   152,  -273,  -273,
    1223,   171,  -273,   907,  -273,  -273,   159,    82,  -273,  -273,
    -273,  -273,  -273,    68,    68,   185,   185,   250,   250,   250,
     250,    40,    40,   260,   209,   174,   205,   265,   -13,  -273,
    1020,   308,   418,   304,  -273,  -273,   698,  -273,  -273,  -273,
    -273,   307,   312,  -273,   306,   327,   117,   397,   975,  -273,
    -273,  -273,  -273,   337,   337,  -273,  1020,  -273,  -273,   462,
     462,   780,  -273,  -273,  -273,  1020,   160,   344,   546,   546,
    -273,  -273,  -273,   794,  -273,  -273,  -273,  -273,  -273,   345,
    -273,   342,   348,  -273,   360,  -273,   215,  -273,   462,  1020,
     989,  1006,  -273,  -273,  -273,  -273,   462,  -273,   712,  -273,
     161,   462,   169,   462,   173,  -273,  -273,   330,  -273,   462,
    -273,   462,  -273,  -273,  -273
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   106,    95,   103,    97,    98,    99,   102,   100,   101,
      96,   110,   111,     0,   214,     0,     0,    90,   104,     0,
     105,     0,   211,   213,   127,     0,   134,     0,   143,    86,
       0,    91,    94,   133,     0,    88,    89,   109,     0,     1,
     212,     0,    10,   131,     0,   128,     0,   142,     0,    87,
     206,     0,   217,     0,   216,     0,     0,     0,   132,     0,
     117,     0,   112,     0,     0,     0,   123,     0,   135,    92,
      94,     2,     6,     7,    11,     0,     8,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
      32,    33,    34,    35,    36,    37,   195,    12,     3,     4,
      26,    38,     0,    40,    44,    47,    50,    55,    58,    60,
      62,    64,    66,    68,    70,    83,     0,   193,   194,   181,
     182,   206,   191,   183,   184,   185,     0,   186,     2,     0,
     171,    93,   218,   215,   150,   140,   149,     0,   144,   145,
       0,   136,    33,     0,     0,   116,   107,   113,     0,   114,
       0,   118,   122,   125,     0,    38,    85,   130,   124,   129,
     206,     0,    30,     0,    27,    28,     0,     0,     0,     0,
       0,   207,   208,   209,     0,     0,   153,     0,     0,    20,
      21,     0,     0,     0,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    72,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   196,   190,   192,
       0,   206,     0,     0,     0,   170,   173,     0,     0,     0,
     177,     0,     0,   147,   155,   148,   156,   139,     0,   141,
       0,   137,   138,   108,   120,     0,   115,     0,   126,   187,
       0,     0,     0,    24,     0,   206,     0,     0,   210,     5,
       0,   155,   152,     0,    19,    14,     0,     0,    18,    71,
      41,    42,    43,    45,    46,    48,    49,    53,    54,    51,
      52,    56,    57,    59,    61,    63,    65,    67,     0,    84,
       0,     0,     0,     0,   180,   168,     0,   172,   176,   178,
     164,     0,     0,   158,    33,     0,   154,     0,     0,   146,
     151,   119,   121,    31,     0,    16,     0,    17,   188,   206,
     206,     0,    39,    15,    13,     0,     0,     0,     0,     0,
     179,   169,   175,     0,   165,   157,   159,   160,   166,     0,
     161,    33,     0,    25,   198,   199,     0,    69,   206,     0,
       0,     0,   174,   167,   162,   163,   206,    22,     0,   200,
       0,   206,     0,   206,     0,   197,    23,     0,   204,   206,
     202,   206,   201,   205,   203
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -273,  -273,  -273,  -273,  -273,  -273,  -108,   -50,  -273,   -91,
      98,    99,    90,    95,   201,   223,   202,   231,   257,  -273,
     -45,   -51,  -273,   -78,   -52,   -24,     1,  -273,   398,  -273,
     -25,  -273,  -273,   386,   -54,   -39,  -273,   229,  -273,   406,
     -55,   -10,   -30,    -9,   -53,  -273,   238,  -273,    77,   -96,
    -195,   -49,   156,  -272,  -273,   249,  -127,  -273,    12,  -273,
     358,  -159,  -273,  -273,  -273,  -273,  -273,   459,  -273,  -273
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    97,    98,    43,    99,   100,   252,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   195,   116,   157,    14,    53,    30,    31,    16,
      17,    18,    19,    61,    62,    63,   150,   151,    20,    44,
      45,    46,    33,    34,   301,   138,   139,   140,   177,   302,
     236,   226,   227,   228,   229,   230,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    21,    22,    23,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     130,    15,   131,   137,    58,    32,   143,   147,    52,   174,
     175,   196,   159,    60,    26,   155,    26,    35,    36,    47,
     156,   145,    15,    24,   333,   162,   117,   164,   165,    37,
     168,   132,   155,   249,    60,    60,    60,   156,    70,   306,
     235,    26,    42,    70,    54,    42,    26,    26,    48,   176,
      41,   216,   155,   152,   204,   205,   223,   136,   224,   254,
     214,    66,    67,    60,    49,   325,   306,   133,    27,    42,
      27,   216,   260,   266,   232,    26,   298,    28,   130,    28,
     262,    28,    25,   175,    28,   175,   333,   217,    38,   148,
     147,   256,   257,    29,   291,    27,   244,   117,   155,   159,
      27,    27,   158,   156,   267,   248,   270,   271,   272,    28,
      28,   239,    26,   206,   207,   253,   253,   240,   215,    60,
      59,   148,   176,   149,   176,   245,   233,   234,   318,   231,
     253,   232,    68,   329,   197,    65,    60,   288,    60,   198,
     199,   246,   324,    56,   269,    57,   216,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   289,   231,   261,   232,   350,
     351,   293,   322,   155,   307,    28,   308,   130,   156,   297,
     216,   305,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   344,   345,    51,   312,   258,   155,   178,   179,
     180,   259,   156,   315,    58,   317,   160,   216,   319,   316,
     320,   316,   326,   155,   216,   166,   216,   323,   348,   367,
     167,   359,   234,   316,   216,   216,   171,   369,   260,   365,
     232,   371,   136,   216,   368,   152,   370,   216,   250,   136,
     251,   194,   373,   169,   374,   130,   181,   332,   182,   211,
     183,   261,   200,   201,   339,   153,   154,   342,   220,   221,
     222,   136,   202,   203,   172,   343,   295,   296,   328,   170,
     130,   360,   362,   364,   210,   155,   208,   209,   357,   358,
     347,   212,   130,   213,   352,    71,    72,    73,    74,    75,
      76,   237,    77,    78,   277,   278,   279,   280,   273,   274,
     238,   275,   276,   281,   282,   241,   242,   130,   136,   332,
     247,   263,     1,    79,    80,    81,     2,     3,     4,   255,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    82,
      83,   264,    84,    39,   268,   290,    85,    86,    87,    88,
     292,   294,   310,   313,    50,    89,   314,    90,    91,    92,
      93,    94,    95,    71,    72,    73,    74,    75,    76,   327,
      77,    78,    96,     1,   330,   334,   336,     2,     3,     4,
     335,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       1,    79,    80,    81,     2,     3,     4,   337,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    82,    83,   321,
      84,   349,   354,   353,    85,    86,    87,    88,   355,   356,
     372,   283,    50,   218,   285,    90,    91,    92,    93,    94,
      95,   128,    72,    73,    74,    75,    76,     1,    77,    78,
      96,     2,     3,     4,   284,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   286,   144,    69,    64,     1,    79,
      80,    81,     2,     3,     4,   338,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    71,    72,    73,    74,    75,
      76,   287,    77,    78,   311,    88,   309,   346,   299,   219,
      40,     0,     0,    90,    91,    92,    93,    94,    95,     0,
       0,     1,     0,    79,    80,    81,     3,     4,    96,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,    82,
      83,     0,    84,     0,     0,     0,    85,    86,    87,    88,
       0,     0,     0,     0,    50,     0,     0,    90,    91,    92,
      93,    94,    95,   128,    72,    73,    74,    75,    76,     0,
      77,    78,    96,     0,     0,     0,     0,     0,     0,   128,
      72,    73,    74,    75,    76,     0,    77,    78,     0,     1,
       0,    79,    80,    81,     3,     4,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,   146,     0,     0,    90,    91,    92,    93,    94,
      95,     0,     0,    88,     0,     0,     0,     0,     0,     0,
     173,    90,    91,    92,    93,    94,    95,   128,    72,    73,
      74,    75,    76,     0,    77,    78,    96,     0,     0,     0,
       0,     0,     0,   128,    72,    73,    74,    75,    76,     0,
      77,    78,     0,     0,     1,    79,    80,    81,     0,     3,
       4,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,     0,     0,    88,     0,   223,
       0,   224,   129,   225,     0,    90,    91,    92,    93,    94,
      95,   128,    72,    73,    74,    75,    76,     0,    77,    78,
       0,     0,     0,     0,     0,   128,    72,    73,    74,    75,
      76,     0,    77,    78,     0,     0,     0,     0,     0,    79,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,   223,     0,   224,
     129,   331,     0,    90,    91,    92,    93,    94,    95,    88,
       0,   223,     0,   224,   129,   366,     0,    90,    91,    92,
      93,    94,    95,   128,    72,    73,    74,    75,    76,     0,
      77,    78,     0,     0,     0,     0,     0,   128,    72,    73,
      74,    75,    76,     0,    77,    78,     0,     0,     0,     0,
       0,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,   223,
       0,   224,   129,     0,     0,    90,    91,    92,    93,    94,
      95,    88,     0,     0,     0,     0,   129,     0,     0,    90,
      91,    92,    93,    94,    95,   128,    72,    73,    74,    75,
      76,     0,    77,    78,     0,     0,     0,     0,     0,   128,
      72,    73,    74,    75,    76,     0,    77,    78,     0,     0,
       0,     0,     0,    79,    80,    81,   128,    72,    73,    74,
      75,    76,     0,    77,    78,     0,     0,    79,    80,    81,
     128,    72,    73,    74,    75,    76,     0,    77,    78,    88,
       0,     0,   141,     0,    79,    80,    81,    90,   142,    92,
      93,    94,    95,    88,   265,     0,     0,     0,    79,    80,
      81,    90,    91,    92,    93,    94,    95,     0,     0,     0,
      88,     0,     0,   303,     0,     0,     0,     0,    90,   304,
      92,    93,    94,    95,    88,     0,     0,     0,     0,   321,
       0,     0,    90,    91,    92,    93,    94,    95,   128,    72,
      73,    74,    75,    76,     0,    77,    78,     0,     0,     0,
       0,     0,   128,    72,    73,    74,    75,    76,     0,    77,
      78,     0,     0,     0,     0,     0,    79,    80,    81,   128,
      72,    73,    74,    75,    76,     0,    77,    78,     0,     0,
      79,    80,    81,   128,    72,    73,    74,    75,    76,     0,
      77,    78,    88,     0,     0,   340,     0,    79,    80,    81,
      90,   341,    92,    93,    94,    95,    88,   361,     0,     0,
       0,    79,    80,    81,    90,    91,    92,    93,    94,    95,
       0,     0,     0,    88,   363,     0,     0,     0,     0,     0,
       0,    90,    91,    92,    93,    94,    95,    88,     0,     0,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,   128,    72,    73,    74,    75,    76,     0,    77,    78,
       0,     0,     0,     0,     0,   128,    72,    73,    74,    75,
      76,     0,    77,    78,     0,     0,     0,     0,     0,    79,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   161,    26,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,    95,   163,
       0,     0,     0,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    95,     1,     0,     0,     0,     2,     3,     4,
     134,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     231,   300,   232,     0,     0,     0,     0,     1,     0,    28,
       0,     2,     3,     4,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     1,     0,
       0,     0,     2,     3,     4,   135,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     2,     3,     4,
      50,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
     260,   300,   232,     0,     0,     1,     0,     0,     0,    28,
       3,     4,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     2,     3,     4,   243,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     0,     0,     0,
       2,     3,     4,    50,     5,     6,     7,     8,     9,    10,
      11,    12,    13
};

static const yytype_int16 yycheck[] =
{
      51,     0,    51,    56,    34,    15,    57,    61,    32,    87,
      88,   102,    67,    38,     3,    65,     3,    16,    17,    28,
      65,    60,    21,     3,   296,    75,    50,    77,    78,     3,
      82,    55,    82,   160,    59,    60,    61,    82,    48,   234,
     136,     3,     3,    53,    32,     3,     3,     3,    64,    88,
      62,    64,   102,    63,    14,    15,    59,    56,    61,   167,
      19,    63,    64,    88,    80,    78,   261,    55,    57,     3,
      57,    64,    57,   181,    59,     3,    79,    66,   129,    66,
     176,    66,    62,   161,    66,   163,   358,    80,    62,    78,
     144,   169,   170,    80,   221,    57,   148,   121,   148,   154,
      57,    57,    63,   148,   182,    63,   197,   198,   199,    66,
      66,    58,     3,    73,    74,   166,   167,    64,    77,   144,
      62,    78,   161,    80,   163,    64,   136,   136,   255,    57,
     181,    59,    58,   292,    66,    79,   161,   215,   163,    71,
      72,    80,    60,    57,   195,    59,    64,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   216,    57,   176,    59,   328,
     329,   223,   263,   223,    57,    66,    59,   228,   223,   228,
      64,   232,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   319,   320,    79,   247,    80,   247,     9,    10,
      11,    58,   247,    58,   234,    58,    78,    64,    58,    64,
      58,    64,   290,   263,    64,    57,    64,    58,    58,    58,
      57,   348,   231,    64,    64,    64,    80,    58,    57,   356,
      59,    58,   231,    64,   361,   245,   363,    64,   161,   238,
     163,    79,   369,    57,   371,   296,    57,   296,    59,    75,
      61,   260,    67,    68,   307,    63,    64,   308,    51,    52,
      53,   260,    12,    13,    80,   316,    63,    64,   292,    57,
     321,   349,   350,   351,    65,   325,    16,    17,    63,    64,
     325,    76,   333,    18,   333,     3,     4,     5,     6,     7,
       8,    58,    10,    11,   204,   205,   206,   207,   200,   201,
      64,   202,   203,   208,   209,    60,    60,   358,   307,   358,
      78,    58,    30,    31,    32,    33,    34,    35,    36,    78,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     3,    50,     0,     3,    57,    54,    55,    56,    57,
      57,     3,     3,    58,    62,    63,    58,    65,    66,    67,
      68,    69,    70,     3,     4,     5,     6,     7,     8,    51,
      10,    11,    80,    30,    60,    58,    60,    34,    35,    36,
      58,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      30,    31,    32,    33,    34,    35,    36,    60,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    62,
      50,    57,    60,    58,    54,    55,    56,    57,    60,    49,
      80,   210,    62,    63,   212,    65,    66,    67,    68,    69,
      70,     3,     4,     5,     6,     7,     8,    30,    10,    11,
      80,    34,    35,    36,   211,    38,    39,    40,    41,    42,
      43,    44,    45,    46,   213,    59,    48,    41,    30,    31,
      32,    33,    34,    35,    36,    58,    38,    39,    40,    41,
      42,    43,    44,    45,    46,     3,     4,     5,     6,     7,
       8,   214,    10,    11,   245,    57,   238,   321,   229,   121,
      21,    -1,    -1,    65,    66,    67,    68,    69,    70,    -1,
      -1,    30,    -1,    31,    32,    33,    35,    36,    80,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    47,
      48,    -1,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      68,    69,    70,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    80,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    30,
      -1,    31,    32,    33,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    65,    66,    67,    68,    69,
      70,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    65,    66,    67,    68,    69,    70,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    80,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    30,    31,    32,    33,    -1,    35,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    -1,    -1,    57,    -1,    59,
      -1,    61,    62,    63,    -1,    65,    66,    67,    68,    69,
      70,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    59,    -1,    61,
      62,    63,    -1,    65,    66,    67,    68,    69,    70,    57,
      -1,    59,    -1,    61,    62,    63,    -1,    65,    66,    67,
      68,    69,    70,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    59,
      -1,    61,    62,    -1,    -1,    65,    66,    67,    68,    69,
      70,    57,    -1,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    68,    69,    70,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,     3,     4,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    31,    32,    33,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    57,
      -1,    -1,    60,    -1,    31,    32,    33,    65,    66,    67,
      68,    69,    70,    57,    58,    -1,    -1,    -1,    31,    32,
      33,    65,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      57,    -1,    -1,    60,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    57,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    65,    66,    67,    68,    69,    70,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    -1,
      31,    32,    33,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    57,    -1,    -1,    60,    -1,    31,    32,    33,
      65,    66,    67,    68,    69,    70,    57,    58,    -1,    -1,
      -1,    31,    32,    33,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,
      70,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    30,    -1,    -1,    -1,    34,    35,    36,
       3,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    -1,    -1,    -1,    -1,    30,    -1,    66,
      -1,    34,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    34,    35,    36,    58,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,    36,
      62,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      57,    58,    59,    -1,    -1,    30,    -1,    -1,    -1,    66,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    35,    36,    63,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    35,    36,    62,    38,    39,    40,    41,    42,    43,
      44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    34,    35,    36,    38,    39,    40,    41,    42,
      43,    44,    45,    46,   106,   107,   110,   111,   112,   113,
     119,   147,   148,   149,     3,    62,     3,    57,    66,    80,
     108,   109,   122,   123,   124,   107,   107,     3,    62,     0,
     148,    62,     3,    84,   120,   121,   122,   124,    64,    80,
      62,    79,   106,   107,   139,   150,    57,    59,   123,    62,
     111,   114,   115,   116,   120,    79,    63,    64,    58,   109,
     122,     3,     4,     5,     6,     7,     8,    10,    11,    31,
      32,    33,    47,    48,    50,    54,    55,    56,    57,    63,
      65,    66,    67,    68,    69,    70,    80,    82,    83,    85,
      86,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   104,   106,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,     3,    62,
     102,   132,   106,   139,     3,    58,   107,   125,   126,   127,
     128,    60,    66,   102,   114,   116,    63,   115,    78,    80,
     117,   118,   122,    63,    64,    88,   101,   105,    63,   121,
      78,    57,    88,    57,    88,    88,    57,    57,   105,    57,
      57,    80,    80,    80,   104,   104,   116,   129,     9,    10,
      11,    57,    59,    61,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    79,   103,    90,    66,    71,    72,
      67,    68,    12,    13,    14,    15,    73,    74,    16,    17,
      65,    75,    76,    18,    19,    77,    64,    80,    63,   141,
      51,    52,    53,    59,    61,    63,   132,   133,   134,   135,
     136,    57,    59,   122,   124,   130,   131,    58,    64,    58,
      64,    60,    60,    63,   105,    64,    80,    78,    63,   137,
     129,   129,    87,   102,    87,    78,   104,   104,    80,    58,
      57,   124,   130,    58,     3,    58,    87,   104,     3,   102,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    93,
      93,    94,    94,    95,    96,    97,    98,    99,   104,   102,
      57,   137,    57,   105,     3,    63,    64,   132,    79,   136,
      58,   125,   130,    60,    66,   102,   131,    57,    59,   127,
       3,   118,   105,    58,    58,    58,    64,    58,   137,    58,
      58,    62,    90,    58,    60,    78,   104,    51,   106,   142,
      60,    63,   132,   134,    58,    58,    60,    60,    58,   125,
      60,    66,   102,   102,   137,   137,   133,   101,    58,    57,
     142,   142,   132,    58,    60,    60,    49,    63,    64,   137,
     104,    58,   104,    58,   104,   137,    63,    58,   137,    58,
     137,    58,    80,   137,   137
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    82,    82,    83,    83,    83,    83,
      84,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    87,    87,    88,    88,    88,    88,
      88,    88,    89,    89,    89,    89,    89,    89,    90,    90,
      91,    91,    91,    91,    92,    92,    92,    93,    93,    93,
      94,    94,    94,    94,    94,    95,    95,    95,    96,    96,
      97,    97,    98,    98,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   104,   104,   105,   106,   106,   107,   107,
     107,   108,   108,   109,   109,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   117,   117,
     118,   118,   118,   119,   119,   119,   119,   119,   120,   120,
     121,   121,   122,   122,   123,   123,   123,   123,   123,   123,
     123,   123,   124,   124,   125,   126,   126,   127,   127,   127,
     128,   128,   129,   129,   130,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   132,   132,
     132,   132,   133,   133,   133,   133,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   142,   143,   143,   143,
     144,   144,   144,   144,   144,   144,   145,   146,   146,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     4,     4,     4,     3,     3,
       2,     2,     6,     7,     1,     3,     1,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     2,     3,     2,     2,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     5,     2,
       1,     1,     1,     2,     2,     3,     2,     1,     1,     3,
       2,     3,     1,     4,     5,     5,     6,     2,     1,     3,
       3,     1,     2,     1,     1,     3,     3,     4,     4,     4,
       3,     4,     2,     1,     1,     1,     3,     2,     2,     1,
       1,     3,     2,     1,     2,     1,     1,     3,     2,     3,
       3,     3,     4,     4,     2,     3,     3,     4,     3,     4,
       2,     1,     2,     1,     4,     3,     2,     1,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     4,     2,
       3,     1,     2,     1,     1,     1,     2,     7,     5,     5,
       6,     8,     7,     8,     7,     8,     0,     2,     2,     2,
       3,     1,     2,     1,     1,     4,     3,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 156 "parser.y" /* yacc.c:1646  */
    {string a = (yyvsp[0].str); map<string, symbol*>::iterator iter = symboltable.front().find(a); (yyval.expr) = new expression();
				  list<map<string, symbol*>>::iterator v; int bb = 0;(yyval.expr)->opera = "ID";
				  for(v = symboltable.begin(); v != symboltable.end(); ++v)
				  {
					map<string, symbol*>::iterator iter = (*v).find(a);
					if(iter == (*v).end())
					{
						continue;
					}
					else
					{
					  (yyval.expr)->sym = iter->second;
					  for(int i = 0; i < iter->second->list.size(); ++i)
					  {
						(yyval.expr)->list.push_back(iter->second->list[i]);
					  }
					  (yyval.expr)->type = iter->second->ty;
					  (yyval.expr)->canbeleft = 1;
					  bb = 1;
					  break;
					 }
				  }
				  if (!bb)
				  {
					(yyval.expr)->opera = "未定义的变量";
					iferror = 1;
				  }
				 }
#line 1901 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 184 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1907 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 185 "parser.y" /* yacc.c:1646  */
    {printf("字符串  ");}
#line 1913 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-1].expr);}
#line 1919 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 190 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 0; (yyval.expr)->type = 2; (yyval.expr)->size = -1; (yyval.expr)->val = malloc(sizeof(int));
					char te[3];
					if(strlen((yyvsp[0].str)) > 2)
					{
						strncpy(te, (yyvsp[0].str), 2);te[2] = '\0';
						if(strcmp(te, "0x") ==0) 
							*(int*)(yyval.expr)->val = strtol((yyvsp[0].str), NULL, 16);
						else
							*(int*)(yyval.expr)->val = strtol((yyvsp[0].str), NULL, 10);
					}
					else
						*(int*)(yyval.expr)->val = strtol((yyvsp[0].str), NULL, 10);
					(yyval.expr)->opera = "VAL";
					}
#line 1938 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 0; (yyval.expr)->type = 3; (yyval.expr)->size = -1; (yyval.expr)->val = malloc(sizeof(double)); *(double*)(yyval.expr)->val = atof((yyvsp[0].str)); (yyval.expr)->opera = "VAL";}
#line 1944 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 205 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 0; (yyval.expr)->type = 1; (yyval.expr)->size = -1; (yyval.expr)->val = malloc(sizeof(int));*(int*)(yyval.expr)->val = (yyvsp[0].str)[1];(yyval.expr)->opera = "VAL";}
#line 1950 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 206 "parser.y" /* yacc.c:1646  */
    {printf("enum常量  ");}
#line 1956 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 214 "parser.y" /* yacc.c:1646  */
    {}
#line 1962 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1968 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "ARRAY"; (yyval.expr)->left = (yyvsp[-3].expr); (yyval.expr)->right = (yyvsp[-1].expr);(yyval.expr)->type = (yyvsp[-3].expr)->type;
											  (yyval.expr)->count = (yyvsp[-3].expr)->count + (yyvsp[-1].expr)->count + 1;
											  for(int i= 1; i< (yyvsp[-3].expr)->list.size(); ++i)
											  {
												(yyval.expr)->list.push_back((yyvsp[-3].expr)->list[i]);
											  }
											  if((yyval.expr)->list.size() == 0 || (yyval.expr)->list[0] == 0)
												(yyval.expr)->canbeleft = 1;
											 }
#line 1982 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "FUNC_CALL"; (yyval.expr)->right = (yyvsp[-2].expr);}
#line 1988 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "FUNC_CALL"; (yyval.expr)->right = (yyvsp[-3].expr); (yyval.expr)->comstmt = (yyvsp[-1].expr);}
#line 1994 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 0; (yyval.expr)->opera = "READ"; (yyval.expr)->comstmt = (yyvsp[-1].expr); (yyval.expr)->count = (yyvsp[-1].expr)->count + 1;}
#line 2000 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 232 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 0; (yyval.expr)->opera = "WRITE"; (yyval.expr)->comstmt = (yyvsp[-1].expr); (yyval.expr)->count = (yyvsp[-1].expr)->count + 1;}
#line 2006 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 235 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "PINC"; (yyval.expr)->right = (yyvsp[-1].expr);(yyval.expr)->op = 1;(yyval.expr)->count = (yyvsp[-1].expr)->count + 1;
									if(!(yyvsp[-1].expr)->canbeleft)
									{
										(yyval.expr)->opera = "POST_INC_OP  运算符必须是左值";
										iferror = 1;
									}
									(yyval.expr)->type = (yyvsp[-1].expr)->type;
								   }
#line 2019 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "PDEC"; (yyval.expr)->right = (yyvsp[-1].expr); (yyval.expr)->op = 1;(yyval.expr)->count = (yyvsp[-1].expr)->count + 1;
								   if(!(yyvsp[-1].expr)->canbeleft)
								   {
										(yyval.expr)->opera = "POST_DEC_OP  运算符必须是左值";
										iferror = 1;
								   }
								   (yyval.expr)->type = (yyvsp[-1].expr)->type;
								  }
#line 2032 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 251 "parser.y" /* yacc.c:1646  */
    {printf("强制类型转换   ");}
#line 2038 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 256 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2044 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 257 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-2].expr); (yyval.expr)->last->next = (yyvsp[0].expr); (yyval.expr)->last = (yyvsp[0].expr);}
#line 2050 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 261 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2056 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 262 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "FINC"; (yyval.expr)->right = (yyvsp[0].expr);(yyval.expr)->count = (yyvsp[0].expr)->count + 1;
								if(!(yyvsp[0].expr)->canbeleft)
								{
									(yyval.expr)->opera = "FRONT_INC_OP  运算符必须是左值";iferror = 1;
								}
								(yyval.expr)->type = (yyvsp[0].expr)->type;(yyval.expr)->sym = (yyvsp[0].expr)->sym;(yyval.expr)->canbeleft = 1;(yyval.expr)->op = 2;
							  }
#line 2068 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 269 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "FDEC"; (yyval.expr)->right = (yyvsp[0].expr);(yyval.expr)->count = (yyvsp[0].expr)->count + 1;
								if(!(yyvsp[0].expr)->canbeleft)
								{
									(yyval.expr)->opera = "FRONT_DEC_OP  运算符必须是左值";iferror = 1;
								}
								(yyval.expr)->type = (yyvsp[0].expr)->type;(yyval.expr)->sym = (yyvsp[0].expr)->sym;
								(yyval.expr)->canbeleft = 1;(yyval.expr)->op = 2;
							   }
#line 2081 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 277 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = (yyvsp[-1].str); (yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->type = (yyvsp[0].expr)->type;
									  (yyval.expr)->count = (yyvsp[0].expr)->count + 1;
									  if(strcmp((yyvsp[-1].str), "ADDR") == 0)
									  {
										(yyval.expr)->list.push_back(0);
										for(int i = 0; i < (yyvsp[0].expr)->list.size(); ++i)
										{
											(yyval.expr)->list.push_back((yyvsp[0].expr)->list[i]);
										}
									  }
									  if(strcmp((yyvsp[-1].str), "STAR") == 0)
									  {
										if((yyvsp[0].expr)->list.size() != 0)
										{
											for(int i = 1; i < (yyvsp[0].expr)->list.size(); ++i)
											{
												(yyval.expr)->list.push_back((yyvsp[0].expr)->list[i]);
											}
											if((yyval.expr)->list.size() == 0 || (yyvsp[0].expr)->list[0] == 0)
												(yyval.expr)->canbeleft = 1;
										}
										else
											iferror = 1;
									  }
										if(strcmp((yyvsp[-1].str), "FEI") == 0)
										{
											(yyval.expr)->type = 2;
										}
									 }
#line 2115 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 311 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "ADDR";}
#line 2121 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 312 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "STAR";}
#line 2127 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 313 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "POSI";}
#line 2133 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 314 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "FU";}
#line 2139 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 315 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "QUFAN";}
#line 2145 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 316 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "FEI";}
#line 2151 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 320 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2157 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 321 "parser.y" /* yacc.c:1646  */
    {
											(yyval.expr) = new expression(); (yyval.expr)->opera = "TYPE_CHANGE"; (yyval.expr)->size = 1; (yyval.expr)->sym = (yyvsp[-2].sym);
											(yyval.expr)->right = (yyvsp[0].expr);(yyval.expr)->type = (yyvsp[-2].sym)->ty;
											for(int i = 0; i < (yyvsp[-2].sym)->list.size(); ++i)
											{
												(yyval.expr)->list.push_back((yyvsp[-2].sym)->list[i]);
											}
										}
#line 2170 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 332 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2176 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 333 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr);(yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->opera = "*";
														(yyval.expr)->type = (yyvsp[-2].expr)->type > (yyvsp[0].expr)->type ? (yyvsp[-2].expr)->type : (yyvsp[0].expr)->type;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													 }
#line 2185 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 337 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr);(yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->opera = "/";
													  (yyval.expr)->type = (yyvsp[-2].expr)->type > (yyvsp[0].expr)->type ? (yyvsp[-2].expr)->type : (yyvsp[0].expr)->type;(yyval.expr)->op = 1;
													  (yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													 }
#line 2194 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 341 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr);(yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->opera = "%";
														if((yyvsp[-2].expr)->type == 3 || (yyvsp[0].expr)->type == 3)
														{
															(yyval.expr)->opera = "MOD_OP  运算符必须为整数";iferror = 1;
														}
														(yyval.expr)->type = 2;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													 }
#line 2207 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2213 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr);(yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->opera = "+";
															if((yyvsp[-2].expr)->list.size() == 0 && (yyvsp[0].expr)->list.size() == 0)
															{
																(yyval.expr)->type = (yyvsp[-2].expr)->type > (yyvsp[0].expr)->type ? (yyvsp[-2].expr)->type : (yyvsp[0].expr)->type;
															}
															else
															{
																(yyval.expr)->type = 2;
																expression *temp;
																if((yyvsp[-2].expr)->list.size() != 0)
																	temp = (yyvsp[-2].expr);
																else
																	temp = (yyvsp[0].expr);
																for(int i = 0; i < temp->list.size(); ++i)
																	(yyval.expr)->list.push_back(temp->list[i]);
															}
															(yyvsp[0].expr)->type;(yyval.expr)->op = 1;
															(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
														 }
#line 2237 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 372 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr);(yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->opera = "-";
															(yyval.expr)->type = (yyvsp[-2].expr)->type > (yyvsp[0].expr)->type ? (yyvsp[-2].expr)->type : (yyvsp[0].expr)->type;(yyval.expr)->op = 1;
															(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
														 }
#line 2246 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 379 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2252 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 380 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "<<"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														(yyval.expr)->type = 2;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													  if((yyvsp[-2].expr)->type == 3 || (yyvsp[0].expr)->type == 3)
													  {
															(yyval.expr)->opera = "LEFT_OP  运算符必须为整数";iferror = 1;
													  }
													 }
#line 2265 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 388 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = ">>"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														(yyval.expr)->type = 2;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													  if((yyvsp[-2].expr)->type == 3 || (yyvsp[0].expr)->type == 3)
														{
															(yyval.expr)->opera = "RIGHT_OP  运算符必须为整数";iferror = 1;
														}
													 }
#line 2278 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 399 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2284 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 400 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "<"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														(yyval.expr)->type = 2;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
												   }
#line 2293 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 404 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = ">"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														(yyval.expr)->type = 2;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
												   }
#line 2302 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 408 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "<="; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														 (yyval.expr)->type = 2;(yyval.expr)->op = 1;
														 (yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													}
#line 2311 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 412 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = ">="; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														 (yyval.expr)->type = 2;(yyval.expr)->op = 1;
														 (yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													}
#line 2320 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 419 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2326 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 420 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "=="; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
															(yyval.expr)->type = 2;(yyval.expr)->op = 1;
															(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													   }
#line 2335 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 424 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "+="; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
															(yyval.expr)->type = 2;(yyval.expr)->op = 1;
															(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
													   }
#line 2344 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 431 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2350 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 432 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "&"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
													(yyval.expr)->type = 2;(yyval.expr)->op = 1;
													(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
											   if((yyvsp[-2].expr)->type == 3 || (yyvsp[0].expr)->type == 3)
												{
													(yyval.expr)->opera = "BIT_AND  运算符必须为整数";iferror = 1;
												}
											  }
#line 2363 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 443 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2369 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 444 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "^"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
														(yyval.expr)->type = 2;(yyval.expr)->op = 1;
														(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
												   	if((yyvsp[-2].expr)->type == 3 || (yyvsp[0].expr)->type == 3)
													{
														(yyval.expr)->opera = "BIT_XOR  运算符必须为整数";iferror = 1;
													}
												  }
#line 2382 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 455 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2388 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 456 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "|"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
															   	(yyval.expr)->type = 2;(yyval.expr)->op = 1;
																(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
															if((yyvsp[-2].expr)->type == 3 || (yyvsp[0].expr)->type == 3)
															{
																(yyval.expr)->opera = "BIT_OR  运算符必须为整数";iferror = 1;
															}
														   }
#line 2401 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 467 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2407 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 468 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "&&"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
																(yyval.expr)->type = 2;(yyval.expr)->op = 1;
																(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
															 }
#line 2416 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 475 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2422 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 476 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "||"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
															(yyval.expr)->type = 2;(yyval.expr)->op = 1;
															(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
														 }
#line 2431 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 483 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2437 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 484 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 3; (yyval.expr)->opera = "QUES"; 
																	   (yyval.expr)->left = (yyvsp[-4].expr); (yyval.expr)->right = (yyvsp[-2].expr); (yyval.expr)->rr = (yyvsp[0].expr);
																	  }
#line 2445 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 490 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2451 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 491 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = (yyvsp[-1].str); (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
																	(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
																	if(strcmp((yyvsp[-1].str),"=") == 0)
																	{
																		if((yyvsp[-2].expr)->list.size() != 0 || (yyvsp[0].expr)->list.size() != 0)
																		{
																			if((yyvsp[-2].expr)->list.size() != (yyvsp[0].expr)->list.size())
																			{
																				(yyval.expr)->opera = "ASSIGN_OP  类型不匹配";iferror = 1;
																			}
																			else
																			{
																				//除了第一个指针可以指向数组 剩下的都要相等
																				for(int i = 1; i < (yyvsp[-2].expr)->list.size(); ++i)
																				{
																					if((yyvsp[-2].expr)->list[i] != (yyvsp[0].expr)->list[i])
																					{
																						(yyval.expr)->opera = "ASSIGN_OP  类型不匹配";iferror = 1;
																						break;
																					}
																				}
																			}
																		}
																		if(!(yyvsp[-2].expr)->canbeleft)
																		{
																			(yyval.expr)->opera = "ASSIGN_OP  运算符必须为左值";iferror = 1;
																		}
																	}
																	(yyval.expr)->type = (yyvsp[-2].expr)->type;(yyval.expr)->op = 2;
																   }
#line 2486 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 524 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "=";}
#line 2492 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 525 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "*=";}
#line 2498 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 526 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "/=";}
#line 2504 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 527 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "%=";}
#line 2510 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 528 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "+=";}
#line 2516 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 529 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "-=";}
#line 2522 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 530 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "<<=";}
#line 2528 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 531 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = ">>=";}
#line 2534 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 532 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "&=";}
#line 2540 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 533 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "^=";}
#line 2546 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 534 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "|=";}
#line 2552 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 538 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2558 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 539 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "COMMA"; (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
											(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count;
											(yyval.expr)->type = (yyvsp[0].expr)->type;
											(yyval.expr)->canbeleft = (yyvsp[0].expr)->canbeleft;
										   }
#line 2568 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 551 "parser.y" /* yacc.c:1646  */
    {printf("声明   ");}
#line 2574 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 552 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression();
														 (yyval.expr)->opera = "DECL";
														 (yyval.expr)->type = (yyvsp[-2].num);
														 (yyval.expr)->size = -1;
														 (yyval.expr)->comstmt = (yyvsp[-1].expr);
														 (yyval.expr)->count = (yyvsp[-1].expr)->count;
														}
#line 2586 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 562 "parser.y" /* yacc.c:1646  */
    {printf("typedef操作   ");}
#line 2592 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 564 "parser.y" /* yacc.c:1646  */
    {(yyval.num)=(yyvsp[0].num);}
#line 2598 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 568 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "INITLIST"; (yyval.expr)->size = -1; (yyval.expr)->comstmt = (yyvsp[0].expr); (yyval.expr)->count = (yyvsp[0].expr)->count;}
#line 2604 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 569 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-2].expr); (yyval.expr)->comstmt->last->next = (yyvsp[0].expr); (yyval.expr)->comstmt->last = (yyvsp[0].expr); (yyval.expr)->count += (yyvsp[0].expr)->count;}
#line 2610 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 573 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new expression();(yyval.expr)->size = 2; (yyval.expr)->sym = (yyvsp[-2].sym); (yyval.expr)->opera = "INITDEF"; (yyval.expr)->right = (yyvsp[0].expr); (yyval.expr)->type = curtype;
									  (yyval.expr)->count = (yyvsp[0].expr)->count;
									  if((yyvsp[-2].sym)->list.size() != 0)
									  {
										if((yyvsp[-2].sym)->list[0] == 0)
										{
											if((yyvsp[-2].sym)->ty != (yyvsp[0].expr)->type)
											{
												(yyval.expr)->opera = "无法类型转换";
												iferror = 1;
											}
											else
											{
												if((yyvsp[-2].sym)->list.size() != (yyvsp[0].expr)->list.size())
												{
													(yyval.expr)->opera = "类型不匹配";
													iferror = 1;
												}
											}
										}
										else if((yyvsp[0].expr)->comstmt != NULL)
										{
											(yyval.expr)->opera = "ARRAYDEF";
											if((yyvsp[-2].sym)->list[0] == -2)
											{
												(yyvsp[-2].sym)->list[0] = (yyvsp[0].expr)->comstmt->arraysize;
											}
											int *size = new int[(yyvsp[-2].sym)->list.size() + 1];
											int *q = new int[(yyvsp[-2].sym)->list.size()];
											size[(yyvsp[-2].sym)->list.size()] = 1;
											int check = 0;
											for(int i = (yyvsp[-2].sym)->list.size()-1; i >= 0; --i )
											{
												if((yyvsp[-2].sym)->list[i] == -2)
												{
													check = 1;iferror = 1;
													(yyval.expr)->opera = "只能第一项为空";
													break;
												}
												size[i] = size[i+1] * (yyvsp[-2].sym)->list[i];
												q[i] = (yyvsp[-2].sym)->list[i];
											}
											if(!check)
											{
												expression *e = (yyvsp[0].expr)->comstmt;
													
												if( e != NULL && e->arraysize > size[0])
													(yyval.expr)->opera = "初始项太多";
												else
												{
													while(e != NULL)
													{
														if(e->compare(q + 1,(yyvsp[-2].sym)->list.size() - 1, size + 1))
														{
															(yyval.expr)->opera = "初始项太多";
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
										if((yyvsp[0].expr)->comstmt != NULL || (yyvsp[-2].sym)->type != (yyvsp[0].expr)->type)
										{
											(yyval.expr)->opera = "类型不匹配";
											iferror = 1;
										}
									  }
									}
#line 2687 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 645 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 0; (yyval.expr)->sym = (yyvsp[0].sym); (yyval.expr)->opera = "INITDECL"; (yyval.expr)->count = 1; (yyval.expr)->type = (yyvsp[0].sym)->type;}
#line 2693 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 653 "parser.y" /* yacc.c:1646  */
    {(yyval.num)=0; curtype = (yyval.num);}
#line 2699 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 654 "parser.y" /* yacc.c:1646  */
    {(yyval.num)=1; curtype = (yyval.num);}
#line 2705 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 655 "parser.y" /* yacc.c:1646  */
    {(yyval.num)=2; curtype = (yyval.num);}
#line 2711 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 657 "parser.y" /* yacc.c:1646  */
    {(yyval.num)=3; curtype = (yyval.num);}
#line 2717 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 658 "parser.y" /* yacc.c:1646  */
    {(yyval.num) = 3; curtype = (yyval.num);}
#line 2723 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 661 "parser.y" /* yacc.c:1646  */
    {(yyval.num) = curtype;}
#line 2729 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 667 "parser.y" /* yacc.c:1646  */
    {}
#line 2735 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 668 "parser.y" /* yacc.c:1646  */
    {
																  }
#line 2742 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 674 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "STRUCT";}
#line 2748 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 675 "parser.y" /* yacc.c:1646  */
    {(yyval.str) = "UNION";}
#line 2754 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 679 "parser.y" /* yacc.c:1646  */
    {(yyval.parm) = (yyvsp[0].parm);}
#line 2760 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 680 "parser.y" /* yacc.c:1646  */
    {
												  }
#line 2767 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 686 "parser.y" /* yacc.c:1646  */
    {
															}
#line 2774 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 692 "parser.y" /* yacc.c:1646  */
    {(yyval.num) = (yyvsp[0].num);}
#line 2780 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 696 "parser.y" /* yacc.c:1646  */
    {}
#line 2786 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 697 "parser.y" /* yacc.c:1646  */
    {}
#line 2792 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 703 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = (yyvsp[0].sym);}
#line 2798 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 726 "parser.y" /* yacc.c:1646  */
    {
									for(int i=0; i< (yyvsp[-1].num); ++i)
									{
										(yyvsp[0].sym)->list.push_back(0);
									}
									(yyval.sym) = (yyvsp[0].sym);
								}
#line 2810 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 733 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = (yyvsp[0].sym);}
#line 2816 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 737 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = new symbol((yyvsp[0].str)); (yyval.sym)->type = curtype; string a = (char*)(yyvsp[0].str);
					if (strcmp((yyvsp[0].str), "main") != 0)
					{
						sv.push_back((yyval.sym));
					}
					map<string, symbol*>::iterator iter;
					iter = (symboltable.front()).find(a);
					if(iter == (symboltable.front()).end())
					{
						(symboltable.front()).insert(pair<string, symbol*>(a,(yyval.sym)));
						(yyval.sym)->ty = curtype;
					}
					else
					{
						yyerror("变量重定义");
					}
				   }
#line 2838 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 754 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = (yyvsp[-1].sym);}
#line 2844 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 755 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].sym)->list.push_back(-2); (yyval.sym) = (yyvsp[-2].sym);}
#line 2850 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 757 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-3].sym)->list.push_back(*(int*)(yyvsp[-1].expr)->val); (yyval.sym) = (yyvsp[-3].sym);}
#line 2856 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 758 "parser.y" /* yacc.c:1646  */
    {}
#line 2862 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 764 "parser.y" /* yacc.c:1646  */
    { (yyval.num) = (yyvsp[0].num) + 1;}
#line 2868 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 765 "parser.y" /* yacc.c:1646  */
    {(yyval.num) = 1;}
#line 2874 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 770 "parser.y" /* yacc.c:1646  */
    {(yyval.parm) = (yyvsp[0].parm);}
#line 2880 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 774 "parser.y" /* yacc.c:1646  */
    {(yyval.parm) = new parameterlist(); (yyval.parm)->param.push_back((yyvsp[0].sym));}
#line 2886 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 775 "parser.y" /* yacc.c:1646  */
    {(yyvsp[-2].parm)->param.push_back((yyvsp[0].sym)); (yyval.parm) = (yyvsp[-2].parm);}
#line 2892 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 779 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = (yyvsp[0].sym); (yyval.sym)->type = (yyvsp[-1].num);}
#line 2898 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 781 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = new symbol(); (yyval.sym)->type = (yyvsp[0].num);}
#line 2904 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 790 "parser.y" /* yacc.c:1646  */
    {(yyval.sym) = new symbol();(yyval.sym)->ty = (yyvsp[-1].num);
													for(int i = 0; i < (yyvsp[0].num); ++i)
													{
														(yyval.sym)->list.push_back(0);
													}
												   }
#line 2915 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 820 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->comstmt = (yyvsp[-1].expr); (yyval.expr)->opera = "LIST"; (yyval.expr)->count = (yyvsp[-1].expr)->count;}
#line 2921 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 822 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "LIST";}
#line 2927 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 823 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr); ++(yyval.expr)->count;}
#line 2933 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 828 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2939 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 830 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-2].expr); (yyval.expr)->last->next = (yyvsp[0].expr); (yyval.expr)->last = (yyvsp[0].expr); ++(yyval.expr)->arraysize; (yyval.expr)->count += (yyvsp[0].expr)->count;}
#line 2945 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 182:
#line 850 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2951 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 851 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2957 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 852 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2963 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 853 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2969 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 854 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2975 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 864 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "COM"; (yyval.expr)->size = -1; (yyval.expr)->comstmt = (yyvsp[-1].expr); (yyval.expr)->count = (yyvsp[-1].expr)->count;}
#line 2981 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 868 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr); (yyval.expr)->count = (yyvsp[0].expr)->count;}
#line 2987 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 869 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-1].expr); (yyval.expr)->last->next = (yyvsp[0].expr); (yyval.expr)->last = (yyvsp[0].expr); (yyval.expr)->count += (yyvsp[0].expr)->count;}
#line 2993 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 873 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 2999 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 874 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 3005 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 878 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "NULL"; (yyval.expr)->size = -1; (yyval.expr)->count = 1;}
#line 3011 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 879 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-1].expr);}
#line 3017 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 883 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 3; (yyval.expr)->opera = "IFELSE"; (yyval.expr)->left = (yyvsp[-4].expr); (yyval.expr)->right = (yyvsp[-2].expr);
													   (yyval.expr)->rr = (yyvsp[0].expr);
													   (yyval.expr)->count = (yyvsp[-4].expr)->count + (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 2;
													  }
#line 3026 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 887 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 2; (yyval.expr)->opera = "IF"; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr);
										(yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 1;
									   }
#line 3034 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 894 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "WHILE"; (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-2].expr); (yyval.expr)->right = (yyvsp[0].expr); symboltable.pop_front(); (yyval.expr)->count = (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 2;}
#line 3040 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 895 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "DOWHILE"; (yyval.expr)->size = 2; (yyval.expr)->left = (yyvsp[-5].expr); (yyval.expr)->right = (yyvsp[-2].expr); symboltable.pop_front();}
#line 3046 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 896 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 3; (yyval.expr)->opera = "FOR"; (yyval.expr)->left = (yyvsp[-3].expr); (yyval.expr)->right = (yyvsp[-2].expr); (yyval.expr)->rrr = (yyvsp[0].expr); symboltable.pop_front(); (yyval.expr)->count = (yyvsp[-3].expr)->count + (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 2;}
#line 3052 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 897 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 4; (yyval.expr)->opera = "FOR"; (yyval.expr)->left = (yyvsp[-4].expr); (yyval.expr)->right = (yyvsp[-3].expr); (yyval.expr)->rr = (yyvsp[-2].expr); (yyval.expr)->rrr = (yyvsp[0].expr); symboltable.pop_front();(yyval.expr)->count = (yyvsp[-4].expr)->count + (yyvsp[-3].expr)->count + (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 2;}
#line 3058 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 898 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "FOR"; (yyval.expr)->size = 3; (yyval.expr)->left = (yyvsp[-3].expr); (yyval.expr)->right = (yyvsp[-2].expr); (yyval.expr)->rrr = (yyvsp[0].expr); symboltable.pop_front(); (yyval.expr)->count = (yyvsp[-3].expr)->count + (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 2;}
#line 3064 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 899 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->opera = "FOR"; (yyval.expr)->size = 4; (yyval.expr)->left = (yyvsp[-4].expr); (yyval.expr)->right = (yyvsp[-3].expr); (yyval.expr)->rr = (yyvsp[-2].expr); (yyval.expr)->rrr = (yyvsp[0].expr); symboltable.pop_front(); (yyval.expr)->count = (yyvsp[-4].expr)->count + (yyvsp[-3].expr)->count + (yyvsp[-2].expr)->count + (yyvsp[0].expr)->count + 2;}
#line 3070 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 902 "parser.y" /* yacc.c:1646  */
    {map<string,symbol*> *p = new map<string,symbol*>; symboltable.push_front(*p);}
#line 3076 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 907 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = -1; (yyval.expr)->opera = "RETURN";}
#line 3082 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 908 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new expression(); (yyval.expr)->size = 1; (yyval.expr)->opera = "RETURN"; (yyval.expr)->right = (yyvsp[-1].expr);}
#line 3088 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 912 "parser.y" /* yacc.c:1646  */
    {start = (yyvsp[0].expr); (yyval.expr) = (yyvsp[0].expr);}
#line 3094 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 913 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[-1].expr);(yyval.expr)->last->next = (yyvsp[0].expr); (yyval.expr)->last = (yyvsp[0].expr);}
#line 3100 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 917 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 3106 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 918 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 3112 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 922 "parser.y" /* yacc.c:1646  */
    {printf("带参数函数声明   ");}
#line 3118 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 923 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new expression(); (yyval.expr)->sym = (yyvsp[-1].sym);  (yyvsp[-1].sym)->type = (yyvsp[-2].num);
															  (yyval.expr)->opera = "FUNC";
															  (yyval.expr)->comstmt = (yyvsp[0].expr);
															}
#line 3127 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 3131 "parser.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 934 "parser.y" /* yacc.c:1906  */

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

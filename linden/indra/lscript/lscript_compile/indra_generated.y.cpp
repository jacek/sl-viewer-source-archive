
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "indra.y"

// We maintain a pre-generated parser source file to simplify user builds.
// Before committing changes to this file, manually run
//
//   bison -d -o indra_generated.y.cpp indra.y
//
// to update the pre-generated parser.  Note that some versions of
// bison use a different default file name for the parser token
// header.  Make sure the file is called 'indra_generated.y.hpp'.
// Then commit all files simultaneously.
	#include "linden_common.h"
	#include "lscript_tree.h"

    #ifdef __cplusplus
    extern "C" {
    #endif

	int yylex(void);
	int yyparse( void );
	int yyerror(const char *fmt, ...);

    #if LL_LINUX
    // broken yacc codegen...  --ryan.
    #define getenv getenv_workaround
    #endif

    #ifdef LL_WINDOWS
	#pragma warning (disable : 4702) // warning C4702: unreachable code
	#pragma warning( disable : 4065 )	// warning: switch statement contains 'default' but no 'case' labels
	#endif

    #ifdef __cplusplus
    }
    #endif


/* Line 189 of yacc.c  */
#line 110 "indra_generated.y.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     FLOAT_TYPE = 259,
     STRING = 260,
     LLKEY = 261,
     VECTOR = 262,
     QUATERNION = 263,
     LIST = 264,
     STATE = 265,
     EVENT = 266,
     JUMP = 267,
     RETURN = 268,
     STATE_ENTRY = 269,
     STATE_EXIT = 270,
     TOUCH_START = 271,
     TOUCH = 272,
     TOUCH_END = 273,
     COLLISION_START = 274,
     COLLISION = 275,
     COLLISION_END = 276,
     LAND_COLLISION_START = 277,
     LAND_COLLISION = 278,
     LAND_COLLISION_END = 279,
     TIMER = 280,
     CHAT = 281,
     SENSOR = 282,
     NO_SENSOR = 283,
     CONTROL = 284,
     AT_TARGET = 285,
     NOT_AT_TARGET = 286,
     AT_ROT_TARGET = 287,
     NOT_AT_ROT_TARGET = 288,
     MONEY = 289,
     EMAIL = 290,
     RUN_TIME_PERMISSIONS = 291,
     INVENTORY = 292,
     ATTACH = 293,
     DATASERVER = 294,
     MOVING_START = 295,
     MOVING_END = 296,
     REZ = 297,
     OBJECT_REZ = 298,
     LINK_MESSAGE = 299,
     REMOTE_DATA = 300,
     HTTP_RESPONSE = 301,
     HTTP_REQUEST = 302,
     IDENTIFIER = 303,
     STATE_DEFAULT = 304,
     INTEGER_CONSTANT = 305,
     INTEGER_TRUE = 306,
     INTEGER_FALSE = 307,
     FP_CONSTANT = 308,
     STRING_CONSTANT = 309,
     INC_OP = 310,
     DEC_OP = 311,
     ADD_ASSIGN = 312,
     SUB_ASSIGN = 313,
     MUL_ASSIGN = 314,
     DIV_ASSIGN = 315,
     MOD_ASSIGN = 316,
     EQ = 317,
     NEQ = 318,
     GEQ = 319,
     LEQ = 320,
     BOOLEAN_AND = 321,
     BOOLEAN_OR = 322,
     SHIFT_LEFT = 323,
     SHIFT_RIGHT = 324,
     IF = 325,
     ELSE = 326,
     FOR = 327,
     DO = 328,
     WHILE = 329,
     PRINT = 330,
     PERIOD = 331,
     ZERO_VECTOR = 332,
     ZERO_ROTATION = 333,
     TOUCH_INVALID_VECTOR = 334,
     TOUCH_INVALID_TEXCOORD = 335,
     LOWER_THAN_ELSE = 336,
     INITIALIZER = 337
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 38 "indra.y"

	S32								ival;
	F32								fval;
	char							*sval;
	class LLScriptType				*type;
	class LLScriptConstant			*constant;
	class LLScriptIdentifier		*identifier;
	class LLScriptSimpleAssignable	*assignable;
	class LLScriptGlobalVariable	*global;
	class LLScriptEvent				*event;
	class LLScriptEventHandler		*handler;
	class LLScriptExpression		*expression;
	class LLScriptStatement			*statement;
	class LLScriptGlobalFunctions	*global_funcs;
	class LLScriptFunctionDec		*global_decl;
	class LLScriptState				*state;
	class LLScritpGlobalStorage		*global_store;
	class LLScriptScript			*script;



/* Line 214 of yacc.c  */
#line 250 "indra_generated.y.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 262 "indra_generated.y.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1284

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  105
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  215
/* YYNRULES -- Number of states.  */
#define YYNSTATES  582

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   337

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,     2,     2,    93,    94,     2,
      97,    98,    91,    90,   100,    84,     2,    92,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    82,
      88,    87,    89,     2,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   101,     2,   102,    96,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   103,    95,   104,    86,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    99
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    13,    15,    17,    20,
      23,    28,    30,    32,    34,    36,    38,    40,    42,    44,
      46,    49,    51,    53,    55,    58,    60,    62,    70,    72,
      74,    76,    86,    88,    92,    95,    97,   101,   103,   105,
     107,   109,   111,   113,   115,   117,   122,   127,   133,   139,
     141,   145,   148,   150,   153,   155,   158,   163,   169,   171,
     174,   177,   180,   183,   186,   189,   192,   195,   198,   201,
     204,   207,   210,   213,   216,   219,   222,   225,   228,   231,
     234,   237,   240,   243,   246,   249,   252,   255,   258,   261,
     264,   267,   270,   273,   276,   280,   284,   290,   296,   302,
     308,   314,   320,   326,   332,   338,   350,   354,   366,   370,
     379,   397,   403,   409,   415,   424,   428,   432,   436,   451,
     457,   461,   473,   479,   485,   500,   521,   536,   548,   551,
     555,   557,   560,   562,   566,   570,   574,   578,   582,   585,
     588,   591,   593,   599,   607,   617,   625,   631,   634,   639,
     640,   642,   644,   648,   649,   651,   653,   657,   658,   660,
     662,   666,   668,   672,   676,   680,   684,   688,   692,   696,
     700,   704,   708,   712,   716,   720,   724,   728,   732,   736,
     740,   744,   748,   752,   756,   760,   764,   767,   770,   773,
     776,   779,   781,   783,   787,   792,   797,   802,   809,   811,
     813,   815,   817,   820,   823,   828,   833,   835,   843,   845,
     847,   849,   859,   861,   865,   867
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     106,     0,    -1,   107,   126,    -1,   126,    -1,   108,    -1,
     108,   107,    -1,   110,    -1,   123,    -1,   122,    48,    -1,
     109,    82,    -1,   109,    87,   111,    82,    -1,   112,    -1,
     119,    -1,    48,    -1,   113,    -1,   116,    -1,   115,    -1,
     114,    -1,    54,    -1,    53,    -1,    84,    53,    -1,    50,
      -1,    51,    -1,    52,    -1,    84,    50,    -1,   117,    -1,
     118,    -1,    88,   111,   100,   111,   100,   111,    89,    -1,
      77,    -1,    79,    -1,    80,    -1,    88,   111,   100,   111,
     100,   111,   100,   111,    89,    -1,    78,    -1,   101,   120,
     102,    -1,   101,   102,    -1,   121,    -1,   121,   100,   120,
      -1,   112,    -1,     3,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,     8,    -1,     9,    -1,    48,    97,    98,
     166,    -1,   109,    97,    98,   166,    -1,    48,    97,   124,
      98,   166,    -1,   109,    97,   124,    98,   166,    -1,   125,
      -1,   125,   100,   124,    -1,   122,    48,    -1,   128,    -1,
     128,   127,    -1,   129,    -1,   129,   127,    -1,    49,   103,
     130,   104,    -1,    10,    48,   103,   130,   104,    -1,   131,
      -1,   131,   130,    -1,   132,   166,    -1,   133,   166,    -1,
     134,   166,    -1,   135,   166,    -1,   136,   166,    -1,   137,
     166,    -1,   138,   166,    -1,   139,   166,    -1,   140,   166,
      -1,   141,   166,    -1,   142,   166,    -1,   155,   166,    -1,
     156,   166,    -1,   157,   166,    -1,   158,   166,    -1,   143,
     166,    -1,   144,   166,    -1,   145,   166,    -1,   146,   166,
      -1,   147,   166,    -1,   148,   166,    -1,   149,   166,    -1,
     150,   166,    -1,   151,   166,    -1,   152,   166,    -1,   159,
     166,    -1,   153,   166,    -1,   154,   166,    -1,   160,   166,
      -1,   161,   166,    -1,   162,   166,    -1,   163,   166,    -1,
     164,   166,    -1,   165,   166,    -1,    14,    97,    98,    -1,
      15,    97,    98,    -1,    16,    97,     3,    48,    98,    -1,
      17,    97,     3,    48,    98,    -1,    18,    97,     3,    48,
      98,    -1,    19,    97,     3,    48,    98,    -1,    20,    97,
       3,    48,    98,    -1,    21,    97,     3,    48,    98,    -1,
      22,    97,     7,    48,    98,    -1,    23,    97,     7,    48,
      98,    -1,    24,    97,     7,    48,    98,    -1,    30,    97,
       3,    48,   100,     7,    48,   100,     7,    48,    98,    -1,
      31,    97,    98,    -1,    32,    97,     3,    48,   100,     8,
      48,   100,     8,    48,    98,    -1,    33,    97,    98,    -1,
      34,    97,     6,    48,   100,     3,    48,    98,    -1,    35,
      97,     5,    48,   100,     5,    48,   100,     5,    48,   100,
       5,    48,   100,     3,    48,    98,    -1,    36,    97,     3,
      48,    98,    -1,    37,    97,     3,    48,    98,    -1,    38,
      97,     6,    48,    98,    -1,    39,    97,     6,    48,   100,
       5,    48,    98,    -1,    40,    97,    98,    -1,    41,    97,
      98,    -1,    25,    97,    98,    -1,    26,    97,     3,    48,
     100,     5,    48,   100,     6,    48,   100,     5,    48,    98,
      -1,    27,    97,     3,    48,    98,    -1,    28,    97,    98,
      -1,    29,    97,     6,    48,   100,     3,    48,   100,     3,
      48,    98,    -1,    42,    97,     3,    48,    98,    -1,    43,
      97,     6,    48,    98,    -1,    44,    97,     3,    48,   100,
       3,    48,   100,     5,    48,   100,     6,    48,    98,    -1,
      45,    97,     3,    48,   100,     6,    48,   100,     6,    48,
     100,     5,    48,   100,     3,    48,   100,     5,    48,    98,
      -1,    46,    97,     6,    48,   100,     3,    48,   100,     9,
      48,   100,     5,    48,    98,    -1,    47,    97,     6,    48,
     100,     5,    48,   100,     5,    48,    98,    -1,   103,   104,
      -1,   103,   167,   104,    -1,   168,    -1,   167,   168,    -1,
      82,    -1,    10,    48,    82,    -1,    10,    49,    82,    -1,
      12,    48,    82,    -1,    83,    48,    82,    -1,    13,   176,
      82,    -1,    13,    82,    -1,   176,    82,    -1,   169,    82,
      -1,   166,    -1,    70,    97,   176,    98,   168,    -1,    70,
      97,   176,    98,   168,    71,   168,    -1,    72,    97,   170,
      82,   176,    82,   170,    98,   168,    -1,    73,   168,    74,
      97,   176,    98,    82,    -1,    74,    97,   176,    98,   168,
      -1,   122,    48,    -1,   122,    48,    87,   176,    -1,    -1,
     171,    -1,   176,    -1,   176,   100,   171,    -1,    -1,   173,
      -1,   176,    -1,   176,   100,   173,    -1,    -1,   175,    -1,
     176,    -1,   176,   100,   175,    -1,   177,    -1,   183,    87,
     176,    -1,   183,    57,   176,    -1,   183,    58,   176,    -1,
     183,    59,   176,    -1,   183,    60,   176,    -1,   183,    61,
     176,    -1,   176,    62,   176,    -1,   176,    63,   176,    -1,
     176,    65,   176,    -1,   176,    64,   176,    -1,   176,    88,
     176,    -1,   176,    89,   176,    -1,   176,    90,   176,    -1,
     176,    84,   176,    -1,   176,    91,   176,    -1,   176,    92,
     176,    -1,   176,    93,   176,    -1,   176,    94,   176,    -1,
     176,    95,   176,    -1,   176,    96,   176,    -1,   176,    66,
     176,    -1,   176,    67,   176,    -1,   176,    68,   176,    -1,
     176,    69,   176,    -1,    84,   176,    -1,    85,   176,    -1,
      86,   176,    -1,    55,   183,    -1,    56,   183,    -1,   178,
      -1,   179,    -1,    97,   176,    98,    -1,    97,   122,    98,
     183,    -1,    97,   122,    98,   113,    -1,    97,   122,    98,
     179,    -1,    97,   122,    98,    97,   176,    98,    -1,   180,
      -1,   181,    -1,   182,    -1,   183,    -1,   183,    55,    -1,
     183,    56,    -1,    48,    97,   172,    98,    -1,    75,    97,
     176,    98,    -1,   113,    -1,    88,   176,   100,   176,   100,
     176,    89,    -1,    77,    -1,    79,    -1,    80,    -1,    88,
     176,   100,   176,   100,   176,   100,   176,    89,    -1,    78,
      -1,   101,   174,   102,    -1,    48,    -1,    48,    76,    48,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   284,   284,   290,   299,   303,   311,   316,   324,   332,
     337,   345,   349,   356,   363,   368,   375,   380,   385,   393,
     397,   404,   408,   412,   416,   423,   427,   434,   439,   456,
     473,   493,   498,   522,   527,   535,   539,   547,   554,   559,
     564,   569,   574,   579,   584,   592,   599,   604,   611,   619,
     623,   631,   641,   645,   653,   657,   665,   675,   685,   689,
     697,   702,   707,   712,   717,   722,   727,   732,   737,   742,
     747,   752,   757,   762,   767,   772,   777,   782,   787,   792,
     797,   802,   807,   812,   817,   822,   827,   832,   837,   842,
     847,   852,   857,   862,   870,   878,   886,   896,   906,   916,
     926,   936,   946,   956,   966,   976,   990,   998,  1012,  1020,
    1032,  1050,  1060,  1070,  1080,  1092,  1100,  1108,  1116,  1132,
    1142,  1150,  1164,  1174,  1184,  1200,  1220,  1236,  1250,  1255,
    1263,  1267,  1275,  1280,  1287,  1294,  1301,  1308,  1313,  1318,
    1323,  1327,  1331,  1337,  1344,  1350,  1356,  1365,  1372,  1383,
    1386,  1393,  1398,  1407,  1410,  1417,  1422,  1431,  1434,  1441,
    1446,  1454,  1458,  1463,  1468,  1473,  1478,  1483,  1488,  1493,
    1498,  1503,  1508,  1513,  1518,  1523,  1528,  1533,  1538,  1543,
    1548,  1553,  1558,  1563,  1568,  1573,  1581,  1586,  1591,  1596,
    1601,  1606,  1610,  1614,  1622,  1627,  1634,  1639,  1647,  1651,
    1655,  1659,  1663,  1668,  1673,  1680,  1685,  1693,  1698,  1715,
    1732,  1752,  1757,  1781,  1789,  1796
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "FLOAT_TYPE", "STRING",
  "LLKEY", "VECTOR", "QUATERNION", "LIST", "STATE", "EVENT", "JUMP",
  "RETURN", "STATE_ENTRY", "STATE_EXIT", "TOUCH_START", "TOUCH",
  "TOUCH_END", "COLLISION_START", "COLLISION", "COLLISION_END",
  "LAND_COLLISION_START", "LAND_COLLISION", "LAND_COLLISION_END", "TIMER",
  "CHAT", "SENSOR", "NO_SENSOR", "CONTROL", "AT_TARGET", "NOT_AT_TARGET",
  "AT_ROT_TARGET", "NOT_AT_ROT_TARGET", "MONEY", "EMAIL",
  "RUN_TIME_PERMISSIONS", "INVENTORY", "ATTACH", "DATASERVER",
  "MOVING_START", "MOVING_END", "REZ", "OBJECT_REZ", "LINK_MESSAGE",
  "REMOTE_DATA", "HTTP_RESPONSE", "HTTP_REQUEST", "IDENTIFIER",
  "STATE_DEFAULT", "INTEGER_CONSTANT", "INTEGER_TRUE", "INTEGER_FALSE",
  "FP_CONSTANT", "STRING_CONSTANT", "INC_OP", "DEC_OP", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "EQ", "NEQ",
  "GEQ", "LEQ", "BOOLEAN_AND", "BOOLEAN_OR", "SHIFT_LEFT", "SHIFT_RIGHT",
  "IF", "ELSE", "FOR", "DO", "WHILE", "PRINT", "PERIOD", "ZERO_VECTOR",
  "ZERO_ROTATION", "TOUCH_INVALID_VECTOR", "TOUCH_INVALID_TEXCOORD",
  "LOWER_THAN_ELSE", "';'", "'@'", "'-'", "'!'", "'~'", "'='", "'<'",
  "'>'", "'+'", "'*'", "'/'", "'%'", "'&'", "'|'", "'^'", "'('", "')'",
  "INITIALIZER", "','", "'['", "']'", "'{'", "'}'", "$accept",
  "lscript_program", "globals", "global", "name_type", "global_variable",
  "simple_assignable", "simple_assignable_no_list", "constant",
  "fp_constant", "integer_constant", "special_constant", "vector_constant",
  "quaternion_constant", "list_constant", "list_entries", "list_entry",
  "typename", "global_function", "function_parameters",
  "function_parameter", "states", "other_states", "default", "state",
  "state_body", "event", "state_entry", "state_exit", "touch_start",
  "touch", "touch_end", "collision_start", "collision", "collision_end",
  "land_collision_start", "land_collision", "land_collision_end",
  "at_target", "not_at_target", "at_rot_target", "not_at_rot_target",
  "money", "email", "run_time_permissions", "inventory", "attach",
  "dataserver", "moving_start", "moving_end", "timer", "chat", "sensor",
  "no_sensor", "control", "rez", "object_rez", "link_message",
  "remote_data", "http_response", "http_request", "compound_statement",
  "statements", "statement", "declaration", "forexpressionlist",
  "nextforexpressionlist", "funcexpressionlist", "nextfuncexpressionlist",
  "listexpressionlist", "nextlistexpressionlist", "expression",
  "unaryexpression", "typecast", "unarypostfixexpression",
  "vector_initializer", "quaternion_initializer", "list_initializer",
  "lvalue", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,    59,    64,    45,    33,   126,    61,    60,    62,
      43,    42,    47,    37,    38,   124,    94,    40,    41,   337,
      44,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   105,   106,   106,   107,   107,   108,   108,   109,   110,
     110,   111,   111,   112,   112,   112,   113,   113,   113,   114,
     114,   115,   115,   115,   115,   116,   116,   117,   117,   117,
     117,   118,   118,   119,   119,   120,   120,   121,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   123,   123,   124,
     124,   125,   126,   126,   127,   127,   128,   129,   130,   130,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   166,
     167,   167,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   173,   173,   174,   174,   175,
     175,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   177,   177,   177,   177,
     177,   177,   177,   177,   178,   178,   178,   178,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   180,   180,   180,
     180,   181,   181,   182,   183,   183
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     2,     1,     1,     7,     1,     1,
       1,     9,     1,     3,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     5,     5,     1,
       3,     2,     1,     2,     1,     2,     4,     5,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     5,     5,     5,     5,
       5,     5,     5,     5,     5,    11,     3,    11,     3,     8,
      17,     5,     5,     5,     8,     3,     3,     3,    14,     5,
       3,    11,     5,     5,    14,    20,    14,    11,     2,     3,
       1,     2,     1,     3,     3,     3,     3,     3,     2,     2,
       2,     1,     5,     7,     9,     7,     5,     2,     4,     0,
       1,     1,     3,     0,     1,     1,     3,     0,     1,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       2,     1,     1,     3,     4,     4,     4,     6,     1,     1,
       1,     1,     2,     2,     4,     4,     1,     7,     1,     1,
       1,     9,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    38,    39,    40,    41,    42,    43,    44,     0,     0,
       0,     0,     4,     0,     6,     0,     7,     3,    52,     0,
       0,     1,     2,     5,     9,     0,     0,     8,     0,    53,
      54,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    21,    22,    23,    19,
      18,    28,    32,    29,    30,     0,     0,     0,     0,    11,
      14,    17,    16,    15,    25,    26,    12,     0,     0,     0,
      55,     0,    45,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    86,    87,    71,    72,    73,    74,    85,
      88,    89,    90,    91,    92,    93,    24,    20,     0,    34,
      37,     0,    35,    10,    46,     0,     0,     0,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,   208,   212,
     209,   210,   132,     0,     0,     0,     0,     0,     0,   157,
     128,   206,     0,   141,     0,   130,     0,     0,   161,   191,
     192,   198,   199,   200,   201,    47,    50,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,   120,     0,     0,   106,     0,   108,     0,     0,     0,
       0,     0,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,    33,     0,    48,     0,     0,     0,     0,   138,
       0,     0,   153,   214,   189,   190,     0,   149,     0,     0,
       0,     0,    21,    19,   186,   187,   188,     0,     0,     0,
       0,   158,   159,   147,   129,   131,   140,     0,     0,     0,
       0,     0,     0,     0,     0,   139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,   203,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,    57,   133,   134,   135,   137,   215,     0,   154,
     155,     0,     0,   150,   151,     0,     0,     0,   136,     0,
       0,   193,   213,     0,     0,   168,   169,   171,   170,   182,
     183,   184,   185,   175,   172,   173,   174,   176,   177,   178,
     179,   180,   181,   163,   164,   165,   166,   167,   162,    96,
      97,    98,    99,   100,   101,   102,   103,   104,     0,   119,
       0,     0,     0,     0,     0,   111,   112,   113,     0,   122,
     123,     0,     0,     0,     0,     0,   204,     0,     0,     0,
       0,     0,     0,   205,     0,     0,   195,   196,   194,   160,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   156,   142,     0,   152,     0,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,   149,     0,     0,   197,     0,
       0,     0,     0,   109,     0,   114,     0,     0,     0,     0,
       0,   143,     0,   145,   207,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   144,   211,     0,
     121,   105,   107,     0,     0,     0,     0,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,     0,
     124,     0,   126,     0,     0,     0,     0,   110,     0,     0,
       0,   125
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    14,   118,   119,   241,   121,
     122,   123,   124,   125,   126,   211,   212,   242,    16,    33,
      34,    17,    29,    18,    30,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   243,   244,   245,   246,   392,   393,   388,   389,   320,
     321,   247,   248,   249,   250,   251,   252,   253,   254
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -218
static const yytype_int16 yypact[] =
{
     104,  -218,  -218,  -218,  -218,  -218,  -218,  -218,   -92,   -91,
      19,   -20,   254,     3,  -218,   -17,  -218,  -218,    30,    74,
    1194,  -218,  -218,  -218,  -218,   626,   206,  -218,    -7,  -218,
      30,   -19,    50,     7,    49,    53,    57,    66,    69,    80,
      81,    82,    84,    85,    86,    87,    88,    95,   119,   120,
     121,   122,   123,   124,   126,   131,   136,   142,   145,   146,
     153,   154,   167,   168,   177,   178,   180,   181,   193,    67,
    1194,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,   -19,   -19,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,   -33,   626,   219,    93,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,   -19,   195,   188,
    -218,   152,  -218,  -218,   -19,   138,   196,   197,   297,   298,
     302,   303,   305,   306,   307,   308,   309,   212,   314,   315,
     215,   316,   317,   225,   322,   235,   328,   331,   334,   335,
     337,   338,   241,   243,   339,   341,   342,   349,   351,   357,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,   272,  -218,
    -218,   274,   278,  -218,  -218,   -19,  1194,   -15,   326,   454,
     -65,   354,   354,   285,   311,   386,   312,   318,  -218,  -218,
    -218,  -218,  -218,   355,   506,   520,   520,   520,   440,   520,
    -218,  -218,   358,  -218,   276,  -218,   325,   958,  -218,  -218,
    -218,  -218,  -218,  -218,   310,  -218,  -218,  -218,  -218,   366,
     368,   370,   371,   374,   375,   383,   384,   385,  -218,   387,
     402,  -218,   403,   404,  -218,   405,  -218,   406,   407,   409,
     414,   419,   425,  -218,  -218,   427,   428,   429,   431,   432,
     433,   626,  -218,   333,  -218,   378,   415,   416,   417,  -218,
     993,   436,   520,   410,  -218,  -218,   520,   520,   411,   520,
     520,   418,  -218,  -218,    -5,  -218,  -218,   628,   413,   784,
     399,  -218,   667,   426,  -218,  -218,  -218,   520,   520,   520,
     520,   520,   520,   520,   520,  -218,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,  -218,  -218,   520,   520,
     520,   520,   520,   520,   423,   424,   437,   445,   446,   447,
     448,   449,   450,   412,   451,   430,   452,   453,   463,   464,
     467,   468,   469,   477,   471,   480,   479,   482,   487,   488,
     489,  -218,  -218,  -218,  -218,  -218,  -218,  -218,   495,  -218,
     680,   821,   421,  -218,   719,   483,   834,   871,  -218,   520,
     584,  -218,  -218,   520,   520,   336,   336,   -54,   -54,  1111,
    1111,    11,    11,    -5,   -54,   -54,    -5,  -218,  -218,  -218,
    1191,   105,  1180,  1063,  1063,  1063,  1063,  1063,  1063,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,   509,  -218,
     513,   516,   519,   547,   591,  -218,  -218,  -218,   596,  -218,
    -218,   599,   603,   607,   606,   626,  -218,   520,   386,   520,
     520,   520,   386,  -218,   732,   520,  -218,  -218,    78,  -218,
    1063,   564,   565,   566,   567,   568,   570,   571,   581,   582,
     583,   585,   -82,  -218,   569,  1028,  -218,   884,  -218,   520,
     921,   539,   541,   542,   543,   546,   545,   548,   553,   554,
     555,   556,  -218,   626,   386,   520,   578,   771,  -218,   642,
     662,   659,   663,  -218,   665,  -218,   670,   661,   673,   678,
     595,  -218,   588,  -218,   572,   520,   639,   640,   641,   650,
     651,   652,   653,   654,   660,  -218,   386,  1076,   609,   613,
     615,   617,   625,   637,   638,   666,   643,  -218,   572,   702,
    -218,  -218,  -218,   721,   733,   735,   745,  -218,   704,   705,
     706,   717,   729,   681,   689,   692,   691,   694,  -218,   775,
    -218,   790,  -218,   754,   756,   707,   718,  -218,   801,   769,
     731,  -218
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -218,  -218,   818,  -218,  -218,  -218,  -115,  -113,   -25,  -218,
    -218,  -218,  -218,  -218,  -218,   538,  -218,    16,  -218,   -13,
    -218,   830,   812,  -218,  -218,   -68,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,   -28,  -218,  -217,  -218,   340,   394,  -218,   400,  -218,
     441,  -213,  -218,  -218,   443,  -218,  -218,  -218,  -212
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     120,   208,   171,   132,   210,    19,   300,   502,   308,   304,
     305,   301,    20,   128,   333,   334,    15,   206,   503,    21,
     207,   314,   315,   316,   317,   319,   322,   325,    15,     9,
     336,    27,   302,   296,   297,    32,   339,   340,   341,   342,
      28,   129,    32,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     1,     2,     3,
       4,     5,     6,     7,   131,    24,   340,   341,   342,   390,
      25,   120,   120,   391,   394,   336,   396,   397,   133,   214,
      26,   339,   340,   341,   342,   134,   255,     1,     2,     3,
       4,     5,     6,     7,   405,   406,   407,   408,   409,   410,
     411,   412,   256,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   346,   347,   423,   424,   425,   426,   427,
     428,     1,     2,     3,     4,     5,     6,     7,   295,   135,
     136,    32,     8,     9,   137,     1,     2,     3,     4,     5,
       6,     7,   217,   138,   218,   219,   139,   327,   328,   329,
     330,   170,    31,   333,   334,   213,   380,   140,   141,   142,
     210,   143,   144,   145,   146,   147,   464,   294,   468,   336,
     322,   470,   148,   337,   338,   339,   340,   341,   342,   343,
     220,   345,   106,   107,   108,   109,   110,   221,   222,     1,
       2,     3,     4,     5,     6,     7,   149,   150,   151,   152,
     153,   154,   223,   155,   224,   225,   226,   227,   156,   228,
     229,   230,   231,   157,   232,   233,   234,   235,   236,   158,
     237,   484,   159,   160,   390,   488,   485,   394,   487,   238,
     161,   162,   490,   239,   318,   131,   240,     1,     2,     3,
       4,     5,     6,     7,   163,   164,   120,   105,   120,   106,
     107,   108,   109,   110,   165,   166,   507,   167,   168,     1,
       2,     3,     4,     5,     6,     7,   217,   521,   218,   219,
     169,   216,   394,   215,   257,   258,   111,   112,   113,   114,
     259,   260,     8,   115,   127,   261,   262,   116,   263,   264,
     268,   415,   537,   271,   265,   266,   267,   269,   270,   547,
     273,   209,   272,   274,   220,   275,   106,   107,   108,   109,
     110,   221,   222,   276,   277,   415,   278,   279,   280,   283,
     482,   284,   285,   281,   282,   287,   223,   286,   224,   225,
     226,   227,   288,   228,   229,   230,   231,   289,   232,   233,
     234,   235,   236,   290,   237,   346,   347,   348,   349,   350,
     351,   352,   291,   238,   298,   466,   292,   239,   293,   131,
     324,   105,   306,   106,   107,   108,   109,   110,   520,     1,
       2,     3,     4,     5,     6,     7,   217,   353,   218,   219,
     329,   330,   303,   311,   333,   334,   323,   326,   307,   309,
     111,   112,   113,   114,   354,   310,   355,   115,   356,   357,
     336,   116,   358,   359,   337,   338,   339,   340,   341,   342,
     120,   360,   361,   362,   220,   363,   106,   107,   108,   109,
     110,   221,   222,     1,     2,     3,     4,     5,     6,     7,
     364,   365,   366,   367,   368,   369,   223,   370,   224,   225,
     226,   227,   371,   228,   229,   230,   231,   372,   232,   233,
     234,   235,   236,   373,   237,   374,   375,   376,   120,   377,
     378,   379,   382,   238,   387,   395,   301,   239,   220,   131,
     106,   107,   108,   109,   110,   221,   222,   383,   384,   385,
     398,   402,   220,   459,   106,   107,   108,   109,   110,   221,
     222,   400,   438,   404,   471,   227,   472,   228,   229,   230,
     231,   429,   430,   473,   234,   235,   236,   474,   237,   227,
     440,   228,   229,   230,   231,   431,   299,   238,   234,   235,
     236,   239,   237,   432,   433,   434,   435,   436,   437,   439,
     475,   238,   441,   442,   220,   239,   312,   107,   108,   313,
     110,   221,   222,   443,   444,   445,   446,   447,   220,   449,
     106,   107,   108,   109,   110,   221,   222,   448,   450,   451,
     461,   227,   452,   228,   229,   230,   231,   453,   454,   455,
     234,   235,   236,   456,   237,   227,   476,   228,   229,   230,
     231,   477,   478,   238,   234,   235,   236,   239,   237,   479,
     480,   481,   491,   492,   493,   494,   495,   238,   496,   497,
     220,   239,   106,   107,   108,   109,   110,   221,   222,   498,
     499,   500,   220,   501,   106,   107,   108,   109,   110,   509,
     504,   510,   511,   512,   513,   514,   515,   227,   526,   228,
     229,   230,   231,   516,   517,   518,   519,   235,   236,   227,
     523,   228,   229,   230,   231,   527,   528,   532,   115,   238,
     530,   529,   237,   239,   105,   531,   106,   107,   108,   109,
     110,   465,   533,   534,   535,   239,   536,   538,   539,   540,
     327,   328,   329,   330,   331,   332,   333,   334,   541,   542,
     543,   544,   545,   111,   112,   113,   114,   558,   546,   549,
     115,   550,   336,   551,   116,   552,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   553,   559,   117,   399,   327,
     328,   329,   330,   331,   332,   333,   334,   554,   555,   560,
     561,   557,   327,   328,   329,   330,   331,   332,   333,   334,
     562,   336,   563,   564,   565,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   336,   566,   556,   403,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   567,   573,   568,
     457,   327,   328,   329,   330,   331,   332,   333,   334,   569,
     570,   571,   572,   574,   327,   328,   329,   330,   331,   332,
     333,   334,   575,   336,   576,   577,   579,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   336,   580,   578,   460,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   581,
      23,   381,   489,   327,   328,   329,   330,   331,   332,   333,
     334,    22,   130,   467,   469,   522,   327,   328,   329,   330,
     331,   332,   333,   334,   486,   336,     0,   483,     0,   337,
     524,   339,   340,   341,   342,   343,   344,   345,   336,     0,
       0,   525,   337,   338,   339,   340,   341,   342,   343,   344,
     345,     0,   401,   327,   328,   329,   330,   331,   332,   333,
     334,     0,     0,     0,     0,     0,   327,   328,   329,   330,
     331,   332,   333,   334,     0,   336,     0,     0,     0,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   336,   458,
       0,     0,   337,   338,   339,   340,   341,   342,   343,   344,
     345,     0,   462,   327,   328,   329,   330,   331,   332,   333,
     334,     0,     0,     0,     0,     0,   327,   328,   329,   330,
     331,   332,   333,   334,     0,   336,     0,     0,     0,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   336,   463,
       0,     0,   337,   338,   339,   340,   341,   342,   343,   344,
     345,     0,   506,   327,   328,   329,   330,   331,   332,   333,
     334,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   336,     0,     0,     0,   337,
     338,   339,   340,   341,   342,   343,   344,   345,     0,   508,
     327,   328,   329,   330,   331,   332,   333,   334,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     335,     0,   336,     0,     0,     0,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   327,   328,   329,   330,   331,
     332,   333,   334,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   386,     0,   336,     0,     0,
       0,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     327,   328,   329,   330,   331,   332,   333,   334,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     505,     0,   336,     0,     0,     0,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   327,   328,   329,   330,   331,
     332,   333,   334,     0,     0,     0,     0,     0,   327,   328,
     329,   330,   331,   332,   333,   334,     0,   336,     0,     0,
       0,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     336,     0,     0,     0,   337,   548,   339,   340,   341,   342,
     343,   344,   345,   327,   328,   329,   330,     0,     0,   333,
     334,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   336,     0,     0,     0,   337,
     338,   339,   340,   341,   342,   343,   344,   345,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,   327,   328,   329,   330,     0,     0,   333,   334,
       0,     0,     0,   327,   328,   329,   330,     0,     0,   333,
     334,     0,     0,     0,   336,     0,     0,     0,   337,   338,
     339,   340,   341,   342,   343,   336,     0,     0,     0,   337,
     338,   339,   340,   341,   342
};

static const yytype_int16 yycheck[] =
{
      25,   116,    70,    31,   117,    97,   219,    89,   225,   221,
     222,    76,   103,    26,    68,    69,     0,    50,   100,     0,
      53,   234,   235,   236,   237,   238,   239,   244,    12,    49,
      84,    48,    97,    48,    49,    19,    90,    91,    92,    93,
      10,    48,    26,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     3,     4,     5,
       6,     7,     8,     9,   103,    82,    91,    92,    93,   302,
      87,   116,   117,   306,   307,    84,   309,   310,    48,   127,
      97,    90,    91,    92,    93,    98,   134,     3,     4,     5,
       6,     7,     8,     9,   327,   328,   329,   330,   331,   332,
     333,   334,   135,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,    55,    56,   348,   349,   350,   351,   352,
     353,     3,     4,     5,     6,     7,     8,     9,   216,   100,
      97,   135,    48,    49,    97,     3,     4,     5,     6,     7,
       8,     9,    10,    97,    12,    13,    97,    62,    63,    64,
      65,   104,    98,    68,    69,    82,   291,    97,    97,    97,
     293,    97,    97,    97,    97,    97,   399,   215,   400,    84,
     403,   404,    97,    88,    89,    90,    91,    92,    93,    94,
      48,    96,    50,    51,    52,    53,    54,    55,    56,     3,
       4,     5,     6,     7,     8,     9,    97,    97,    97,    97,
      97,    97,    70,    97,    72,    73,    74,    75,    97,    77,
      78,    79,    80,    97,    82,    83,    84,    85,    86,    97,
      88,   458,    97,    97,   457,   462,   459,   460,   461,    97,
      97,    97,   465,   101,   238,   103,   104,     3,     4,     5,
       6,     7,     8,     9,    97,    97,   291,    48,   293,    50,
      51,    52,    53,    54,    97,    97,   489,    97,    97,     3,
       4,     5,     6,     7,     8,     9,    10,   504,    12,    13,
      97,   103,   505,    98,    98,    98,    77,    78,    79,    80,
       3,     3,    48,    84,    98,     3,     3,    88,     3,     3,
      98,   524,   525,    98,     7,     7,     7,     3,     3,   536,
       3,   102,     6,    98,    48,     3,    50,    51,    52,    53,
      54,    55,    56,    98,     6,   548,     5,     3,     3,    98,
     455,    98,     3,     6,     6,     3,    70,     6,    72,    73,
      74,    75,     3,    77,    78,    79,    80,     6,    82,    83,
      84,    85,    86,     6,    88,    55,    56,    57,    58,    59,
      60,    61,   100,    97,    48,   400,   102,   101,   100,   103,
     104,    48,    97,    50,    51,    52,    53,    54,   503,     3,
       4,     5,     6,     7,     8,     9,    10,    87,    12,    13,
      64,    65,    48,    48,    68,    69,    48,    82,    97,    97,
      77,    78,    79,    80,    48,    97,    48,    84,    48,    48,
      84,    88,    48,    48,    88,    89,    90,    91,    92,    93,
     455,    48,    48,    48,    48,    48,    50,    51,    52,    53,
      54,    55,    56,     3,     4,     5,     6,     7,     8,     9,
      48,    48,    48,    48,    48,    48,    70,    48,    72,    73,
      74,    75,    48,    77,    78,    79,    80,    48,    82,    83,
      84,    85,    86,    48,    88,    48,    48,    48,   503,    48,
      48,    48,   104,    97,    48,    74,    76,   101,    48,   103,
      50,    51,    52,    53,    54,    55,    56,    82,    82,    82,
      82,   102,    48,    82,    50,    51,    52,    53,    54,    55,
      56,    98,   100,    87,     5,    75,     3,    77,    78,    79,
      80,    98,    98,     7,    84,    85,    86,     8,    88,    75,
     100,    77,    78,    79,    80,    98,    82,    97,    84,    85,
      86,   101,    88,    98,    98,    98,    98,    98,    98,    98,
       3,    97,   100,   100,    48,   101,    50,    51,    52,    53,
      54,    55,    56,   100,   100,    98,    98,    98,    48,    98,
      50,    51,    52,    53,    54,    55,    56,   100,    98,   100,
      97,    75,   100,    77,    78,    79,    80,   100,   100,   100,
      84,    85,    86,    98,    88,    75,     5,    77,    78,    79,
      80,     5,     3,    97,    84,    85,    86,   101,    88,     6,
       3,     5,    48,    48,    48,    48,    48,    97,    48,    48,
      48,   101,    50,    51,    52,    53,    54,    55,    56,    48,
      48,    48,    48,    48,    50,    51,    52,    53,    54,   100,
      71,   100,   100,   100,    98,   100,    98,    75,     6,    77,
      78,    79,    80,   100,   100,   100,   100,    85,    86,    75,
      82,    77,    78,    79,    80,     3,     7,     6,    84,    97,
       5,     8,    88,   101,    48,     5,    50,    51,    52,    53,
      54,    97,     9,     5,    89,   101,    98,    48,    48,    48,
      62,    63,    64,    65,    66,    67,    68,    69,    48,    48,
      48,    48,    48,    77,    78,    79,    80,     5,    48,   100,
      84,    98,    84,    98,    88,    98,    88,    89,    90,    91,
      92,    93,    94,    95,    96,   100,     5,   101,   100,    62,
      63,    64,    65,    66,    67,    68,    69,   100,   100,     6,
       5,    98,    62,    63,    64,    65,    66,    67,    68,    69,
       5,    84,    48,    48,    48,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    84,    48,   100,   100,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    48,     3,    98,
     100,    62,    63,    64,    65,    66,    67,    68,    69,   100,
      98,   100,    98,     3,    62,    63,    64,    65,    66,    67,
      68,    69,    48,    84,    48,    98,     5,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    84,    48,   100,   100,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    98,
      12,   293,   100,    62,    63,    64,    65,    66,    67,    68,
      69,    11,    30,   400,   403,   505,    62,    63,    64,    65,
      66,    67,    68,    69,   460,    84,    -1,   457,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    84,    -1,
      -1,   100,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    -1,    98,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    84,    98,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    -1,    98,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    -1,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    84,    98,
      -1,    -1,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    -1,    98,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    -1,    98,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    62,    63,    64,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    62,    63,    64,    65,    -1,    -1,    68,    69,
      -1,    -1,    -1,    62,    63,    64,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    48,    49,
     106,   107,   108,   109,   110,   122,   123,   126,   128,    97,
     103,     0,   126,   107,    82,    87,    97,    48,    10,   127,
     129,    98,   122,   124,   125,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,    48,    50,    51,    52,    53,
      54,    77,    78,    79,    80,    84,    88,   101,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    98,   124,    48,
     127,   103,   166,    48,    98,   100,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
     104,   130,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,    50,    53,   111,   102,
     112,   120,   121,    82,   166,    98,   103,    10,    12,    13,
      48,    55,    56,    70,    72,    73,    74,    75,    77,    78,
      79,    80,    82,    83,    84,    85,    86,    88,    97,   101,
     104,   113,   122,   166,   167,   168,   169,   176,   177,   178,
     179,   180,   181,   182,   183,   166,   124,    98,    98,     3,
       3,     3,     3,     3,     3,     7,     7,     7,    98,     3,
       3,    98,     6,     3,    98,     3,    98,     6,     5,     3,
       3,     6,     6,    98,    98,     3,     6,     3,     3,     6,
       6,   100,   102,   100,   166,   130,    48,    49,    48,    82,
     176,    76,    97,    48,   183,   183,    97,    97,   168,    97,
      97,    48,    50,    53,   176,   176,   176,   176,   122,   176,
     174,   175,   176,    48,   104,   168,    82,    62,    63,    64,
      65,    66,    67,    68,    69,    82,    84,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    55,    56,    57,    58,
      59,    60,    61,    87,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
     111,   120,   104,    82,    82,    82,    82,    48,   172,   173,
     176,   176,   170,   171,   176,    74,   176,   176,    82,   100,
      98,    98,   102,   100,    87,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,    98,
      98,    98,    98,    98,    98,    98,    98,    98,   100,    98,
     100,   100,   100,   100,   100,    98,    98,    98,   100,    98,
      98,   100,   100,   100,   100,   100,    98,   100,    98,    82,
     100,    97,    98,    98,   176,    97,   113,   179,   183,   175,
     176,     5,     3,     7,     8,     3,     5,     5,     3,     6,
       3,     5,   111,   173,   168,   176,   171,   176,   168,   100,
     176,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    89,   100,    71,    82,    98,   176,    98,   100,
     100,   100,   100,    98,   100,    98,   100,   100,   100,   100,
     111,   168,   170,    82,    89,   100,     6,     3,     7,     8,
       5,     5,     6,     9,     5,    89,    98,   176,    48,    48,
      48,    48,    48,    48,    48,    48,    48,   168,    89,   100,
      98,    98,    98,   100,   100,   100,   100,    98,     5,     5,
       6,     5,     5,    48,    48,    48,    48,    48,    98,   100,
      98,   100,    98,     3,     3,    48,    48,    98,   100,     5,
      48,    98
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1455 of yacc.c  */
#line 285 "indra.y"
    {
		(yyval.script) = new LLScriptScript((yyvsp[(1) - (2)].global_store), (yyvsp[(2) - (2)].state));
		gAllocationManager->addAllocation((yyval.script));
		gScriptp = (yyval.script);
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 291 "indra.y"
    {
		(yyval.script) = new LLScriptScript(NULL, (yyvsp[(1) - (1)].state));
		gAllocationManager->addAllocation((yyval.script));
		gScriptp = (yyval.script);
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 300 "indra.y"
    {
		(yyval.global_store) = (yyvsp[(1) - (1)].global_store);
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 304 "indra.y"
    {
		(yyval.global_store) = (yyvsp[(1) - (2)].global_store);
		(yyvsp[(1) - (2)].global_store)->addGlobal((yyvsp[(2) - (2)].global_store));
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 312 "indra.y"
    {
		(yyval.global_store) = new LLScritpGlobalStorage((yyvsp[(1) - (1)].global));
		gAllocationManager->addAllocation((yyval.global_store));
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 317 "indra.y"
    {
		(yyval.global_store) = new LLScritpGlobalStorage((yyvsp[(1) - (1)].global_funcs));
		gAllocationManager->addAllocation((yyval.global_store));
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 325 "indra.y"
    {
		(yyval.identifier) = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (2)].sval), (yyvsp[(1) - (2)].type));	
		gAllocationManager->addAllocation((yyval.identifier));
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 333 "indra.y"
    {
		(yyval.global) = new LLScriptGlobalVariable(gLine, gColumn, (yyvsp[(1) - (2)].identifier)->mType, (yyvsp[(1) - (2)].identifier), NULL);
		gAllocationManager->addAllocation((yyval.global));
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 338 "indra.y"
    {
		(yyval.global) = new LLScriptGlobalVariable(gLine, gColumn, (yyvsp[(1) - (4)].identifier)->mType, (yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].assignable));
		gAllocationManager->addAllocation((yyval.global));
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 346 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 350 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 357 "indra.y"
    {
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (1)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.assignable) = new LLScriptSAIdentifier(gLine, gColumn, id);	
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 364 "indra.y"
    {
		(yyval.assignable) = new LLScriptSAConstant(gLine, gColumn, (yyvsp[(1) - (1)].constant));
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 369 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 376 "indra.y"
    {
		(yyval.constant) = new LLScriptConstantInteger(gLine, gColumn, (yyvsp[(1) - (1)].ival));
		gAllocationManager->addAllocation((yyval.constant));
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 381 "indra.y"
    {
		(yyval.constant) = new LLScriptConstantFloat(gLine, gColumn, (yyvsp[(1) - (1)].fval));
		gAllocationManager->addAllocation((yyval.constant));
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 386 "indra.y"
    {
		(yyval.constant) = new LLScriptConstantString(gLine, gColumn, (yyvsp[(1) - (1)].sval));
		gAllocationManager->addAllocation((yyval.constant));
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 394 "indra.y"
    {
		(yyval.fval) = (yyvsp[(1) - (1)].fval);
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 398 "indra.y"
    {
		(yyval.fval) = -(yyvsp[(2) - (2)].fval);
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 405 "indra.y"
    {
		(yyval.ival) = (yyvsp[(1) - (1)].ival);
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 409 "indra.y"
    {
		(yyval.ival) = (yyvsp[(1) - (1)].ival);
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 413 "indra.y"
    {
		(yyval.ival) = (yyvsp[(1) - (1)].ival);
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 417 "indra.y"
    {
		(yyval.ival) = -(yyvsp[(2) - (2)].ival);
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 424 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 428 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 435 "indra.y"
    {
		(yyval.assignable) = new LLScriptSAVector(gLine, gColumn, (yyvsp[(2) - (7)].assignable), (yyvsp[(4) - (7)].assignable), (yyvsp[(6) - (7)].assignable));
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 440 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptSAConstant *sa0 = new LLScriptSAConstant(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptSAConstant *sa1 = new LLScriptSAConstant(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptSAConstant *sa2 = new LLScriptSAConstant(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		(yyval.assignable) = new LLScriptSAVector(gLine, gColumn, sa0, sa1, sa2);
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 457 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptSAConstant *sa0 = new LLScriptSAConstant(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptSAConstant *sa1 = new LLScriptSAConstant(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptSAConstant *sa2 = new LLScriptSAConstant(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		(yyval.assignable) = new LLScriptSAVector(gLine, gColumn, sa0, sa1, sa2);
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 474 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, -1.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptSAConstant *sa0 = new LLScriptSAConstant(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, -1.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptSAConstant *sa1 = new LLScriptSAConstant(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptSAConstant *sa2 = new LLScriptSAConstant(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		(yyval.assignable) = new LLScriptSAVector(gLine, gColumn, sa0, sa1, sa2);
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 494 "indra.y"
    {
		(yyval.assignable) = new LLScriptSAQuaternion(gLine, gColumn, (yyvsp[(2) - (9)].assignable), (yyvsp[(4) - (9)].assignable), (yyvsp[(6) - (9)].assignable), (yyvsp[(8) - (9)].assignable));
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 499 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptSAConstant *sa0 = new LLScriptSAConstant(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptSAConstant *sa1 = new LLScriptSAConstant(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptSAConstant *sa2 = new LLScriptSAConstant(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		LLScriptConstantFloat *cf3 = new LLScriptConstantFloat(gLine, gColumn, 1.f);
		gAllocationManager->addAllocation(cf3);
		LLScriptSAConstant *sa3 = new LLScriptSAConstant(gLine, gColumn, cf3);
		gAllocationManager->addAllocation(sa3);
		(yyval.assignable) = new LLScriptSAQuaternion(gLine, gColumn, sa0, sa1, sa2, sa3);
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 523 "indra.y"
    {
		(yyval.assignable) = new LLScriptSAList(gLine, gColumn, (yyvsp[(2) - (3)].assignable));
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 528 "indra.y"
    {
		(yyval.assignable) = new LLScriptSAList(gLine, gColumn, NULL);
		gAllocationManager->addAllocation((yyval.assignable));
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 536 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 540 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (3)].assignable);
		(yyvsp[(1) - (3)].assignable)->addAssignable((yyvsp[(3) - (3)].assignable));
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 548 "indra.y"
    {
		(yyval.assignable) = (yyvsp[(1) - (1)].assignable);
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 555 "indra.y"
    {  
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_INTEGER);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 560 "indra.y"
    {  
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_FLOATINGPOINT);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 565 "indra.y"
    {  
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_STRING);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 570 "indra.y"
    {  
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_KEY);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 575 "indra.y"
    {  
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_VECTOR);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 580 "indra.y"
    {  
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_QUATERNION);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 585 "indra.y"
    {
		(yyval.type) = new LLScriptType(gLine, gColumn, LST_LIST);
		gAllocationManager->addAllocation((yyval.type));
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 593 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (4)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.global_funcs) = new LLScriptGlobalFunctions(gLine, gColumn, NULL, id, NULL, (yyvsp[(4) - (4)].statement));
		gAllocationManager->addAllocation((yyval.global_funcs));
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 600 "indra.y"
    {
		(yyval.global_funcs) = new LLScriptGlobalFunctions(gLine, gColumn, (yyvsp[(1) - (4)].identifier)->mType, (yyvsp[(1) - (4)].identifier), NULL, (yyvsp[(4) - (4)].statement));
		gAllocationManager->addAllocation((yyval.global_funcs));
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 605 "indra.y"
    {
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (5)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.global_funcs) = new LLScriptGlobalFunctions(gLine, gColumn, NULL, id, (yyvsp[(3) - (5)].global_decl), (yyvsp[(5) - (5)].statement));
		gAllocationManager->addAllocation((yyval.global_funcs));
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 612 "indra.y"
    {  
		(yyval.global_funcs) = new LLScriptGlobalFunctions(gLine, gColumn, (yyvsp[(1) - (5)].identifier)->mType, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].global_decl), (yyvsp[(5) - (5)].statement));
		gAllocationManager->addAllocation((yyval.global_funcs));
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 620 "indra.y"
    {  
		(yyval.global_decl) = (yyvsp[(1) - (1)].global_decl);
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 624 "indra.y"
    {  
		(yyval.global_decl) = (yyvsp[(1) - (3)].global_decl);
		(yyvsp[(1) - (3)].global_decl)->addFunctionParameter((yyvsp[(3) - (3)].global_decl));
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 632 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (2)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.global_decl) = new LLScriptFunctionDec(gLine, gColumn, (yyvsp[(1) - (2)].type), id);
		gAllocationManager->addAllocation((yyval.global_decl));
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 642 "indra.y"
    {  
		(yyval.state) = (yyvsp[(1) - (1)].state);
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 646 "indra.y"
    {  
		(yyval.state) = (yyvsp[(1) - (2)].state);
		(yyvsp[(1) - (2)].state)->mNextp = (yyvsp[(2) - (2)].state);
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 654 "indra.y"
    {  
		(yyval.state) = (yyvsp[(1) - (1)].state);
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 658 "indra.y"
    {  
		(yyval.state) = (yyvsp[(1) - (2)].state);
		(yyvsp[(1) - (2)].state)->addState((yyvsp[(2) - (2)].state));
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 666 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (4)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.state) = new LLScriptState(gLine, gColumn, LSSTYPE_DEFAULT, id, (yyvsp[(3) - (4)].handler));
		gAllocationManager->addAllocation((yyval.state));
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 676 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (5)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.state) = new LLScriptState(gLine, gColumn, LSSTYPE_USER, id, (yyvsp[(4) - (5)].handler));
		gAllocationManager->addAllocation((yyval.state));
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 686 "indra.y"
    {  
		(yyval.handler) = (yyvsp[(1) - (1)].handler);
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 690 "indra.y"
    {  
		(yyval.handler) = (yyvsp[(1) - (2)].handler);
		(yyvsp[(1) - (2)].handler)->addEvent((yyvsp[(2) - (2)].handler));
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 698 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 703 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 708 "indra.y"
    {
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 713 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 718 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 723 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 728 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 733 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 738 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 743 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 748 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 753 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 758 "indra.y"
    {
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 763 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 768 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 773 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 778 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 783 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 788 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 793 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 798 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 803 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 808 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 813 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 818 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 823 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 828 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 833 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 838 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 843 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 848 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 853 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 858 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 863 "indra.y"
    {  
		(yyval.handler) = new LLScriptEventHandler(gLine, gColumn, (yyvsp[(1) - (2)].event), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.handler));
	;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 871 "indra.y"
    {  
		(yyval.event) = new LLScriptStateEntryEvent(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 879 "indra.y"
    {  
		(yyval.event) = new LLScriptStateExitEvent(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 887 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptTouchStartEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 897 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptTouchEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 907 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptTouchEndEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 917 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptCollisionStartEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 927 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptCollisionEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 937 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptCollisionEndEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 947 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptLandCollisionStartEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 957 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptLandCollisionEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 967 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptLandCollisionEndEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 977 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (11)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (11)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (11)].sval));	
		gAllocationManager->addAllocation(id3);
		(yyval.event) = new LLScriptAtTarget(gLine, gColumn, id1, id2, id3);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 991 "indra.y"
    {  
		(yyval.event) = new LLScriptNotAtTarget(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 999 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (11)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (11)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (11)].sval));	
		gAllocationManager->addAllocation(id3);
		(yyval.event) = new LLScriptAtRotTarget(gLine, gColumn, id1, id2, id3);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1013 "indra.y"
    {  
		(yyval.event) = new LLScriptNotAtRotTarget(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1021 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (8)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (8)].sval));	
		gAllocationManager->addAllocation(id2);
		(yyval.event) = new LLScriptMoneyEvent(gLine, gColumn, id1, id2);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1033 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (17)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (17)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (17)].sval));	
		gAllocationManager->addAllocation(id3);
		LLScriptIdentifier	*id4 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(13) - (17)].sval));	
		gAllocationManager->addAllocation(id4);
		LLScriptIdentifier	*id5 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(16) - (17)].sval));	
		gAllocationManager->addAllocation(id5);
		(yyval.event) = new LLScriptEmailEvent(gLine, gColumn, id1, id2, id3, id4, id5);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1051 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptRTPEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1061 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptInventoryEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1071 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptAttachEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1081 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (8)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (8)].sval));	
		gAllocationManager->addAllocation(id2);
		(yyval.event) = new LLScriptDataserverEvent(gLine, gColumn, id1, id2);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1093 "indra.y"
    {  
		(yyval.event) = new LLScriptMovingStartEvent(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1101 "indra.y"
    {  
		(yyval.event) = new LLScriptMovingEndEvent(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1109 "indra.y"
    {  
		(yyval.event) = new LLScriptTimerEvent(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1117 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (14)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (14)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (14)].sval));	
		gAllocationManager->addAllocation(id3);
		LLScriptIdentifier	*id4 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(13) - (14)].sval));	
		gAllocationManager->addAllocation(id4);
		(yyval.event) = new LLScriptChatEvent(gLine, gColumn, id1, id2, id3, id4);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1133 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptSensorEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1143 "indra.y"
    {  
		(yyval.event) = new LLScriptNoSensorEvent(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1151 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (11)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (11)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (11)].sval));	
		gAllocationManager->addAllocation(id3);
		(yyval.event) = new LLScriptControlEvent(gLine, gColumn, id1, id2, id3);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1165 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptRezEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1175 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (5)].sval));	
		gAllocationManager->addAllocation(id1);
		(yyval.event) = new LLScriptObjectRezEvent(gLine, gColumn, id1);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1185 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (14)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (14)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (14)].sval));	
		gAllocationManager->addAllocation(id3);
		LLScriptIdentifier	*id4 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(13) - (14)].sval));	
		gAllocationManager->addAllocation(id4);
		(yyval.event) = new LLScriptLinkMessageEvent(gLine, gColumn, id1, id2, id3, id4);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1201 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (20)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (20)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (20)].sval));	
		gAllocationManager->addAllocation(id3);
		LLScriptIdentifier	*id4 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(13) - (20)].sval));	
		gAllocationManager->addAllocation(id4);
		LLScriptIdentifier	*id5 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(16) - (20)].sval));	
		gAllocationManager->addAllocation(id4);
		LLScriptIdentifier	*id6 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(19) - (20)].sval));	
		gAllocationManager->addAllocation(id4);
		(yyval.event) = new LLScriptRemoteEvent(gLine, gColumn, id1, id2, id3, id4, id5, id6);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1221 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (14)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (14)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (14)].sval));	
		gAllocationManager->addAllocation(id3);
		LLScriptIdentifier	*id4 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(13) - (14)].sval));	
		gAllocationManager->addAllocation(id4);
		(yyval.event) = new LLScriptHTTPResponseEvent(gLine, gColumn, id1, id2, id3, id4);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1237 "indra.y"
    {  
		LLScriptIdentifier	*id1 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(4) - (11)].sval));	
		gAllocationManager->addAllocation(id1);
		LLScriptIdentifier	*id2 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(7) - (11)].sval));	
		gAllocationManager->addAllocation(id2);
		LLScriptIdentifier	*id3 = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(10) - (11)].sval));	
		gAllocationManager->addAllocation(id3);
		(yyval.event) = new LLScriptHTTPRequestEvent(gLine, gColumn, id1, id2, id3);
		gAllocationManager->addAllocation((yyval.event));
	;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1251 "indra.y"
    {  
		(yyval.statement) = new LLScriptCompoundStatement(gLine, gColumn, NULL);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1256 "indra.y"
    {  
		(yyval.statement) = new LLScriptCompoundStatement(gLine, gColumn, (yyvsp[(2) - (3)].statement));
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1264 "indra.y"
    {  
		(yyval.statement) = (yyvsp[(1) - (1)].statement);
	;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1268 "indra.y"
    {  
		(yyval.statement) = new LLScriptStatementSequence(gLine, gColumn, (yyvsp[(1) - (2)].statement), (yyvsp[(2) - (2)].statement));
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1276 "indra.y"
    {  
		(yyval.statement) = new LLScriptNOOP(gLine, gColumn);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1281 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (3)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.statement) = new LLScriptStateChange(gLine, gColumn, id);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1288 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (3)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.statement) = new LLScriptStateChange(gLine, gColumn, id);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1295 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (3)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.statement) = new LLScriptJump(gLine, gColumn, id);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1302 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (3)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.statement) = new LLScriptLabel(gLine, gColumn, id);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1309 "indra.y"
    {  
		(yyval.statement) = new LLScriptReturn(gLine, gColumn, (yyvsp[(2) - (3)].expression));
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1314 "indra.y"
    {  
		(yyval.statement) = new LLScriptReturn(gLine, gColumn, NULL);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1319 "indra.y"
    {  
		(yyval.statement) = new LLScriptExpressionStatement(gLine, gColumn, (yyvsp[(1) - (2)].expression));
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1324 "indra.y"
    {  
		(yyval.statement) = (yyvsp[(1) - (2)].statement);
	;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1328 "indra.y"
    { 
		(yyval.statement) = (yyvsp[(1) - (1)].statement);
	;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1332 "indra.y"
    {  
		(yyval.statement) = new LLScriptIf(gLine, gColumn, (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement));
		(yyvsp[(5) - (5)].statement)->mAllowDeclarations = FALSE;
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1338 "indra.y"
    {  
		(yyval.statement) = new LLScriptIfElse(gLine, gColumn, (yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement));
		(yyvsp[(5) - (7)].statement)->mAllowDeclarations = FALSE;
		(yyvsp[(7) - (7)].statement)->mAllowDeclarations = FALSE;
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1345 "indra.y"
    {  
		(yyval.statement) = new LLScriptFor(gLine, gColumn, (yyvsp[(3) - (9)].expression), (yyvsp[(5) - (9)].expression), (yyvsp[(7) - (9)].expression), (yyvsp[(9) - (9)].statement));
		(yyvsp[(9) - (9)].statement)->mAllowDeclarations = FALSE;
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1351 "indra.y"
    {  
		(yyval.statement) = new LLScriptDoWhile(gLine, gColumn, (yyvsp[(2) - (7)].statement), (yyvsp[(5) - (7)].expression));
		(yyvsp[(2) - (7)].statement)->mAllowDeclarations = FALSE;
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1357 "indra.y"
    {  
		(yyval.statement) = new LLScriptWhile(gLine, gColumn, (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement));
		(yyvsp[(5) - (5)].statement)->mAllowDeclarations = FALSE;
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1366 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (2)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.statement) = new LLScriptDeclaration(gLine, gColumn, (yyvsp[(1) - (2)].type), id, NULL);
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1373 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(2) - (4)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.statement) = new LLScriptDeclaration(gLine, gColumn, (yyvsp[(1) - (4)].type), id, (yyvsp[(4) - (4)].expression));
		gAllocationManager->addAllocation((yyval.statement));
	;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1383 "indra.y"
    {  
		(yyval.expression) = NULL;
	;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1387 "indra.y"
    {
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1394 "indra.y"
    {  
		(yyval.expression) = new LLScriptForExpressionList(gLine, gColumn, (yyvsp[(1) - (1)].expression), NULL);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1399 "indra.y"
    {
		(yyval.expression) = new LLScriptForExpressionList(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1407 "indra.y"
    {  
		(yyval.expression) = NULL;
	;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1411 "indra.y"
    {
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1418 "indra.y"
    {  
		(yyval.expression) = new LLScriptFuncExpressionList(gLine, gColumn, (yyvsp[(1) - (1)].expression), NULL);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1423 "indra.y"
    {
		(yyval.expression) = new LLScriptFuncExpressionList(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1431 "indra.y"
    {  
		(yyval.expression) = NULL;
	;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1435 "indra.y"
    {
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1442 "indra.y"
    {  
		(yyval.expression) = new LLScriptListExpressionList(gLine, gColumn, (yyvsp[(1) - (1)].expression), NULL);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1447 "indra.y"
    {
		(yyval.expression) = new LLScriptListExpressionList(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1455 "indra.y"
    {  
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1459 "indra.y"
    {  
		(yyval.expression) = new LLScriptAssignment(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1464 "indra.y"
    {  
		(yyval.expression) = new LLScriptAddAssignment(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1469 "indra.y"
    {  
		(yyval.expression) = new LLScriptSubAssignment(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1474 "indra.y"
    {  
		(yyval.expression) = new LLScriptMulAssignment(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1479 "indra.y"
    {  
		(yyval.expression) = new LLScriptDivAssignment(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1484 "indra.y"
    {  
		(yyval.expression) = new LLScriptModAssignment(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1489 "indra.y"
    {  
		(yyval.expression) = new LLScriptEquality(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1494 "indra.y"
    {  
		(yyval.expression) = new LLScriptNotEquals(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1499 "indra.y"
    {  
		(yyval.expression) = new LLScriptLessEquals(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1504 "indra.y"
    {  
		(yyval.expression) = new LLScriptGreaterEquals(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1509 "indra.y"
    {  
		(yyval.expression) = new LLScriptLessThan(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1514 "indra.y"
    {  
		(yyval.expression) = new LLScriptGreaterThan(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1519 "indra.y"
    {  
		(yyval.expression) = new LLScriptPlus(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1524 "indra.y"
    {  
		(yyval.expression) = new LLScriptMinus(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1529 "indra.y"
    {  
		(yyval.expression) = new LLScriptTimes(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1534 "indra.y"
    {  
		(yyval.expression) = new LLScriptDivide(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1539 "indra.y"
    {  
		(yyval.expression) = new LLScriptMod(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1544 "indra.y"
    {  
		(yyval.expression) = new LLScriptBitAnd(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1549 "indra.y"
    {  
		(yyval.expression) = new LLScriptBitOr(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1554 "indra.y"
    {  
		(yyval.expression) = new LLScriptBitXor(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1559 "indra.y"
    {  
		(yyval.expression) = new LLScriptBooleanAnd(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1564 "indra.y"
    {  
		(yyval.expression) = new LLScriptBooleanOr(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1569 "indra.y"
    {
		(yyval.expression) = new LLScriptShiftLeft(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1574 "indra.y"
    {
		(yyval.expression) = new LLScriptShiftRight(gLine, gColumn, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1582 "indra.y"
    {  
		(yyval.expression) = new LLScriptUnaryMinus(gLine, gColumn, (yyvsp[(2) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1587 "indra.y"
    {  
		(yyval.expression) = new LLScriptBooleanNot(gLine, gColumn, (yyvsp[(2) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1592 "indra.y"
    {  
		(yyval.expression) = new LLScriptBitNot(gLine, gColumn, (yyvsp[(2) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1597 "indra.y"
    {  
		(yyval.expression) = new LLScriptPreIncrement(gLine, gColumn, (yyvsp[(2) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1602 "indra.y"
    {  
		(yyval.expression) = new LLScriptPreDecrement(gLine, gColumn, (yyvsp[(2) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1607 "indra.y"
    {
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1611 "indra.y"
    {  
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1615 "indra.y"
    {  
		(yyval.expression) = new LLScriptParenthesis(gLine, gColumn, (yyvsp[(2) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1623 "indra.y"
    {
		(yyval.expression) = new LLScriptTypeCast(gLine, gColumn, (yyvsp[(2) - (4)].type), (yyvsp[(4) - (4)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1628 "indra.y"
    {
		LLScriptConstantExpression *temp =  new LLScriptConstantExpression(gLine, gColumn, (yyvsp[(4) - (4)].constant));
		gAllocationManager->addAllocation(temp);
		(yyval.expression) = new LLScriptTypeCast(gLine, gColumn, (yyvsp[(2) - (4)].type), temp);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1635 "indra.y"
    {
		(yyval.expression) = new LLScriptTypeCast(gLine, gColumn, (yyvsp[(2) - (4)].type), (yyvsp[(4) - (4)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1640 "indra.y"
    {
		(yyval.expression) = new LLScriptTypeCast(gLine, gColumn, (yyvsp[(2) - (6)].type), (yyvsp[(5) - (6)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1648 "indra.y"
    {  
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1652 "indra.y"
    {
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1656 "indra.y"
    {  
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1660 "indra.y"
    {  
		(yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1664 "indra.y"
    {  
		(yyval.expression) = new LLScriptPostIncrement(gLine, gColumn, (yyvsp[(1) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1669 "indra.y"
    {  
		(yyval.expression) = new LLScriptPostDecrement(gLine, gColumn, (yyvsp[(1) - (2)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1674 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (4)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.expression) = new LLScriptFunctionCall(gLine, gColumn, id, (yyvsp[(3) - (4)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1681 "indra.y"
    {  
		(yyval.expression) = new LLScriptPrint(gLine, gColumn, (yyvsp[(3) - (4)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1686 "indra.y"
    {  
		(yyval.expression) = new LLScriptConstantExpression(gLine, gColumn, (yyvsp[(1) - (1)].constant));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1694 "indra.y"
    {
		(yyval.expression) = new LLScriptVectorInitializer(gLine, gColumn, (yyvsp[(2) - (7)].expression), (yyvsp[(4) - (7)].expression), (yyvsp[(6) - (7)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1699 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptConstantExpression *sa0 = new LLScriptConstantExpression(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptConstantExpression *sa1 = new LLScriptConstantExpression(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptConstantExpression *sa2 = new LLScriptConstantExpression(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		(yyval.expression) = new LLScriptVectorInitializer(gLine, gColumn, sa0, sa1, sa2);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1716 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptConstantExpression *sa0 = new LLScriptConstantExpression(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptConstantExpression *sa1 = new LLScriptConstantExpression(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptConstantExpression *sa2 = new LLScriptConstantExpression(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		(yyval.expression) = new LLScriptVectorInitializer(gLine, gColumn, sa0, sa1, sa2);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1733 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, -1.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptConstantExpression *sa0 = new LLScriptConstantExpression(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, -1.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptConstantExpression *sa1 = new LLScriptConstantExpression(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptConstantExpression *sa2 = new LLScriptConstantExpression(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		(yyval.expression) = new LLScriptVectorInitializer(gLine, gColumn, sa0, sa1, sa2);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1753 "indra.y"
    {
		(yyval.expression) = new LLScriptQuaternionInitializer(gLine, gColumn, (yyvsp[(2) - (9)].expression), (yyvsp[(4) - (9)].expression), (yyvsp[(6) - (9)].expression), (yyvsp[(8) - (9)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1758 "indra.y"
    {
		LLScriptConstantFloat *cf0 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf0);
		LLScriptConstantExpression *sa0 = new LLScriptConstantExpression(gLine, gColumn, cf0);
		gAllocationManager->addAllocation(sa0);
		LLScriptConstantFloat *cf1 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf1);
		LLScriptConstantExpression *sa1 = new LLScriptConstantExpression(gLine, gColumn, cf1);
		gAllocationManager->addAllocation(sa1);
		LLScriptConstantFloat *cf2 = new LLScriptConstantFloat(gLine, gColumn, 0.f);
		gAllocationManager->addAllocation(cf2);
		LLScriptConstantExpression *sa2 = new LLScriptConstantExpression(gLine, gColumn, cf2);
		gAllocationManager->addAllocation(sa2);
		LLScriptConstantFloat *cf3 = new LLScriptConstantFloat(gLine, gColumn, 1.f);
		gAllocationManager->addAllocation(cf3);
		LLScriptConstantExpression *sa3 = new LLScriptConstantExpression(gLine, gColumn, cf3);
		gAllocationManager->addAllocation(sa3);
		(yyval.expression) = new LLScriptQuaternionInitializer(gLine, gColumn, sa0, sa1, sa2, sa3);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1782 "indra.y"
    {  
		(yyval.expression) = new LLScriptListInitializer(gLine, gColumn, (yyvsp[(2) - (3)].expression));
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1790 "indra.y"
    {  
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (1)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.expression) = new LLScriptLValue(gLine, gColumn, id, NULL);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1797 "indra.y"
    {
		LLScriptIdentifier	*id = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(1) - (3)].sval));	
		gAllocationManager->addAllocation(id);
		LLScriptIdentifier	*ac = new LLScriptIdentifier(gLine, gColumn, (yyvsp[(3) - (3)].sval));	
		gAllocationManager->addAllocation(id);
		(yyval.expression) = new LLScriptLValue(gLine, gColumn, id, ac);
		gAllocationManager->addAllocation((yyval.expression));
	;}
    break;



/* Line 1455 of yacc.c  */
#line 4469 "indra_generated.y.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1807 "indra.y"



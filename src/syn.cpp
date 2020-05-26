/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syn.y" /* yacc.c:337  */

    #include<cstdio>
    #include<cstdlib>
    #include<string>
    #include<memory>
    #include"ast.h"

    using std::shared_ptr;
    using std::make_shared;

    BlockNode* programBlock;

    extern int yylex();
    void yyerror(const char *s) {
        std::printf("Error: %s\n", s);
        std::exit(1);
    }

#line 89 "syn.cpp" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
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
   by #include "syn.hpp".  */
#ifndef YY_YY_SYN_HPP_INCLUDED
# define YY_YY_SYN_HPP_INCLUDED
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
    ID = 258,
    INTEGER = 259,
    CHARACTER = 260,
    REAL = 261,
    INT = 262,
    CHAR = 263,
    BOOL = 264,
    DOUBLE = 265,
    TRUE = 266,
    FALSE = 267,
    EQUAL = 268,
    GE = 269,
    GT = 270,
    LE = 271,
    LT = 272,
    NEQUAL = 273,
    ASSIGN = 274,
    LBRACE = 275,
    RBRACE = 276,
    LBRACKET = 277,
    RBRACKET = 278,
    LPAR = 279,
    RPAR = 280,
    COMMA = 281,
    SEMI = 282,
    DOT = 283,
    COLON = 284,
    WHILE = 285,
    DO = 286,
    LOOP = 287,
    FOREVER = 288,
    PLUS = 289,
    MINUS = 290,
    MUL = 291,
    DIV = 292,
    NOT = 293,
    AND = 294,
    OR = 295,
    IF = 296,
    ELIF = 297,
    ELSE = 298,
    RETURN = 299,
    STATIC = 300,
    BREAK = 301,
    THEN = 302,
    EXTERN = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "syn.y" /* yacc.c:352  */

    BlockNode* block;
    ExpressionNode* expr;
    StatementNode* stat;
    IdentifierNode* id;
    ArrayIndexNode* array_index;
    VariableDeclarationNode* var_decl;
    ExpressionList* expr_list;
    VariableList* var_list;
    TypeNode* type;
    std::string* string;
    int token;

#line 195 "syn.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYN_HPP_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

#define YYUNDEFTOK  2
#define YYMAXUTOK   303

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    63,    64,    69,    70,    73,    75,    76,
      79,    82,    85,    92,    93,    94,    95,    98,    99,   102,
     103,   109,   110,   113,   114,   117,   118,   124,   125,   126,
     127,   128,   129,   133,   134,   137,   138,   139,   148,   151,
     152,   156,   157,   158,   161,   164,   165,   168,   169,   172,
     173,   176,   177,   180,   180,   180,   180,   180,   180,   182,
     183,   186,   186,   188,   189,   192,   192,   194,   198,   199,
     202,   203,   206,   207,   208,   211,   212,   216,   217,   220,
     221,   222,   223,   224
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "CHARACTER", "REAL",
  "INT", "CHAR", "BOOL", "DOUBLE", "TRUE", "FALSE", "EQUAL", "GE", "GT",
  "LE", "LT", "NEQUAL", "ASSIGN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "LPAR", "RPAR", "COMMA", "SEMI", "DOT", "COLON", "WHILE",
  "DO", "LOOP", "FOREVER", "PLUS", "MINUS", "MUL", "DIV", "NOT", "AND",
  "OR", "IF", "ELIF", "ELSE", "RETURN", "STATIC", "BREAK", "THEN",
  "EXTERN", "$accept", "program", "declarationList", "declaration",
  "identifier", "statementList", "varDeclaration", "typeSpecifier",
  "codeBlock", "funDeclaration", "params", "paramList", "paramType",
  "statement", "expressionStmt", "selectionStmt", "iterationStmt",
  "returnStmt", "expression", "arrayElement", "simpleExpression",
  "andExpression", "unaryRelExpression", "relExpression", "relop",
  "sumExpression", "sumop", "mulExpression", "mulop", "unaryExpression",
  "factor", "mutable", "immutable", "call", "argList", "constant", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -47

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-47)))

#define YYTABLE_NINF -45

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,   -47,   -47,   -47,   -47,   -47,    29,    77,   -47,    24,
     -47,    47,   -47,   -47,   -47,    88,   -10,    47,    34,    26,
     -47,   156,    88,   -47,   156,    39,    42,    88,   -47,   -47,
     -47,   -47,   -47,   156,   156,    27,    54,    51,    41,    44,
     -47,   -47,    58,    -3,   -47,   -47,   -47,   -47,   -47,   -47,
      63,    -4,   -18,    78,   103,   -47,   -47,    79,   -47,   156,
     156,    20,    75,   156,   156,   156,   -47,   -47,   -47,   -47,
     -47,   -47,   -47,   -47,   114,   114,   -47,   -47,   114,    42,
     156,   -47,   -47,   -47,   -47,   156,   156,   173,   145,   -47,
      47,   -47,   -47,   -47,   -47,   -47,   -47,    89,   -47,   -47,
      98,   -47,   -47,    30,   -47,   -47,    44,   -47,    31,    -3,
     -47,   -47,    99,   -24,     7,   -47,   101,   -47,   -47,     8,
     -47,   110,   -47,   156,   -47,    42,    42,   -47,   -47,   -47,
      91,   -14,   -47,   -47
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    13,    15,    14,    16,     0,     2,     4,     0,
       5,     0,     6,     1,     3,    21,     0,     0,     0,    22,
      24,     0,    21,    10,     0,    25,     0,     0,    79,    80,
      81,    83,    82,     0,     0,    70,     0,     0,    43,    46,
      48,    50,    52,    60,    64,    67,    69,    68,    73,    74,
       0,    70,     0,     0,     0,    20,    23,     0,    49,     0,
       0,     0,     0,     0,     0,     0,    57,    56,    55,    53,
      54,    58,    61,    62,     0,     0,    65,    66,     0,     0,
       0,    11,    26,    17,    34,     0,     0,     0,     0,    31,
       0,    32,     8,    27,    28,    29,    30,     0,    72,    41,
       0,    76,    78,     0,    12,    42,    45,    47,    51,    59,
      63,    19,     0,     0,     0,    39,     0,    18,     9,     0,
      33,    71,    75,     0,    71,     0,     0,    40,    77,    38,
      35,     0,    36,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -47,   -47,   -47,   124,     4,   -47,   -46,     3,   -26,   -47,
     113,   -47,   105,    48,   -47,     6,   -47,   -47,   -20,   -47,
     -22,    76,   -29,   -47,   -47,    65,   -47,    67,   -47,    68,
     -47,   -47,   -47,   -47,   -47,   -47
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,    35,    88,    10,    17,    91,    12,
      18,    19,    20,    92,    93,    94,    95,    96,    97,    37,
      38,    39,    40,    41,    74,    42,    75,    43,    78,    44,
      45,    46,    47,    48,   103,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    36,    52,    11,     9,    58,    54,   125,    89,    81,
      11,     9,    21,    57,    22,    16,    64,    23,    80,    24,
      61,    25,    64,     1,    28,    29,    30,    86,    51,    13,
      21,    31,    32,    76,    77,    23,   107,    24,    51,    99,
     100,   102,    89,   105,    33,   101,    59,    64,    15,    60,
       1,    61,    27,   111,   126,   122,   123,    90,    34,    26,
     112,    53,    54,   113,   114,    72,    73,   116,    51,    51,
      63,    66,    67,    68,    69,    70,    71,    62,    51,    51,
       1,    64,    51,    65,     2,     3,     4,     5,    79,    51,
      51,    90,    72,    73,   119,     2,     3,     4,     5,   129,
     130,    82,   104,   128,    98,   132,     1,    28,    29,    30,
       2,     3,     4,     5,    31,    32,   120,     1,    28,    29,
      30,   121,   124,    54,    83,    31,    32,    33,   127,   -44,
      84,    14,    56,    85,   131,    50,   118,   133,    33,   108,
     106,    34,   109,     0,    86,     0,   110,    87,     1,    28,
      29,    30,     2,     3,     4,     5,    31,    32,     0,     1,
      28,    29,    30,     0,     0,    54,   117,    31,    32,    33,
       0,     0,    84,     0,     0,    85,     1,    28,    29,    30,
      33,     0,     0,    34,    31,    32,    86,     0,     0,    87,
       0,     0,     0,     0,    34,     0,     0,    33,     0,     0,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34
};

static const yytype_int16 yycheck[] =
{
      26,    21,    24,     0,     0,    34,    20,    31,    54,    27,
       7,     7,    22,    33,    24,    11,    40,    27,    22,    29,
      24,    17,    40,     3,     4,     5,     6,    41,    24,     0,
      22,    11,    12,    36,    37,    27,    65,    29,    34,    59,
      60,    61,    88,    63,    24,    25,    19,    40,    24,    22,
       3,    24,    26,    79,    47,    25,    26,    54,    38,    25,
      80,    22,    20,    85,    86,    34,    35,    87,    64,    65,
      19,    13,    14,    15,    16,    17,    18,    23,    74,    75,
       3,    40,    78,    39,     7,     8,     9,    10,    25,    85,
      86,    88,    34,    35,    90,     7,     8,     9,    10,   125,
     126,    23,    27,   123,    25,   131,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    27,     3,     4,     5,
       6,    23,    23,    20,    21,    11,    12,    24,    27,    19,
      27,     7,    27,    30,    43,    22,    88,   131,    24,    74,
      64,    38,    75,    -1,    41,    -1,    78,    44,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,     3,
       4,     5,     6,    -1,    -1,    20,    21,    11,    12,    24,
      -1,    -1,    27,    -1,    -1,    30,     3,     4,     5,     6,
      24,    -1,    -1,    38,    11,    12,    41,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,     8,     9,    10,    50,    51,    52,    53,
      55,    56,    58,     0,    52,    24,    53,    56,    59,    60,
      61,    22,    24,    27,    29,    53,    25,    26,     4,     5,
       6,    11,    12,    24,    38,    53,    67,    68,    69,    70,
      71,    72,    74,    76,    78,    79,    80,    81,    82,    84,
      59,    53,    69,    22,    20,    57,    61,    67,    71,    19,
      22,    24,    23,    19,    40,    39,    13,    14,    15,    16,
      17,    18,    34,    35,    73,    75,    36,    37,    77,    25,
      22,    27,    23,    21,    27,    30,    41,    44,    54,    55,
      56,    57,    62,    63,    64,    65,    66,    67,    25,    67,
      67,    25,    67,    83,    27,    67,    70,    71,    74,    76,
      78,    57,    67,    69,    69,    27,    67,    21,    62,    53,
      27,    23,    25,    26,    23,    31,    47,    27,    67,    57,
      57,    43,    57,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    64,    65,    66,
      66,    67,    67,    67,    68,    69,    69,    70,    70,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    79,    79,
      80,    80,    81,    81,    81,    82,    82,    83,    83,    84,
      84,    84,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       3,     5,     6,     1,     1,     1,     1,     2,     3,     6,
       5,     0,     1,     3,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     2,     1,     4,     6,     6,     4,     2,
       3,     3,     3,     1,     4,     3,     1,     3,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     1,     1,     4,     3,     3,     1,     1,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
| yyreduce -- do a reduction.  |
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
#line 61 "syn.y" /* yacc.c:1652  */
    { programBlock = (yyvsp[0].block); }
#line 1407 "syn.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 63 "syn.y" /* yacc.c:1652  */
    { (yyvsp[-1].block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));}
#line 1413 "syn.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 64 "syn.y" /* yacc.c:1652  */
    { (yyval.block) = new BlockNode(); 
                    (yyval.block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));
                }
#line 1421 "syn.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 69 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = (yyvsp[0].var_decl); }
#line 1427 "syn.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 70 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = (yyvsp[0].stat); }
#line 1433 "syn.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 73 "syn.y" /* yacc.c:1652  */
    { (yyval.id) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string);}
#line 1439 "syn.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 75 "syn.y" /* yacc.c:1652  */
    { (yyval.block) = new BlockNode(); (yyval.block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));}
#line 1445 "syn.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 76 "syn.y" /* yacc.c:1652  */
    {  (yyvsp[-1].block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat))); }
#line 1451 "syn.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 79 "syn.y" /* yacc.c:1652  */
    { 
                    (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-2].type), (yyvsp[-1].id)); 
                    }
#line 1459 "syn.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 82 "syn.y" /* yacc.c:1652  */
    {
                    (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-4].type), (yyvsp[-3].id), (yyvsp[-1].expr));
                }
#line 1467 "syn.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 85 "syn.y" /* yacc.c:1652  */
    {
                (yyvsp[-5].type)->isArray = true;
                (yyvsp[-5].type)->arraySize = shared_ptr<ExpressionNode>((yyvsp[-2].expr));
                (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-5].type), (yyvsp[-4].id));
            }
#line 1477 "syn.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 92 "syn.y" /* yacc.c:1652  */
    { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1483 "syn.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 93 "syn.y" /* yacc.c:1652  */
    { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1489 "syn.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 94 "syn.y" /* yacc.c:1652  */
    { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1495 "syn.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 95 "syn.y" /* yacc.c:1652  */
    { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1501 "syn.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 98 "syn.y" /* yacc.c:1652  */
    { (yyval.block) = new BlockNode();}
#line 1507 "syn.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 99 "syn.y" /* yacc.c:1652  */
    { (yyval.block) = (yyvsp[-1].block); }
#line 1513 "syn.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 102 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new FunctionDeclarationNode((yyvsp[-5].type), (yyvsp[-4].id), (yyvsp[-2].var_list), (yyvsp[0].block)); }
#line 1519 "syn.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 103 "syn.y" /* yacc.c:1652  */
    {
    		TypeNode* type = new TypeNode("void");
    		(yyval.stat) = new FunctionDeclarationNode(type, (yyvsp[-4].id), (yyvsp[-2].var_list), (yyvsp[0].block));
    	}
#line 1528 "syn.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 109 "syn.y" /* yacc.c:1652  */
    { (yyval.var_list) = new VariableList(); }
#line 1534 "syn.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 110 "syn.y" /* yacc.c:1652  */
    { (yyval.var_list) = (yyvsp[0].var_list); }
#line 1540 "syn.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 113 "syn.y" /* yacc.c:1652  */
    { (yyvsp[-2].var_list)->emplace_back(shared_ptr<VariableDeclarationNode>((yyvsp[0].var_decl))); }
#line 1546 "syn.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 114 "syn.y" /* yacc.c:1652  */
    { (yyval.var_list) = new VariableList(); (yyval.var_list)->emplace_back(shared_ptr<VariableDeclarationNode>((yyvsp[0].var_decl))); }
#line 1552 "syn.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 117 "syn.y" /* yacc.c:1652  */
    { (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-1].type), (yyvsp[0].id)); }
#line 1558 "syn.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 118 "syn.y" /* yacc.c:1652  */
    {
            (yyvsp[-3].type)->isArray = true;
            (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-3].type), (yyvsp[-2].id));
        }
#line 1567 "syn.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 133 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new ExpressionStatementNode((yyvsp[-1].expr)); }
#line 1573 "syn.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 134 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = nullptr; }
#line 1579 "syn.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 137 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new IfStatementNode((yyvsp[-2].expr), (yyvsp[0].block), nullptr);}
#line 1585 "syn.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 138 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new IfStatementNode((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[0].block)); }
#line 1591 "syn.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 139 "syn.y" /* yacc.c:1652  */
    { 
                            BlockNode* elseBlock = new BlockNode();
                            elseBlock->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));
                            (yyval.stat) = new IfStatementNode((yyvsp[-4].expr), (yyvsp[-2].block), elseBlock);
                    }
#line 1601 "syn.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 148 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new WhileStatementNode((yyvsp[-2].expr), (yyvsp[0].block)); }
#line 1607 "syn.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 151 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new ReturnStatementNode(nullptr);}
#line 1613 "syn.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 152 "syn.y" /* yacc.c:1652  */
    { (yyval.stat) = new ReturnStatementNode((yyvsp[-1].expr)); }
#line 1619 "syn.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 156 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new AssignmentNode((yyvsp[-2].id), (yyvsp[0].expr)); }
#line 1625 "syn.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 157 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new ArrayIndexAssignmentNode((yyvsp[-2].array_index), (yyvsp[0].expr)); }
#line 1631 "syn.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 158 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1637 "syn.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 161 "syn.y" /* yacc.c:1652  */
    { (yyval.array_index) = new ArrayIndexNode((yyvsp[-3].id), (yyvsp[-1].expr)); }
#line 1643 "syn.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 164 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1649 "syn.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 165 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1655 "syn.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 168 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1661 "syn.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 169 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1667 "syn.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 172 "syn.y" /* yacc.c:1652  */
    { /*Not implement*/ (yyval.expr) = nullptr; }
#line 1673 "syn.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 173 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1679 "syn.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 176 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1685 "syn.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 177 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1691 "syn.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 182 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1697 "syn.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 183 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1703 "syn.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 188 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1709 "syn.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 189 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1715 "syn.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 194 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1721 "syn.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 198 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1727 "syn.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 199 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1733 "syn.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 202 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].id); }
#line 1739 "syn.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 203 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new ArrayIndexNode((yyvsp[-3].id), (yyvsp[-1].expr)); }
#line 1745 "syn.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 206 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1751 "syn.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 207 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1757 "syn.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 208 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1763 "syn.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 211 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new FunctionCallNode((yyvsp[-3].id), (yyvsp[-1].expr_list)); }
#line 1769 "syn.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 212 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new FunctionCallNode((yyvsp[-2].id)); }
#line 1775 "syn.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 216 "syn.y" /* yacc.c:1652  */
    { (yyvsp[-2].expr_list)->emplace_back(shared_ptr<ExpressionNode>((yyvsp[0].expr))); }
#line 1781 "syn.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 217 "syn.y" /* yacc.c:1652  */
    { (yyval.expr_list) = new ExpressionList(); (yyval.expr_list)->emplace_back(shared_ptr<ExpressionNode>((yyvsp[0].expr))); }
#line 1787 "syn.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 220 "syn.y" /* yacc.c:1652  */
    { int64_t value; sscanf((yyvsp[0].string)->c_str(), "%ld", &value); (yyval.expr) = new IntegerNode(value); delete (yyvsp[0].string); }
#line 1793 "syn.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 221 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new CharNode((*(yyvsp[0].string))[1]); delete (yyvsp[0].string); }
#line 1799 "syn.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 222 "syn.y" /* yacc.c:1652  */
    { double value; sscanf((yyvsp[0].string)->c_str(), "%lf", &value); (yyval.expr) = new RealNode(value); delete (yyvsp[0].string); }
#line 1805 "syn.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 223 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BoolNode(false); }
#line 1811 "syn.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 224 "syn.y" /* yacc.c:1652  */
    { (yyval.expr) = new BoolNode(true); }
#line 1817 "syn.cpp" /* yacc.c:1652  */
    break;


#line 1821 "syn.cpp" /* yacc.c:1652  */
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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 226 "syn.y" /* yacc.c:1918  */


extern int dbg_on;
extern void compile_and_run(BlockNode* b);

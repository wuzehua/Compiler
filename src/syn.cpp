/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syn.y"

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

#line 89 "syn.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    MOD = 296,
    IF = 297,
    ELIF = 298,
    ELSE = 299,
    RETURN = 300,
    STATIC = 301,
    BREAK = 302,
    THEN = 303,
    EXTERN = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "syn.y"

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

#line 205 "syn.cpp"

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

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    63,    64,    69,    70,    73,    75,    76,
      79,    82,    85,    95,    96,    97,    98,   101,   102,   105,
     106,   110,   113,   119,   120,   123,   124,   127,   128,   134,
     135,   136,   137,   138,   139,   143,   144,   147,   148,   149,
     158,   161,   162,   166,   167,   168,   171,   174,   175,   178,
     179,   182,   183,   186,   187,   190,   190,   190,   190,   190,
     190,   192,   193,   196,   196,   198,   199,   202,   202,   202,
     204,   208,   209,   212,   213,   216,   217,   218,   221,   222,
     228,   229,   232,   233,   234,   235,   236
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
  "OR", "MOD", "IF", "ELIF", "ELSE", "RETURN", "STATIC", "BREAK", "THEN",
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
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-47)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,   -56,   -56,   -56,   -56,   -56,   100,    22,    11,   -56,
     -13,   -56,    33,   -56,    13,    33,   -56,   -56,   158,   113,
     158,    15,    33,    18,    35,   -56,    44,   158,   -56,    52,
      42,   158,    50,    63,   158,    71,    62,   -56,   -56,   -56,
     -56,   -56,    52,    52,    -7,     7,    83,   -56,   -56,    36,
     112,   -56,   -56,   -56,   -56,   -56,   -56,    74,    77,   104,
     109,   -56,   -56,   101,    63,   119,   121,   115,   105,   -56,
      52,    21,   -56,    52,    52,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,   120,   120,   -56,   -56,   -56,   120,   -56,
     123,   -56,   -56,   -56,    52,    52,   180,   152,   -56,    33,
     -56,   -56,   -56,   -56,   -56,   -56,   125,   -56,   -56,    52,
      52,   -56,    52,   146,   -56,   -56,    72,    83,   -56,    43,
     112,   -56,   -56,    -2,    25,   -56,   143,   -56,   -56,    64,
     -56,   -56,   148,   -56,   -56,   -56,    52,    63,    63,   -56,
     155,   -56,   -56,   131,   -14,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     7,    13,    15,    14,    16,     0,     0,     2,     4,
       0,     5,     0,     6,     0,     0,     1,     3,    23,     0,
      23,     0,     0,     0,    24,    26,     0,    23,    10,     0,
       0,    23,    27,     0,     0,     0,     0,    82,    83,    84,
      86,    85,     0,     0,    73,     0,    48,    50,    52,    54,
      62,    66,    70,    72,    71,    76,    77,     0,     0,     0,
       0,    20,    25,     0,     0,    73,     0,     0,    45,    51,
       0,     0,    11,     0,     0,    59,    58,    57,    55,    56,
      60,    63,    64,     0,     0,    67,    68,    69,     0,    22,
       0,    28,    17,    36,     0,     0,     0,     0,    33,     0,
      34,     8,    29,    30,    31,    32,     0,    12,    19,     0,
       0,    75,     0,     0,    79,    81,     0,    47,    49,    53,
      61,    65,    21,     0,     0,    41,     0,    18,     9,     0,
      35,    43,     0,    44,    74,    78,     0,     0,     0,    42,
      74,    80,    40,    37,     0,    38,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -56,   -56,   -56,   169,     1,   -56,   -55,     2,   -33,   -56,
      61,   -56,   144,    84,   -56,    45,   -56,   -56,   -30,   -56,
     -26,   107,   -39,   -56,   -56,   110,   -56,   103,   -56,   108,
     -56,   -56,   -56,   -56,   -56,   -56
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    65,    97,    11,    22,   100,    13,
      23,    24,    25,   101,   102,   103,   104,   105,   106,    67,
      68,    46,    47,    48,    83,    49,    84,    50,    88,    51,
      52,    53,    54,    55,   116,    56
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    10,    12,    45,    69,    98,    60,    14,    15,    10,
      12,    18,    66,    19,     1,    70,    21,    71,     2,     3,
       4,     5,    16,    32,     1,    37,    38,    39,    95,   137,
      44,   108,    40,    41,    72,   118,     1,    20,    73,    31,
     113,   115,    98,    33,    44,    42,   114,    73,    35,    75,
      76,    77,    78,    79,    80,     1,    37,    38,    39,    43,
       6,    34,    99,    40,    41,    73,   126,    57,   123,   124,
      81,    82,    59,   138,    44,    44,    42,    81,    82,   131,
     132,    30,   133,    60,    44,    44,    26,    64,    36,    44,
      43,    28,    58,    29,    63,    44,    44,   135,   136,    99,
     129,    89,    90,     1,   142,   143,   141,     2,     3,     4,
       5,   145,     1,    37,    38,    39,     2,     3,     4,     5,
      40,    41,    74,     1,    37,    38,    39,    91,   107,    60,
      92,    40,    41,    42,   112,    26,    93,    27,   109,    94,
      28,   110,    29,    71,    42,    73,   111,    43,    85,    86,
     122,    95,   130,    87,    96,     1,    37,    38,    39,     2,
       3,     4,     5,    40,    41,     2,     3,     4,     5,   134,
     139,   140,    60,   127,   -46,   144,    42,    17,    62,    93,
     117,   128,    94,     1,    37,    38,    39,   120,     0,   146,
      43,    40,    41,   119,    95,     0,   121,    96,     0,     0,
       0,     0,     0,     0,    42,     0,     0,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43
};

static const yytype_int16 yycheck[] =
{
      33,     0,     0,    29,    43,    60,    20,     6,     6,     8,
       8,    24,    42,    12,     3,    22,    15,    24,     7,     8,
       9,    10,     0,    22,     3,     4,     5,     6,    42,    31,
      29,    64,    11,    12,    27,    74,     3,    24,    40,    24,
      70,    71,    97,    25,    43,    24,    25,    40,     4,    13,
      14,    15,    16,    17,    18,     3,     4,     5,     6,    38,
      49,    26,    60,    11,    12,    40,    96,    25,    94,    95,
      34,    35,    22,    48,    73,    74,    24,    34,    35,   109,
     110,    20,   112,    20,    83,    84,    22,    25,    27,    88,
      38,    27,    31,    29,    23,    94,    95,    25,    26,    97,
      99,    27,    25,     3,   137,   138,   136,     7,     8,     9,
      10,   144,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    39,     3,     4,     5,     6,    23,    27,    20,
      21,    11,    12,    24,    19,    22,    27,    24,    19,    30,
      27,    22,    29,    24,    24,    40,    25,    38,    36,    37,
      27,    42,    27,    41,    45,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     7,     8,     9,    10,    23,
      27,    23,    20,    21,    19,    44,    24,     8,    34,    27,
      73,    97,    30,     3,     4,     5,     6,    84,    -1,   144,
      38,    11,    12,    83,    42,    -1,    88,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,     8,     9,    10,    49,    51,    52,    53,
      54,    56,    57,    59,    54,    57,     0,    53,    24,    54,
      24,    54,    57,    60,    61,    62,    22,    24,    27,    29,
      60,    24,    54,    25,    26,     4,    60,     4,     5,     6,
      11,    12,    24,    38,    54,    70,    71,    72,    73,    75,
      77,    79,    80,    81,    82,    83,    85,    25,    60,    22,
      20,    58,    62,    23,    25,    54,    68,    69,    70,    72,
      22,    24,    27,    40,    39,    13,    14,    15,    16,    17,
      18,    34,    35,    74,    76,    36,    37,    41,    78,    27,
      25,    23,    21,    27,    30,    42,    45,    55,    56,    57,
      58,    63,    64,    65,    66,    67,    68,    27,    58,    19,
      22,    25,    19,    68,    25,    68,    84,    71,    72,    75,
      77,    79,    27,    70,    70,    27,    68,    21,    63,    54,
      27,    68,    68,    68,    23,    25,    26,    31,    48,    27,
      23,    68,    58,    58,    44,    58,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    55,    55,
      56,    56,    56,    57,    57,    57,    57,    58,    58,    59,
      59,    59,    59,    60,    60,    61,    61,    62,    62,    63,
      63,    63,    63,    63,    63,    64,    64,    65,    65,    65,
      66,    67,    67,    68,    68,    68,    69,    70,    70,    71,
      71,    72,    72,    73,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    78,
      79,    80,    80,    81,    81,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    85,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       3,     5,     6,     1,     1,     1,     1,     2,     3,     6,
       5,     7,     6,     0,     1,     3,     1,     2,     4,     1,
       1,     1,     1,     1,     1,     2,     1,     4,     6,     6,
       4,     2,     3,     3,     3,     1,     4,     3,     1,     3,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     1,     1,     4,     3,
       3,     1,     1,     1,     1,     1,     1
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
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
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
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

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
#line 61 "syn.y"
                          { programBlock = (yyvsp[0].block); }
#line 1502 "syn.cpp"
    break;

  case 3:
#line 63 "syn.y"
                                              { (yyvsp[-1].block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));}
#line 1508 "syn.cpp"
    break;

  case 4:
#line 64 "syn.y"
                  { (yyval.block) = new BlockNode(); 
                    (yyval.block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));
                }
#line 1516 "syn.cpp"
    break;

  case 5:
#line 69 "syn.y"
                            { (yyval.stat) = (yyvsp[0].var_decl); }
#line 1522 "syn.cpp"
    break;

  case 6:
#line 70 "syn.y"
                     { (yyval.stat) = (yyvsp[0].stat); }
#line 1528 "syn.cpp"
    break;

  case 7:
#line 73 "syn.y"
               { (yyval.id) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string);}
#line 1534 "syn.cpp"
    break;

  case 8:
#line 75 "syn.y"
                          { (yyval.block) = new BlockNode(); (yyval.block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));}
#line 1540 "syn.cpp"
    break;

  case 9:
#line 76 "syn.y"
                              {  (yyvsp[-1].block)->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat))); }
#line 1546 "syn.cpp"
    break;

  case 10:
#line 79 "syn.y"
                                              { 
                    (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-2].type), (yyvsp[-1].id)); 
                    }
#line 1554 "syn.cpp"
    break;

  case 11:
#line 82 "syn.y"
                                                                    {
                    (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-4].type), (yyvsp[-3].id), (yyvsp[-1].expr));
                }
#line 1562 "syn.cpp"
    break;

  case 12:
#line 85 "syn.y"
                                                                        {
                (yyvsp[-5].type)->isArray = true;
                int64_t value;
                sscanf((yyvsp[-2].string)->c_str(), "%ld", &value);
                delete (yyvsp[-2].string);
                (yyvsp[-5].type)->arraySize = make_shared<IntegerNode>(value);
                (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-5].type), (yyvsp[-4].id));
            }
#line 1575 "syn.cpp"
    break;

  case 13:
#line 95 "syn.y"
                   { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1581 "syn.cpp"
    break;

  case 14:
#line 96 "syn.y"
                   { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1587 "syn.cpp"
    break;

  case 15:
#line 97 "syn.y"
                   { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1593 "syn.cpp"
    break;

  case 16:
#line 98 "syn.y"
                     { (yyval.type) = new TypeNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1599 "syn.cpp"
    break;

  case 17:
#line 101 "syn.y"
                         { (yyval.block) = new BlockNode();}
#line 1605 "syn.cpp"
    break;

  case 18:
#line 102 "syn.y"
                                       { (yyval.block) = (yyvsp[-1].block); }
#line 1611 "syn.cpp"
    break;

  case 19:
#line 105 "syn.y"
                                                                    { (yyval.stat) = new FunctionDeclarationNode((yyvsp[-5].type), (yyvsp[-4].id), (yyvsp[-2].var_list), (yyvsp[0].block)); }
#line 1617 "syn.cpp"
    break;

  case 20:
#line 106 "syn.y"
                                            {
    		TypeNode* type = new TypeNode("void");
    		(yyval.stat) = new FunctionDeclarationNode(type, (yyvsp[-4].id), (yyvsp[-2].var_list), (yyvsp[0].block));
    	}
#line 1626 "syn.cpp"
    break;

  case 21:
#line 110 "syn.y"
                                                            {
    		(yyval.stat) = new FunctionDeclarationNode((yyvsp[-5].type), (yyvsp[-4].id), (yyvsp[-2].var_list), nullptr, true);
    	}
#line 1634 "syn.cpp"
    break;

  case 22:
#line 113 "syn.y"
                                             {
    		TypeNode* type = new TypeNode("void");
    		(yyval.stat) = new FunctionDeclarationNode(type, (yyvsp[-4].id), (yyvsp[-2].var_list), nullptr, true);
   	}
#line 1643 "syn.cpp"
    break;

  case 23:
#line 119 "syn.y"
         { (yyval.var_list) = new VariableList(); }
#line 1649 "syn.cpp"
    break;

  case 24:
#line 120 "syn.y"
                { (yyval.var_list) = (yyvsp[0].var_list); }
#line 1655 "syn.cpp"
    break;

  case 25:
#line 123 "syn.y"
                                     { (yyvsp[-2].var_list)->emplace_back(shared_ptr<VariableDeclarationNode>((yyvsp[0].var_decl))); }
#line 1661 "syn.cpp"
    break;

  case 26:
#line 124 "syn.y"
                { (yyval.var_list) = new VariableList(); (yyval.var_list)->emplace_back(shared_ptr<VariableDeclarationNode>((yyvsp[0].var_decl))); }
#line 1667 "syn.cpp"
    break;

  case 27:
#line 127 "syn.y"
                                    { (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-1].type), (yyvsp[0].id)); }
#line 1673 "syn.cpp"
    break;

  case 28:
#line 128 "syn.y"
                                                   {
            (yyvsp[-3].type)->isArray = true;
            (yyval.var_decl) = new VariableDeclarationNode((yyvsp[-3].type), (yyvsp[-2].id));
        }
#line 1682 "syn.cpp"
    break;

  case 35:
#line 143 "syn.y"
                                { (yyval.stat) = new ExpressionStatementNode((yyvsp[-1].expr)); }
#line 1688 "syn.cpp"
    break;

  case 36:
#line 144 "syn.y"
           { (yyval.stat) = nullptr; }
#line 1694 "syn.cpp"
    break;

  case 37:
#line 147 "syn.y"
                                                  { (yyval.stat) = new IfStatementNode((yyvsp[-2].expr), (yyvsp[0].block), nullptr);}
#line 1700 "syn.cpp"
    break;

  case 38:
#line 148 "syn.y"
                                                        { (yyval.stat) = new IfStatementNode((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[0].block)); }
#line 1706 "syn.cpp"
    break;

  case 39:
#line 149 "syn.y"
                                                            { 
                            BlockNode* elseBlock = new BlockNode();
                            elseBlock->statements.emplace_back(shared_ptr<StatementNode>((yyvsp[0].stat)));
                            (yyval.stat) = new IfStatementNode((yyvsp[-4].expr), (yyvsp[-2].block), elseBlock);
                    }
#line 1716 "syn.cpp"
    break;

  case 40:
#line 158 "syn.y"
                                                   { (yyval.stat) = new WhileStatementNode((yyvsp[-2].expr), (yyvsp[0].block)); }
#line 1722 "syn.cpp"
    break;

  case 41:
#line 161 "syn.y"
                        { (yyval.stat) = new ReturnStatementNode(nullptr);}
#line 1728 "syn.cpp"
    break;

  case 42:
#line 162 "syn.y"
                             { (yyval.stat) = new ReturnStatementNode((yyvsp[-1].expr)); }
#line 1734 "syn.cpp"
    break;

  case 43:
#line 166 "syn.y"
                                         { (yyval.expr) = new AssignmentNode((yyvsp[-2].id), (yyvsp[0].expr)); }
#line 1740 "syn.cpp"
    break;

  case 44:
#line 167 "syn.y"
                                     { (yyval.expr) = new ArrayIndexAssignmentNode((yyvsp[-2].array_index), (yyvsp[0].expr)); }
#line 1746 "syn.cpp"
    break;

  case 45:
#line 168 "syn.y"
                       { (yyval.expr) = (yyvsp[0].expr); }
#line 1752 "syn.cpp"
    break;

  case 46:
#line 171 "syn.y"
                                                      { (yyval.array_index) = new ArrayIndexNode((yyvsp[-3].id), (yyvsp[-1].expr)); }
#line 1758 "syn.cpp"
    break;

  case 47:
#line 174 "syn.y"
                                                    { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1764 "syn.cpp"
    break;

  case 48:
#line 175 "syn.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1770 "syn.cpp"
    break;

  case 49:
#line 178 "syn.y"
                                                     { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1776 "syn.cpp"
    break;

  case 50:
#line 179 "syn.y"
                         { (yyval.expr) = (yyvsp[0].expr); }
#line 1782 "syn.cpp"
    break;

  case 51:
#line 182 "syn.y"
                                           { /*Not implement*/ (yyval.expr) = nullptr; }
#line 1788 "syn.cpp"
    break;

  case 52:
#line 183 "syn.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1794 "syn.cpp"
    break;

  case 53:
#line 186 "syn.y"
                                                 { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1800 "syn.cpp"
    break;

  case 54:
#line 187 "syn.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1806 "syn.cpp"
    break;

  case 61:
#line 192 "syn.y"
                                                 { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1812 "syn.cpp"
    break;

  case 62:
#line 193 "syn.y"
                    { (yyval.expr) = (yyvsp[0].expr); }
#line 1818 "syn.cpp"
    break;

  case 65:
#line 198 "syn.y"
                                                   { (yyval.expr) = new BinaryOperatorNode((yyvsp[-2].expr), (yyvsp[-1].token), (yyvsp[0].expr));}
#line 1824 "syn.cpp"
    break;

  case 66:
#line 199 "syn.y"
                      { (yyval.expr) = (yyvsp[0].expr); }
#line 1830 "syn.cpp"
    break;

  case 70:
#line 204 "syn.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1836 "syn.cpp"
    break;

  case 71:
#line 208 "syn.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1842 "syn.cpp"
    break;

  case 72:
#line 209 "syn.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 1848 "syn.cpp"
    break;

  case 73:
#line 212 "syn.y"
                    { (yyval.expr) = (yyvsp[0].id); }
#line 1854 "syn.cpp"
    break;

  case 74:
#line 213 "syn.y"
                                              { (yyval.expr) = new ArrayIndexNode((yyvsp[-3].id), (yyvsp[-1].expr)); }
#line 1860 "syn.cpp"
    break;

  case 75:
#line 216 "syn.y"
                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1866 "syn.cpp"
    break;

  case 76:
#line 217 "syn.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1872 "syn.cpp"
    break;

  case 77:
#line 218 "syn.y"
               { (yyval.expr) = (yyvsp[0].expr); }
#line 1878 "syn.cpp"
    break;

  case 78:
#line 221 "syn.y"
                                   { (yyval.expr) = new FunctionCallNode((yyvsp[-3].id), (yyvsp[-1].expr_list)); }
#line 1884 "syn.cpp"
    break;

  case 79:
#line 222 "syn.y"
                           {
        ExpressionList* args = new ExpressionList();
         (yyval.expr) = new FunctionCallNode((yyvsp[-2].id), args); }
#line 1892 "syn.cpp"
    break;

  case 80:
#line 228 "syn.y"
                                  { (yyvsp[-2].expr_list)->emplace_back(shared_ptr<ExpressionNode>((yyvsp[0].expr))); }
#line 1898 "syn.cpp"
    break;

  case 81:
#line 229 "syn.y"
                 { (yyval.expr_list) = new ExpressionList(); (yyval.expr_list)->emplace_back(shared_ptr<ExpressionNode>((yyvsp[0].expr))); }
#line 1904 "syn.cpp"
    break;

  case 82:
#line 232 "syn.y"
                  { int64_t value; sscanf((yyvsp[0].string)->c_str(), "%ld", &value); (yyval.expr) = new IntegerNode(value); delete (yyvsp[0].string); }
#line 1910 "syn.cpp"
    break;

  case 83:
#line 233 "syn.y"
                { (yyval.expr) = new CharNode((*(yyvsp[0].string))[1]); delete (yyvsp[0].string); }
#line 1916 "syn.cpp"
    break;

  case 84:
#line 234 "syn.y"
           { double value; sscanf((yyvsp[0].string)->c_str(), "%lf", &value); (yyval.expr) = new RealNode(value); delete (yyvsp[0].string); }
#line 1922 "syn.cpp"
    break;

  case 85:
#line 235 "syn.y"
            { (yyval.expr) = new BoolNode(false); }
#line 1928 "syn.cpp"
    break;

  case 86:
#line 236 "syn.y"
           { (yyval.expr) = new BoolNode(true); }
#line 1934 "syn.cpp"
    break;


#line 1938 "syn.cpp"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
                  yystos[+*yyssp], yyvsp);
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
#line 238 "syn.y"


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
#line 1 "misc/parser.y"

  #include <stdio.h>
  #include <iostream>
  #include <string.h>
  #include <vector>
  #include "../inc/assembler.h"

  using namespace std;

  extern void yyrestart(FILE *input_file);

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

  void yyerror(const char *s);

  char error_str[32];

  int asm_line = 1;

  vector<string> sym_name_list;
  int gpr_1, gpr_2;
  int csr;
  int pc_relative_disp;
  bool is_first_pass_aborted;

  uint8_t instruction[4];
  

#line 101 "src/parser.cpp"

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
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_INC_PARSER_H_INCLUDED
# define YY_YY_INC_PARSER_H_INCLUDED
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
    GLOBAL = 258,
    EXTERN = 259,
    SECTION = 260,
    WORD = 261,
    SKIP = 262,
    END = 263,
    HALT = 264,
    INT = 265,
    IRET = 266,
    CALL = 267,
    RET = 268,
    JMP = 269,
    BEQ = 270,
    BNE = 271,
    BGT = 272,
    PUSH = 273,
    POP = 274,
    XCHG = 275,
    ADD = 276,
    SUB = 277,
    MUL = 278,
    DIV = 279,
    NOT = 280,
    AND = 281,
    OR = 282,
    XOR = 283,
    SHL = 284,
    SHR = 285,
    LD = 286,
    ST = 287,
    CSRRD = 288,
    CSRWR = 289,
    REG = 290,
    STATUS = 291,
    HANDLER = 292,
    CAUSE = 293,
    DOLLAR = 294,
    LEFTBRACKET = 295,
    RIGHTBRACKET = 296,
    PLUS = 297,
    COMMA = 298,
    COLON = 299,
    EOL = 300,
    NUMBER = 301,
    IDENTIFIER = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "misc/parser.y"

  unsigned int num;
  char* ident;

#line 206 "src/parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INC_PARSER_H_INCLUDED  */



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
#define YYFINAL  92
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   225

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

#define YYUNDEFTOK  2
#define YYMAXUTOK   302


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
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    56,    56,    57,    61,    62,    63,    64,    68,    76,
      85,    86,    90,   100,   107,   114,   117,   124,   134,   135,
     136,   137,   138,   139,   149,   154,   164,   176,   179,   182,
     188,   197,   207,   222,   234,   243,   257,   266,   275,   287,
     296,   305,   314,   323,   332,   341,   350,   359,   368,   380,
     387,   393,   402,   411,   425,   432,   442,   456,   469,   487,
     505,   514,   523,   554,   566,   578,   587,   606,   610,   618,
     622,   629,   639,   649,   659
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GLOBAL", "EXTERN", "SECTION", "WORD",
  "SKIP", "END", "HALT", "INT", "IRET", "CALL", "RET", "JMP", "BEQ", "BNE",
  "BGT", "PUSH", "POP", "XCHG", "ADD", "SUB", "MUL", "DIV", "NOT", "AND",
  "OR", "XOR", "SHL", "SHR", "LD", "ST", "CSRRD", "CSRWR", "REG", "STATUS",
  "HANDLER", "CAUSE", "DOLLAR", "LEFTBRACKET", "RIGHTBRACKET", "PLUS",
  "COMMA", "COLON", "EOL", "NUMBER", "IDENTIFIER", "$accept", "program",
  "line", "end_of_line", "label", "operation", "directive", "instruction",
  "csr_reg", "no_op_inst", "jmp_inst", "one_reg_inst", "two_reg_inst",
  "one_reg", "two_regs", "two_reg_jmp_inst", "adress_operand",
  "ld_data_operand", "st_data_operand", "literal", "symbol", "symbol_list",
  "symbol_literal_list", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     135,   -32,   -32,   -32,   -36,   -28,   -37,   -37,   -37,   -37,
     -36,   -37,   -36,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,   -23,
      -9,    30,    -9,   -37,   -13,    29,   -37,   -37,   180,    19,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,    26,
      26,   -37,   -37,   -37,   -37,    28,   -37,   -37,   -37,   -37,
     -37,   -37,    36,    43,    52,    53,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -36,
      -9,    54,   -37,    58,    64,    65,   -37,   -37,   -37,    66,
      68,   -37,   -37,   -37,   -37,    19,   -37,   -32,   -36,    71,
     -36,   -36,   -36,    69,    70,    31,    79,    80,    81,   -19,
      -9,    30,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
      82,    83,    77,   -28,   -37,   -37,   -37,    86,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,    87,    84,    51,   -37,    85,
     -37,   -28,    88,    89,   -37,   -37
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    17,    30,    31,    32,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,     2,     7,     0,     0,
      10,    11,    18,    19,    20,    21,    22,    68,    69,    12,
      13,    14,    67,    72,    71,    15,    16,    34,    54,    55,
      35,    49,     0,     0,     0,     0,    36,    37,    39,    40,
      41,    42,    43,    38,    44,    45,    46,    47,    48,     0,
       0,     0,    23,     0,     0,     0,    27,    28,    29,     0,
       0,     9,     1,     3,     5,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,    70,    74,    73,    50,    51,    52,    53,
       0,     0,     0,     0,    60,    58,    59,     0,    24,    63,
      64,    25,    26,    56,    57,     0,     0,     0,    61,     0,
      65,     0,     0,     0,    62,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,    91,   -30,   -37,    93,   -37,   -37,    13,   -37,
     -37,   -37,   -37,   -10,    63,   -37,     2,   -37,   -37,    -4,
       1,   125,   -37
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    35,    36,    37,    38,    39,    40,    41,    89,    42,
      43,    44,    45,    62,    63,    46,    57,    82,   128,    58,
      59,    49,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    56,    48,    48,    51,    54,    66,    67,    94,    96,
      52,    47,    61,    73,    60,    47,    79,    80,    52,    81,
      85,   127,    90,    52,    47,    83,    61,    52,    47,    92,
      84,    91,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,   112,    86,    87,    88,    97,
     105,    98,   122,   123,    33,   103,    34,    64,    65,    99,
     104,    68,    69,    70,    71,    72,   100,    74,    75,    76,
      77,    78,   140,   141,   114,   101,   102,   106,   113,   115,
     131,   107,   117,   118,   119,   129,   116,   108,   109,   110,
     130,   111,   120,   121,   124,   125,   126,   133,   134,   136,
     135,   137,   138,   144,   132,   139,    93,    50,   142,     0,
     145,    95,     0,     0,     0,     0,     0,   143,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,    34,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33
};

static const yytype_int16 yycheck[] =
{
       4,     5,     1,     2,     3,     4,    16,    17,    38,    39,
      46,    47,    35,    23,    12,    47,    39,    40,    46,    29,
      30,    40,    32,    46,    47,    29,    35,    46,    47,     0,
      29,    44,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    45,    95,    36,    37,    38,    43,
      80,    43,    41,    42,    45,    79,    47,    14,    15,    43,
      79,    18,    19,    20,    21,    22,    43,    24,    25,    26,
      27,    28,    41,    42,    98,    43,    43,    43,    97,    98,
     110,    43,   100,   101,   102,   109,    35,    43,    43,    43,
     109,    43,    43,    43,    35,    35,    35,    35,    35,   123,
      43,    35,    35,    35,   111,    41,    35,     2,    43,    -1,
      41,    38,    -1,    -1,    -1,    -1,    -1,   141,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    45,    47,    49,    50,    51,    52,    53,
      54,    55,    57,    58,    59,    60,    63,    47,    68,    69,
      69,    68,    46,    67,    68,    70,    67,    64,    67,    68,
      64,    35,    61,    62,    62,    62,    61,    61,    62,    62,
      62,    62,    62,    61,    62,    62,    62,    62,    62,    39,
      40,    61,    65,    67,    68,    61,    36,    37,    38,    56,
      61,    44,     0,    50,    51,    53,    51,    43,    43,    43,
      43,    43,    43,    67,    68,    61,    43,    43,    43,    43,
      43,    43,    51,    68,    67,    68,    35,    64,    64,    64,
      43,    43,    41,    42,    35,    35,    35,    40,    66,    67,
      68,    61,    56,    35,    35,    43,    67,    35,    35,    41,
      41,    42,    43,    67,    35,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    51,    52,
      53,    53,    54,    54,    54,    54,    54,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    56,    56,
      57,    57,    57,    57,    58,    58,    59,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      62,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    66,    67,    68,    69,
      69,    70,    70,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     2,     2,     1,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     2,     4,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       3,     4,     4,     4,     1,     1,     4,     4,     3,     3,
       3,     5,     7,     1,     1,     3,     5,     1,     1,     1,
       3,     1,     1,     3,     3
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
  case 8:
#line 68 "misc/parser.y"
        {
    //printf("%d: EOL, parser\n", asm_line);
    asm_line++;
    
  }
#line 1501 "src/parser.cpp"
    break;

  case 9:
#line 76 "misc/parser.y"
                     {
      if (asm_data.is_first_pass)
        ASM_addSymbol(asm_data.location_cnt, SYM_TYPE_NOTYP, false,
                     asm_data.curr_section_symbol_index, (yyvsp[-1].ident));
      //printf("%d: LABEL: %s\n", asm_line, $1);
  }
#line 1512 "src/parser.cpp"
    break;

  case 12:
#line 90 "misc/parser.y"
                       {
      //SECOND PASS
      if (!asm_data.is_first_pass) {
        ASM_makeSymbolsGlobal(sym_name_list);  //only switch syms to global
        sym_name_list.clear(); //clear everytime symbol_list is used
      } else {
        ASM_declareSymbols(sym_name_list);
      }
      //printf("%d: GLOBAL\n", asm_line);
  }
#line 1527 "src/parser.cpp"
    break;

  case 13:
#line 100 "misc/parser.y"
                       {
      if (asm_data.is_first_pass) {
        ASM_declareSymbols(sym_name_list);
        sym_name_list.clear();
      }
      //printf("%d: EXTERN\n", asm_line);
  }
#line 1539 "src/parser.cpp"
    break;

  case 14:
#line 107 "misc/parser.y"
                   {
      if (asm_data.is_first_pass)
        ASM_addSection((yyvsp[0].ident));
      else
        ASM_changeSection((yyvsp[0].ident));
      //printf("%d: SECTION\n", asm_line);
  }
#line 1551 "src/parser.cpp"
    break;

  case 15:
#line 114 "misc/parser.y"
                             {
      
  }
#line 1559 "src/parser.cpp"
    break;

  case 16:
#line 117 "misc/parser.y"
                 {
      asm_data.location_cnt += (yyvsp[0].num);
      //SECOND PASS
      if (!asm_data.is_first_pass)
        for (int i = 0; i < (yyvsp[0].num); i++) 
          ASM_addByteToCurrSection(0x00);
  }
#line 1571 "src/parser.cpp"
    break;

  case 17:
#line 124 "misc/parser.y"
        {
      if (asm_data.is_first_pass)
        ASM_firstPassFinalize();
      else
        ASM_secondPassFinalize();
      YYACCEPT;
  }
#line 1583 "src/parser.cpp"
    break;

  case 23:
#line 139 "misc/parser.y"
                       {
      asm_data.location_cnt += 4;
      //if (!asm_data.is_first_pass) {
        //ASM_addByteToCurrSection(instruction[0]);
        //ASM_addByteToCurrSection(instruction[1] | (uint8_t)(reg_t << 4));
        //ASM_addByteToCurrSection(instruction[2]);
        //ASM_addByteToCurrSection(instruction[3]);
      //}
      //printf("%d: LD\n", asm_line);
  }
#line 1598 "src/parser.cpp"
    break;

  case 24:
#line 149 "misc/parser.y"
                                     {
      asm_data.location_cnt += 4;
      
      //printf("%d: ST\n", asm_line);
  }
#line 1608 "src/parser.cpp"
    break;

  case 25:
#line 154 "misc/parser.y"
                                {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x90);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)csr);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
      
  }
#line 1623 "src/parser.cpp"
    break;

  case 26:
#line 164 "misc/parser.y"
                                {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x94);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 0) | (uint8_t)(csr << 4));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1637 "src/parser.cpp"
    break;

  case 27:
#line 176 "misc/parser.y"
           {
      csr = 0;
  }
#line 1645 "src/parser.cpp"
    break;

  case 28:
#line 179 "misc/parser.y"
            {
      csr = 1;
  }
#line 1653 "src/parser.cpp"
    break;

  case 29:
#line 182 "misc/parser.y"
          {
      csr = 2;
  }
#line 1661 "src/parser.cpp"
    break;

  case 30:
#line 188 "misc/parser.y"
         {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1675 "src/parser.cpp"
    break;

  case 31:
#line 197 "misc/parser.y"
        {
    //printf("%d: INT\n", asm_line);
    asm_data.location_cnt += 4;
    if (!asm_data.is_first_pass) {
      ASM_addByteToCurrSection(0x10);
      ASM_addByteToCurrSection(0x00);
      ASM_addByteToCurrSection(0x00);
      ASM_addByteToCurrSection(0x00);
    }
  }
#line 1690 "src/parser.cpp"
    break;

  case 32:
#line 207 "misc/parser.y"
         {
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x96); //MMMM==0b0110: csr[A]<=mem32[gpr[B]+gpr[C]+D
        ASM_addByteToCurrSection(0x0E); // 0x0 == 0 == status, 0xE == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x04); 

        ASM_addByteToCurrSection(0x93); //pop pc
        ASM_addByteToCurrSection(0xFE); // 0xF == 15 == PC, 0xE == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x08); //move sp by 2 words because of status
      }
      asm_data.location_cnt += 4;
      asm_data.location_cnt += 4;
  }
#line 1710 "src/parser.cpp"
    break;

  case 33:
#line 222 "misc/parser.y"
        {
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x93); //pop pc
        ASM_addByteToCurrSection(0xFE); // 0xE == 15 == PC, 0xE == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x04); 
      }
      asm_data.location_cnt += 4;
  }
#line 1724 "src/parser.cpp"
    break;

  case 34:
#line 234 "misc/parser.y"
                        {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x21);
        ASM_addByteToCurrSection(0xF0); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
#line 1738 "src/parser.cpp"
    break;

  case 35:
#line 243 "misc/parser.y"
                       {
      asm_data.location_cnt += 4;
      // 0011 1000  0xF0  0x0+pc_relative_disp[] + pc_relative_disp[9..12] pc_relative_disp[0..8]
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x38);
        ASM_addByteToCurrSection(0xF0); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
      
  }
#line 1754 "src/parser.cpp"
    break;

  case 36:
#line 257 "misc/parser.y"
                 {  //OC==0b1000; MMMM==0b0001: gpr[A]<=gpr[A]+D; mem32[gpr[A]]<=gpr[C];
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x81);
        ASM_addByteToCurrSection(0xE0); // 0xe == 14 == SP
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | 0x0F);  //FFC
        ASM_addByteToCurrSection(0xFC); 
      }
  }
#line 1768 "src/parser.cpp"
    break;

  case 37:
#line 266 "misc/parser.y"
                {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x93);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | 0x0E); // 0xe == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x04); 
      }
  }
#line 1782 "src/parser.cpp"
    break;

  case 38:
#line 275 "misc/parser.y"
                {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x60);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)gpr_1);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1796 "src/parser.cpp"
    break;

  case 39:
#line 287 "misc/parser.y"
                  {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x40);
        ASM_addByteToCurrSection(0x00 | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1810 "src/parser.cpp"
    break;

  case 40:
#line 296 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x50);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1824 "src/parser.cpp"
    break;

  case 41:
#line 305 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {        
        ASM_addByteToCurrSection(0x51);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1838 "src/parser.cpp"
    break;

  case 42:
#line 314 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x52);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1852 "src/parser.cpp"
    break;

  case 43:
#line 323 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x53);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1866 "src/parser.cpp"
    break;

  case 44:
#line 332 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x61);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1880 "src/parser.cpp"
    break;

  case 45:
#line 341 "misc/parser.y"
                {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x62);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1894 "src/parser.cpp"
    break;

  case 46:
#line 350 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x63);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1908 "src/parser.cpp"
    break;

  case 47:
#line 359 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x70);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1922 "src/parser.cpp"
    break;

  case 48:
#line 368 "misc/parser.y"
                 {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x71);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 1936 "src/parser.cpp"
    break;

  case 49:
#line 380 "misc/parser.y"
        {
      gpr_1 = yylval.num;
  }
#line 1944 "src/parser.cpp"
    break;

  case 50:
#line 387 "misc/parser.y"
                      {
      gpr_2 = yylval.num;
  }
#line 1952 "src/parser.cpp"
    break;

  case 51:
#line 393 "misc/parser.y"
                                      {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x39);
        ASM_addByteToCurrSection(0xF0 | (uint8_t)(gpr_1)); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
#line 1966 "src/parser.cpp"
    break;

  case 52:
#line 402 "misc/parser.y"
                                      {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x3A);
        ASM_addByteToCurrSection(0xF0 | (uint8_t)(gpr_1)); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
#line 1980 "src/parser.cpp"
    break;

  case 53:
#line 411 "misc/parser.y"
                                      {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x3B);
        ASM_addByteToCurrSection(0xF0 | (uint8_t)(gpr_1)); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
#line 1994 "src/parser.cpp"
    break;

  case 54:
#line 425 "misc/parser.y"
            {
      if (asm_data.is_first_pass) {
        ASM_literalAddValueToPool((yyvsp[0].num));
      } else {
        pc_relative_disp = ASM_literalGetLocationFromPool((yyvsp[0].num));  //
      }
  }
#line 2006 "src/parser.cpp"
    break;

  case 55:
#line 432 "misc/parser.y"
           {// add it to the pool, but also add rela record for that spot in the pool
      if (asm_data.is_first_pass) {
        //ASM_symbolAddValueToPool($1);
      } else {
        pc_relative_disp = ASM_symbolGetLocationFromPool((yyvsp[0].ident));  //
      }
  }
#line 2018 "src/parser.cpp"
    break;

  case 56:
#line 442 "misc/parser.y"
                             {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool((yyvsp[-2].num));
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF));
      } else {
        ASM_literalAddValueToPool((yyvsp[-2].num));
      }

      //printf("%d: DOLLAR literal\n", asm_line);
  }
#line 2037 "src/parser.cpp"
    break;

  case 57:
#line 456 "misc/parser.y"
                            {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_symbolGetLocationFromPool((yyvsp[-2].ident));
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF));
      } else {
        //ASM_symbolAddValueToPool($2);
      }
      //printf("%d: DOLLAR symbol\n", asm_line);
  }
#line 2055 "src/parser.cpp"
    break;

  case 58:
#line 469 "misc/parser.y"
                      {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool((yyvsp[-2].num));
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));// f = pc
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));

        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_t << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      } else {
        ASM_literalAddValueToPool((yyvsp[-2].num));
      }
      asm_data.location_cnt += 4;
  }
#line 2078 "src/parser.cpp"
    break;

  case 59:
#line 487 "misc/parser.y"
                     {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_symbolGetLocationFromPool((yyvsp[-2].ident));
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));// f = pc
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));

        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_t << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      } else {
        //ASM_symbolAddValueToPool($1);
      }
      asm_data.location_cnt += 4;
  }
#line 2101 "src/parser.cpp"
    break;

  case 60:
#line 505 "misc/parser.y"
                      {
      if (!asm_data.is_first_pass) {
        uint gpr_t = yylval.num;  //load into this reg, gpr_1 was updated in one_reg
        ASM_addByteToCurrSection(0x91);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_1 << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 2115 "src/parser.cpp"
    break;

  case 61:
#line 514 "misc/parser.y"
                                               {
      if (!asm_data.is_first_pass) {
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_1 << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 2129 "src/parser.cpp"
    break;

  case 62:
#line 523 "misc/parser.y"
                                                            {//two machine inst
      //printf("%d: LEFTBRACKET REG PLUS literal RIGHTBRACKET\n", asm_line);
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool((yyvsp[-3].num));
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92); //load literal val from the pool to gpr_t
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));// f = pc
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));

        ASM_addByteToCurrSection(0x92); //use gpr_1 and gpr_t to load from mem to gpr_t
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_t << 0));//changed0x0F to 0x00
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      } else {
        int value = (yyvsp[-3].num);
        if (!(value >= -2048 && value <= 2047)) {
          printf("ASM_ERROR %d: literal %#x in instruction type ld [%%gpr1 + literal], %%gpr2 must be 12 bit", asm_line, value);
          
          YYABORT;
        }
        ASM_literalAddValueToPool((yyvsp[-3].num));
      }
      asm_data.location_cnt += 4;
  }
#line 2159 "src/parser.cpp"
    break;

  case 63:
#line 554 "misc/parser.y"
            {
      if (!asm_data.is_first_pass) {  //gpr_1 is the src
        pc_relative_disp = ASM_literalGetLocationFromPool((yyvsp[0].num));
        ASM_addByteToCurrSection(0x82);
        ASM_addByteToCurrSection(0x0F); // pc relative
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));
      } else {
        ASM_literalAddValueToPool((yyvsp[0].num));
      }
      //printf("%d: literal\n", asm_line);
  }
#line 2176 "src/parser.cpp"
    break;

  case 64:
#line 566 "misc/parser.y"
           {
      if (!asm_data.is_first_pass) {  //gpr_1 is the src
        pc_relative_disp = ASM_symbolGetLocationFromPool((yyvsp[0].ident));
        ASM_addByteToCurrSection(0x82);
        ASM_addByteToCurrSection(0x0F); // pc relative
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));
      } else {
        //ASM_symbolAddValueToPool($1);//this will need to be removed
      }
      //printf("%d: literal\n", asm_line);
  }
#line 2193 "src/parser.cpp"
    break;

  case 65:
#line 578 "misc/parser.y"
                                 {
      if (!asm_data.is_first_pass) {
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x80);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
#line 2207 "src/parser.cpp"
    break;

  case 66:
#line 587 "misc/parser.y"
                                              {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool((yyvsp[-1].num));
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x80);// maybe even here
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4)); // pc relative and gpr_t
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));
      } else {
        ASM_literalAddValueToPool((yyvsp[-1].num));
      }
      //printf("%d: LEFTBRACKET REG PLUS literal RIGHTBRACKET\n", asm_line);
  }
#line 2225 "src/parser.cpp"
    break;

  case 68:
#line 610 "misc/parser.y"
               {
    if (asm_data.is_first_pass) {
      //ASM_addSymbol(0, SYM_TYPE_NOTYP, false, 0, $1);
    }
  }
#line 2235 "src/parser.cpp"
    break;

  case 69:
#line 618 "misc/parser.y"
           {
      //printf("%d: symbol: %s\n", asm_line, $1);
      sym_name_list.push_back((yyvsp[0].ident));
  }
#line 2244 "src/parser.cpp"
    break;

  case 70:
#line 622 "misc/parser.y"
                             {
      //printf("%d: symbol_list COMMA symbol: %s\n", asm_line, $3);
      sym_name_list.push_back((yyvsp[0].ident));
  }
#line 2253 "src/parser.cpp"
    break;

  case 71:
#line 629 "misc/parser.y"
           {
      if (!asm_data.is_first_pass) { 
        ASM_symbolAddToCurrRelaForAllocation((yyvsp[0].ident));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
      asm_data.location_cnt += 4;
  }
#line 2268 "src/parser.cpp"
    break;

  case 72:
#line 639 "misc/parser.y"
            {
      if (!asm_data.is_first_pass) {
        unsigned int litValue = (yyvsp[0].num);
        ASM_addByteToCurrSection((uint8_t) (litValue >> 0 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 8 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 16));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 24));
      }
      asm_data.location_cnt += 4;
  }
#line 2283 "src/parser.cpp"
    break;

  case 73:
#line 649 "misc/parser.y"
                                     {
      if (!asm_data.is_first_pass) { 
        ASM_symbolAddToCurrRelaForAllocation((yyvsp[0].ident));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
      asm_data.location_cnt += 4;
  }
#line 2298 "src/parser.cpp"
    break;

  case 74:
#line 659 "misc/parser.y"
                                      {
      if (!asm_data.is_first_pass) {
        unsigned int litValue = (yyvsp[0].num);
        ASM_addByteToCurrSection((uint8_t) (litValue >> 0 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 8 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 16));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 24));
      }
      asm_data.location_cnt += 4;
  }
#line 2313 "src/parser.cpp"
    break;


#line 2317 "src/parser.cpp"

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
#line 671 "misc/parser.y"


int main(int argc, char** argv) {
  // open a file handle to a particular file:
  char file_name_in[64];
  strcpy(file_name_in, argv[3]);
  //FIRST PASS
  FILE *fp_in = fopen(file_name_in, "r");
  // make sure it's valid:
  if (!fp_in) {
    std::cout << "Can't open file!" << std::endl;
    return -1;
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = fp_in;
  ASM_addSymbol(0, SYM_TYPE_NOTYP, false, 0, "");
  // Parse through the input:
  do {
		yyparse();
	} while(!feof(yyin));

  //some asm functions

  fclose(fp_in);

  //SECOND PASS
  yyrestart(NULL);
  asm_line = 1;
  FILE *fp_in2 = fopen(file_name_in, "r");
  // make sure it's valid:
  if (!fp_in2) {
    printf("Can't open file!\n");
    return -1;
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = fp_in2;

  // Parse through the input:
  do {
		yyparse();
	} while(!feof(yyin));


  fclose(fp_in2);


  char file_name_out[64];
  strcpy(file_name_out, argv[2]);

  ASM_createOutputFileText(file_name_out);

  return 0;
}


void yyerror(const char *s) {
  std::cout << "EEK, parse error!  Message: " << s << ", at the line: " << asm_line <<std::endl;
  // might as well halt now:
  exit(-1);
}

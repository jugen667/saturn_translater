/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 9 "grammar/grammar.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "../include/defs.h"
#include "../include/common.h"
#include "../include/passe_1.h"



/* Global variables */
extern bool stop_after_syntax;
extern bool stop_after_verif;
extern char * outfile;


/* prototypes */
int yylex(void);
extern int yylineno;

void yyerror(node_t * program_root, char * s);
void analyse_tree(node_t root);
node_t make_node(node_nature nature, int nops, ...);
node_t make_node_ident(char* identifier);
node_t make_node_type(node_type type);
node_t make_node_intval(int32_t value);
node_t make_node_floatval(double value);
node_t make_node_boolval(bool value);
node_t make_node_strval(char* string);


#line 108 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_VOID = 258,                /* TOK_VOID  */
    TOK_INT = 259,                 /* TOK_INT  */
    TOK_INTVAL = 260,              /* TOK_INTVAL  */
    TOK_FLOAT = 261,               /* TOK_FLOAT  */
    TOK_FLOATVAL = 262,            /* TOK_FLOATVAL  */
    TOK_BOOL = 263,                /* TOK_BOOL  */
    TOK_TRUE = 264,                /* TOK_TRUE  */
    TOK_FALSE = 265,               /* TOK_FALSE  */
    TOK_MAIN = 266,                /* TOK_MAIN  */
    TOK_IDENT = 267,               /* TOK_IDENT  */
    TOK_IF = 268,                  /* TOK_IF  */
    TOK_ELSE = 269,                /* TOK_ELSE  */
    TOK_WHILE = 270,               /* TOK_WHILE  */
    TOK_FOR = 271,                 /* TOK_FOR  */
    TOK_PRINT = 272,               /* TOK_PRINT  */
    TOK_SEMICOL = 273,             /* TOK_SEMICOL  */
    TOK_COMMA = 274,               /* TOK_COMMA  */
    TOK_LPAR = 275,                /* TOK_LPAR  */
    TOK_RPAR = 276,                /* TOK_RPAR  */
    TOK_LACC = 277,                /* TOK_LACC  */
    TOK_RACC = 278,                /* TOK_RACC  */
    TOK_STRING = 279,              /* TOK_STRING  */
    TOK_DO = 280,                  /* TOK_DO  */
    TOK_THEN = 281,                /* TOK_THEN  */
    TOK_AFFECT = 282,              /* TOK_AFFECT  */
    TOK_OR = 283,                  /* TOK_OR  */
    TOK_AND = 284,                 /* TOK_AND  */
    TOK_BOR = 285,                 /* TOK_BOR  */
    TOK_BXOR = 286,                /* TOK_BXOR  */
    TOK_BAND = 287,                /* TOK_BAND  */
    TOK_EQ = 288,                  /* TOK_EQ  */
    TOK_NE = 289,                  /* TOK_NE  */
    TOK_GT = 290,                  /* TOK_GT  */
    TOK_LT = 291,                  /* TOK_LT  */
    TOK_GE = 292,                  /* TOK_GE  */
    TOK_LE = 293,                  /* TOK_LE  */
    TOK_SRL = 294,                 /* TOK_SRL  */
    TOK_SRA = 295,                 /* TOK_SRA  */
    TOK_SLL = 296,                 /* TOK_SLL  */
    TOK_PLUS = 297,                /* TOK_PLUS  */
    TOK_MINUS = 298,               /* TOK_MINUS  */
    TOK_MUL = 299,                 /* TOK_MUL  */
    TOK_DIV = 300,                 /* TOK_DIV  */
    TOK_MOD = 301,                 /* TOK_MOD  */
    TOK_UMINUS = 302,              /* TOK_UMINUS  */
    TOK_NOT = 303,                 /* TOK_NOT  */
    TOK_BNOT = 304                 /* TOK_BNOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TOK_VOID 258
#define TOK_INT 259
#define TOK_INTVAL 260
#define TOK_FLOAT 261
#define TOK_FLOATVAL 262
#define TOK_BOOL 263
#define TOK_TRUE 264
#define TOK_FALSE 265
#define TOK_MAIN 266
#define TOK_IDENT 267
#define TOK_IF 268
#define TOK_ELSE 269
#define TOK_WHILE 270
#define TOK_FOR 271
#define TOK_PRINT 272
#define TOK_SEMICOL 273
#define TOK_COMMA 274
#define TOK_LPAR 275
#define TOK_RPAR 276
#define TOK_LACC 277
#define TOK_RACC 278
#define TOK_STRING 279
#define TOK_DO 280
#define TOK_THEN 281
#define TOK_AFFECT 282
#define TOK_OR 283
#define TOK_AND 284
#define TOK_BOR 285
#define TOK_BXOR 286
#define TOK_BAND 287
#define TOK_EQ 288
#define TOK_NE 289
#define TOK_GT 290
#define TOK_LT 291
#define TOK_GE 292
#define TOK_LE 293
#define TOK_SRL 294
#define TOK_SRA 295
#define TOK_SLL 296
#define TOK_PLUS 297
#define TOK_MINUS 298
#define TOK_MUL 299
#define TOK_DIV 300
#define TOK_MOD 301
#define TOK_UMINUS 302
#define TOK_NOT 303
#define TOK_BNOT 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "grammar/grammar.y"

    int32_t intval;
    double floatval; // double for accuracy
    char * strval;
    node_t ptr;

#line 266 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (node_t * program_root);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_VOID = 3,                   /* TOK_VOID  */
  YYSYMBOL_TOK_INT = 4,                    /* TOK_INT  */
  YYSYMBOL_TOK_INTVAL = 5,                 /* TOK_INTVAL  */
  YYSYMBOL_TOK_FLOAT = 6,                  /* TOK_FLOAT  */
  YYSYMBOL_TOK_FLOATVAL = 7,               /* TOK_FLOATVAL  */
  YYSYMBOL_TOK_BOOL = 8,                   /* TOK_BOOL  */
  YYSYMBOL_TOK_TRUE = 9,                   /* TOK_TRUE  */
  YYSYMBOL_TOK_FALSE = 10,                 /* TOK_FALSE  */
  YYSYMBOL_TOK_MAIN = 11,                  /* TOK_MAIN  */
  YYSYMBOL_TOK_IDENT = 12,                 /* TOK_IDENT  */
  YYSYMBOL_TOK_IF = 13,                    /* TOK_IF  */
  YYSYMBOL_TOK_ELSE = 14,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 15,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_FOR = 16,                   /* TOK_FOR  */
  YYSYMBOL_TOK_PRINT = 17,                 /* TOK_PRINT  */
  YYSYMBOL_TOK_SEMICOL = 18,               /* TOK_SEMICOL  */
  YYSYMBOL_TOK_COMMA = 19,                 /* TOK_COMMA  */
  YYSYMBOL_TOK_LPAR = 20,                  /* TOK_LPAR  */
  YYSYMBOL_TOK_RPAR = 21,                  /* TOK_RPAR  */
  YYSYMBOL_TOK_LACC = 22,                  /* TOK_LACC  */
  YYSYMBOL_TOK_RACC = 23,                  /* TOK_RACC  */
  YYSYMBOL_TOK_STRING = 24,                /* TOK_STRING  */
  YYSYMBOL_TOK_DO = 25,                    /* TOK_DO  */
  YYSYMBOL_TOK_THEN = 26,                  /* TOK_THEN  */
  YYSYMBOL_TOK_AFFECT = 27,                /* TOK_AFFECT  */
  YYSYMBOL_TOK_OR = 28,                    /* TOK_OR  */
  YYSYMBOL_TOK_AND = 29,                   /* TOK_AND  */
  YYSYMBOL_TOK_BOR = 30,                   /* TOK_BOR  */
  YYSYMBOL_TOK_BXOR = 31,                  /* TOK_BXOR  */
  YYSYMBOL_TOK_BAND = 32,                  /* TOK_BAND  */
  YYSYMBOL_TOK_EQ = 33,                    /* TOK_EQ  */
  YYSYMBOL_TOK_NE = 34,                    /* TOK_NE  */
  YYSYMBOL_TOK_GT = 35,                    /* TOK_GT  */
  YYSYMBOL_TOK_LT = 36,                    /* TOK_LT  */
  YYSYMBOL_TOK_GE = 37,                    /* TOK_GE  */
  YYSYMBOL_TOK_LE = 38,                    /* TOK_LE  */
  YYSYMBOL_TOK_SRL = 39,                   /* TOK_SRL  */
  YYSYMBOL_TOK_SRA = 40,                   /* TOK_SRA  */
  YYSYMBOL_TOK_SLL = 41,                   /* TOK_SLL  */
  YYSYMBOL_TOK_PLUS = 42,                  /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 43,                 /* TOK_MINUS  */
  YYSYMBOL_TOK_MUL = 44,                   /* TOK_MUL  */
  YYSYMBOL_TOK_DIV = 45,                   /* TOK_DIV  */
  YYSYMBOL_TOK_MOD = 46,                   /* TOK_MOD  */
  YYSYMBOL_TOK_UMINUS = 47,                /* TOK_UMINUS  */
  YYSYMBOL_TOK_NOT = 48,                   /* TOK_NOT  */
  YYSYMBOL_TOK_BNOT = 49,                  /* TOK_BNOT  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_listdecl = 52,                  /* listdecl  */
  YYSYMBOL_listdeclnonnull = 53,           /* listdeclnonnull  */
  YYSYMBOL_vardecl = 54,                   /* vardecl  */
  YYSYMBOL_type = 55,                      /* type  */
  YYSYMBOL_listtypedecl = 56,              /* listtypedecl  */
  YYSYMBOL_decl = 57,                      /* decl  */
  YYSYMBOL_maindecl = 58,                  /* maindecl  */
  YYSYMBOL_listinst = 59,                  /* listinst  */
  YYSYMBOL_listinstnonnull = 60,           /* listinstnonnull  */
  YYSYMBOL_inst = 61,                      /* inst  */
  YYSYMBOL_list = 62,                      /* list  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_expr = 64,                      /* expr  */
  YYSYMBOL_listparamprint = 65,            /* listparamprint  */
  YYSYMBOL_paramprint = 66,                /* paramprint  */
  YYSYMBOL_ident = 67                      /* ident  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   500

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
static const yytype_int16 yyrline[] =
{
       0,    92,    92,    97,   102,   107,   114,   119,   124,   128,
     134,   140,   144,   148,   152,   158,   162,   168,   172,   178,
     184,   190,   194,   200,   204,   208,   212,   216,   220,   224,
     228,   232,   237,   242,   246,   250,   254,   260,   266,   270,
     274,   278,   282,   286,   290,   294,   298,   302,   306,   310,
     314,   318,   322,   326,   330,   334,   338,   342,   346,   350,
     354,   358,   362,   366,   370,   374,   378,   384,   388,   394,
     398,   404,   408
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_VOID", "TOK_INT",
  "TOK_INTVAL", "TOK_FLOAT", "TOK_FLOATVAL", "TOK_BOOL", "TOK_TRUE",
  "TOK_FALSE", "TOK_MAIN", "TOK_IDENT", "TOK_IF", "TOK_ELSE", "TOK_WHILE",
  "TOK_FOR", "TOK_PRINT", "TOK_SEMICOL", "TOK_COMMA", "TOK_LPAR",
  "TOK_RPAR", "TOK_LACC", "TOK_RACC", "TOK_STRING", "TOK_DO", "TOK_THEN",
  "TOK_AFFECT", "TOK_OR", "TOK_AND", "TOK_BOR", "TOK_BXOR", "TOK_BAND",
  "TOK_EQ", "TOK_NE", "TOK_GT", "TOK_LT", "TOK_GE", "TOK_LE", "TOK_SRL",
  "TOK_SRA", "TOK_SLL", "TOK_PLUS", "TOK_MINUS", "TOK_MUL", "TOK_DIV",
  "TOK_MOD", "TOK_UMINUS", "TOK_NOT", "TOK_BNOT", "$accept", "program",
  "listdecl", "listdeclnonnull", "vardecl", "type", "listtypedecl", "decl",
  "maindecl", "listinst", "listinstnonnull", "inst", "list", "block",
  "expr", "listparamprint", "paramprint", "ident", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-25)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     162,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -13,   -11,    -4,    -2,   -25,   140,   162,    58,   140,
     140,   140,    42,   -25,   153,   -25,    87,   -25,   -25,    58,
     -25,   162,   -25,    -5,    45,   140,   140,   140,    70,   239,
     106,    87,   115,    73,   -25,   -25,   -25,   -25,   -25,   -25,
      86,   -25,   -12,   -25,   -25,   -25,   -25,   -25,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   265,   291,
     184,   -25,    -9,   -25,   -25,   -25,    66,   -25,    65,   -25,
      87,    81,   140,   380,   397,   413,   428,   442,   155,   155,
     454,   454,   454,   454,   193,   193,   193,    97,    97,   -25,
     -25,   -25,   362,    58,    58,   140,    70,    90,   140,   -25,
      91,   362,   102,   -25,   213,   -25,   -25,   317,   -25,    58,
     140,   111,   -25,   343,   -25,    58,   -25
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    14,    11,    62,    13,    63,    12,    64,    65,    72,
      71,     0,     0,     0,     0,    30,     0,     7,     0,     0,
       0,     0,     0,    35,     6,     8,     0,     5,    36,    20,
      21,     0,    29,     0,    66,     0,     0,     0,     0,     0,
       6,     0,     0,     0,    45,    58,    59,     1,     9,     3,
       0,    15,    17,    22,    33,     2,    34,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,     0,    68,    69,    60,    17,    37,     0,    10,
       0,     0,     0,    51,    50,    53,    54,    52,    48,    49,
      44,    43,    46,    47,    55,    56,    57,    40,    41,    38,
      39,    42,    61,    32,    32,     0,     0,     0,     0,    16,
       0,    18,    25,    26,     0,    67,    31,     0,    19,    32,
       0,     0,    24,     0,    28,    32,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -25,   -25,    48,   134,   -21,    47,   -25,    46,    60,    55,
     -25,   -18,   122,    24,   -15,   -25,    30,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    22,    23,    40,    25,    26,    50,    51,    27,    28,
      29,    30,    31,    32,    33,    82,    83,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    39,    52,    48,    44,    45,    46,    35,    91,    36,
     116,    53,   117,    57,    84,    92,    37,    86,    38,    48,
      78,    79,    80,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    47,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     3,    41,     5,    86,     7,     8,     9,
      10,    11,    77,    12,    13,    14,    15,   121,    16,    54,
      17,     9,    10,    18,    49,   118,    56,    41,    88,    41,
      54,    55,    84,    92,    81,   122,   123,    56,     9,    10,
     124,    19,   120,   127,    89,    90,    20,    21,   126,     1,
       2,   132,     4,    17,     6,   133,   129,   136,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,   134,
      12,    13,    14,    15,    24,    16,   119,    17,    87,    42,
      18,    74,    75,    76,   128,     3,   125,     5,     0,     7,
       8,     9,    10,    -4,     0,     0,     1,     2,    19,     4,
      16,     6,     0,    20,    21,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,    12,    13,    14,
      15,     0,    16,    19,    17,     0,     0,    18,    20,    21,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   115,     0,     0,    19,     0,     0,     0,     0,
      20,    21,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   130,    -5,    -5,    -5,    72,    73,    74,    75,    76,
       0,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      85,     0,     0,     0,     0,     0,     0,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,   113,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   114,     0,     0,     0,     0,     0,     0,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,   131,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   135,     0,     0,     0,     0,     0,
       0,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -5,
      -5,    -5,    -5,    69,    70,    71,    72,    73,    74,    75,
      76
};

static const yytype_int16 yycheck[] =
{
      18,    16,    26,    24,    19,    20,    21,    20,    20,    20,
      19,    29,    21,    18,    38,    27,    20,    41,    20,    40,
      35,    36,    37,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     5,    17,     7,    90,     9,    10,    11,
      12,    13,    27,    15,    16,    17,    18,    92,    20,    31,
      22,    11,    12,    25,    24,    20,    31,    40,    15,    42,
      42,    31,   116,    27,    24,   113,   114,    42,    11,    12,
     115,    43,    21,   118,    18,    19,    48,    49,    18,     3,
       4,   129,     6,    22,     8,   130,    14,   135,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    18,
      15,    16,    17,    18,     0,    20,    90,    22,    23,    17,
      25,    44,    45,    46,   120,     5,   116,     7,    -1,     9,
      10,    11,    12,     0,    -1,    -1,     3,     4,    43,     6,
      20,     8,    -1,    48,    49,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    -1,    20,    43,    22,    -1,    -1,    25,    48,    49,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    18,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    18,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    21,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    15,    16,    17,    18,    20,    22,    25,    43,
      48,    49,    51,    52,    53,    54,    55,    58,    59,    60,
      61,    62,    63,    64,    67,    20,    20,    20,    20,    64,
      53,    55,    62,    61,    64,    64,    64,     0,    54,    58,
      56,    57,    67,    61,    52,    58,    59,    18,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    27,    64,    64,
      64,    24,    65,    66,    67,    21,    67,    23,    15,    18,
      19,    20,    27,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    21,    21,    18,    19,    21,    20,    57,
      21,    64,    61,    61,    64,    66,    18,    64,    63,    14,
      18,    21,    61,    64,    18,    21,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    52,    52,    53,    53,
      54,    55,    55,    55,    55,    56,    56,    57,    57,    58,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    66,
      66,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     0,     1,     2,
       3,     1,     1,     1,     1,     1,     3,     1,     3,     5,
       1,     1,     2,     2,     7,     5,     5,     9,     7,     1,
       1,     5,     0,     2,     2,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     3,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (program_root, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, program_root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, node_t * program_root)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (program_root);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, node_t * program_root)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, program_root);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, node_t * program_root)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], program_root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, program_root); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, node_t * program_root)
{
  YY_USE (yyvaluep);
  YY_USE (program_root);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (node_t * program_root)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* program: list maindecl  */
#line 93 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node(NODE_PROGRAM, 2, (yyvsp[-1].ptr), (yyvsp[0].ptr));
            *program_root = (yyval.ptr);
        }
#line 1480 "y.tab.c"
    break;

  case 3: /* program: listdeclnonnull maindecl  */
#line 98 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node(NODE_PROGRAM, 2, (yyvsp[-1].ptr), (yyvsp[0].ptr));
            *program_root = (yyval.ptr);
        }
#line 1489 "y.tab.c"
    break;

  case 4: /* program: listdeclnonnull  */
#line 103 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node(NODE_PROGRAM, 2, (yyvsp[0].ptr), NULL);
            *program_root = (yyval.ptr);
        }
#line 1498 "y.tab.c"
    break;

  case 5: /* program: maindecl  */
#line 108 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node(NODE_PROGRAM, 1, (yyvsp[0].ptr));
            *program_root = (yyval.ptr);
        }
#line 1507 "y.tab.c"
    break;

  case 6: /* listdecl: listdeclnonnull  */
#line 115 "grammar/grammar.y"
        {
            (yyval.ptr) = (yyvsp[0].ptr);
        }
#line 1515 "y.tab.c"
    break;

  case 7: /* listdecl: %empty  */
#line 119 "grammar/grammar.y"
        {
            (yyval.ptr) = NULL;
        }
#line 1523 "y.tab.c"
    break;

  case 8: /* listdeclnonnull: vardecl  */
#line 125 "grammar/grammar.y"
            { 
                (yyval.ptr) = (yyvsp[0].ptr); 
            }
#line 1531 "y.tab.c"
    break;

  case 9: /* listdeclnonnull: listdeclnonnull vardecl  */
#line 129 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_LIST, 2, (yyvsp[-1].ptr), (yyvsp[0].ptr));
            }
#line 1539 "y.tab.c"
    break;

  case 10: /* vardecl: type listtypedecl TOK_SEMICOL  */
#line 135 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node(NODE_DECLS, 2, (yyvsp[-2].ptr), (yyvsp[-1].ptr));
        }
#line 1547 "y.tab.c"
    break;

  case 11: /* type: TOK_INT  */
#line 141 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node_type(TYPE_INT);
        }
#line 1555 "y.tab.c"
    break;

  case 12: /* type: TOK_BOOL  */
#line 145 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node_type(TYPE_BOOL);
        }
#line 1563 "y.tab.c"
    break;

  case 13: /* type: TOK_FLOAT  */
#line 149 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node_type(TYPE_FLOAT);
        }
#line 1571 "y.tab.c"
    break;

  case 14: /* type: TOK_VOID  */
#line 153 "grammar/grammar.y"
        {
            (yyval.ptr) = make_node_type(TYPE_VOID);
        }
#line 1579 "y.tab.c"
    break;

  case 15: /* listtypedecl: decl  */
#line 159 "grammar/grammar.y"
                {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 1587 "y.tab.c"
    break;

  case 16: /* listtypedecl: listtypedecl TOK_COMMA decl  */
#line 163 "grammar/grammar.y"
                {
                    (yyval.ptr) = make_node(NODE_LIST, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
                }
#line 1595 "y.tab.c"
    break;

  case 17: /* decl: ident  */
#line 169 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_DECL, 2, (yyvsp[0].ptr), NULL);
            }
#line 1603 "y.tab.c"
    break;

  case 18: /* decl: ident TOK_AFFECT expr  */
#line 173 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_DECL, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1611 "y.tab.c"
    break;

  case 19: /* maindecl: type ident TOK_LPAR TOK_RPAR block  */
#line 179 "grammar/grammar.y"
                {
                    (yyval.ptr) = make_node(NODE_FUNC, 3, (yyvsp[-4].ptr), (yyvsp[-3].ptr), (yyvsp[0].ptr));
                }
#line 1619 "y.tab.c"
    break;

  case 20: /* listinst: listinstnonnull  */
#line 185 "grammar/grammar.y"
                {
                    (yyval.ptr) =(yyvsp[0].ptr);
                }
#line 1627 "y.tab.c"
    break;

  case 21: /* listinstnonnull: inst  */
#line 191 "grammar/grammar.y"
                {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 1635 "y.tab.c"
    break;

  case 22: /* listinstnonnull: listinstnonnull inst  */
#line 195 "grammar/grammar.y"
                {
                    (yyval.ptr) = make_node(NODE_LIST, 2, (yyvsp[-1].ptr), (yyvsp[0].ptr));
                }
#line 1643 "y.tab.c"
    break;

  case 23: /* inst: expr TOK_SEMICOL  */
#line 201 "grammar/grammar.y"
            {
                (yyval.ptr) = (yyvsp[-1].ptr);
            }
#line 1651 "y.tab.c"
    break;

  case 24: /* inst: TOK_IF TOK_LPAR expr TOK_RPAR inst TOK_ELSE inst  */
#line 205 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_IF, 3, (yyvsp[-4].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1659 "y.tab.c"
    break;

  case 25: /* inst: TOK_IF TOK_LPAR expr TOK_RPAR inst  */
#line 209 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_IF, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1667 "y.tab.c"
    break;

  case 26: /* inst: TOK_WHILE TOK_LPAR expr TOK_RPAR inst  */
#line 213 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_WHILE, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1675 "y.tab.c"
    break;

  case 27: /* inst: TOK_FOR TOK_LPAR expr TOK_SEMICOL expr TOK_SEMICOL expr TOK_RPAR inst  */
#line 217 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_FOR, 4, (yyvsp[-6].ptr), (yyvsp[-4].ptr),(yyvsp[-2].ptr) ,(yyvsp[0].ptr));
            }
#line 1683 "y.tab.c"
    break;

  case 28: /* inst: TOK_DO inst TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SEMICOL  */
#line 221 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_DOWHILE, 2, (yyvsp[-5].ptr), (yyvsp[-2].ptr));
            }
#line 1691 "y.tab.c"
    break;

  case 29: /* inst: block  */
#line 225 "grammar/grammar.y"
            {
                (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 1699 "y.tab.c"
    break;

  case 30: /* inst: TOK_SEMICOL  */
#line 229 "grammar/grammar.y"
            {
                (yyval.ptr) = NULL;
            }
#line 1707 "y.tab.c"
    break;

  case 31: /* inst: TOK_PRINT TOK_LPAR listparamprint TOK_RPAR TOK_SEMICOL  */
#line 233 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_PRINT, 1, (yyvsp[-2].ptr));
            }
#line 1715 "y.tab.c"
    break;

  case 32: /* inst: %empty  */
#line 237 "grammar/grammar.y"
            {
                (yyval.ptr) = NULL;
            }
#line 1723 "y.tab.c"
    break;

  case 33: /* list: list listdecl  */
#line 243 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_LIST, 2, (yyvsp[-1].ptr), (yyvsp[0].ptr));
            }
#line 1731 "y.tab.c"
    break;

  case 34: /* list: list listinst  */
#line 247 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_LIST, 2, (yyvsp[-1].ptr), (yyvsp[0].ptr));
            }
#line 1739 "y.tab.c"
    break;

  case 35: /* list: listdecl  */
#line 251 "grammar/grammar.y"
            {
                (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 1747 "y.tab.c"
    break;

  case 36: /* list: listinst  */
#line 255 "grammar/grammar.y"
            {
                (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 1755 "y.tab.c"
    break;

  case 37: /* block: TOK_LACC list TOK_RACC  */
#line 261 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_BLOCK, 1, (yyvsp[-1].ptr));
            }
#line 1763 "y.tab.c"
    break;

  case 38: /* expr: expr TOK_MUL expr  */
#line 267 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_MUL, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1771 "y.tab.c"
    break;

  case 39: /* expr: expr TOK_DIV expr  */
#line 271 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_DIV, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1779 "y.tab.c"
    break;

  case 40: /* expr: expr TOK_PLUS expr  */
#line 275 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_PLUS, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1787 "y.tab.c"
    break;

  case 41: /* expr: expr TOK_MINUS expr  */
#line 279 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_MINUS, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1795 "y.tab.c"
    break;

  case 42: /* expr: expr TOK_MOD expr  */
#line 283 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_MOD, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1803 "y.tab.c"
    break;

  case 43: /* expr: expr TOK_LT expr  */
#line 287 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_LT, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1811 "y.tab.c"
    break;

  case 44: /* expr: expr TOK_GT expr  */
#line 291 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_GT, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1819 "y.tab.c"
    break;

  case 45: /* expr: TOK_MINUS expr  */
#line 295 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_UMINUS, 1, (yyvsp[0].ptr));
            }
#line 1827 "y.tab.c"
    break;

  case 46: /* expr: expr TOK_GE expr  */
#line 299 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_GE, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1835 "y.tab.c"
    break;

  case 47: /* expr: expr TOK_LE expr  */
#line 303 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_LE, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1843 "y.tab.c"
    break;

  case 48: /* expr: expr TOK_EQ expr  */
#line 307 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_EQ, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1851 "y.tab.c"
    break;

  case 49: /* expr: expr TOK_NE expr  */
#line 311 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_NE, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1859 "y.tab.c"
    break;

  case 50: /* expr: expr TOK_AND expr  */
#line 315 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_AND, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1867 "y.tab.c"
    break;

  case 51: /* expr: expr TOK_OR expr  */
#line 319 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_OR, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1875 "y.tab.c"
    break;

  case 52: /* expr: expr TOK_BAND expr  */
#line 323 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_BAND, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1883 "y.tab.c"
    break;

  case 53: /* expr: expr TOK_BOR expr  */
#line 327 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_BOR, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1891 "y.tab.c"
    break;

  case 54: /* expr: expr TOK_BXOR expr  */
#line 331 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_BXOR, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1899 "y.tab.c"
    break;

  case 55: /* expr: expr TOK_SRL expr  */
#line 335 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_SRL, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1907 "y.tab.c"
    break;

  case 56: /* expr: expr TOK_SRA expr  */
#line 339 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_SRA, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1915 "y.tab.c"
    break;

  case 57: /* expr: expr TOK_SLL expr  */
#line 343 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_SLL, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1923 "y.tab.c"
    break;

  case 58: /* expr: TOK_NOT expr  */
#line 347 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_NOT, 1, (yyvsp[0].ptr));
            }
#line 1931 "y.tab.c"
    break;

  case 59: /* expr: TOK_BNOT expr  */
#line 351 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_BNOT, 1, (yyvsp[0].ptr));
            }
#line 1939 "y.tab.c"
    break;

  case 60: /* expr: TOK_LPAR expr TOK_RPAR  */
#line 355 "grammar/grammar.y"
            {
                (yyval.ptr) = (yyvsp[-1].ptr);
            }
#line 1947 "y.tab.c"
    break;

  case 61: /* expr: ident TOK_AFFECT expr  */
#line 359 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node(NODE_AFFECT, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 1955 "y.tab.c"
    break;

  case 62: /* expr: TOK_INTVAL  */
#line 363 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node_intval((yyvsp[0].intval));
            }
#line 1963 "y.tab.c"
    break;

  case 63: /* expr: TOK_FLOATVAL  */
#line 367 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node_floatval((yyvsp[0].floatval));
            }
#line 1971 "y.tab.c"
    break;

  case 64: /* expr: TOK_TRUE  */
#line 371 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node_boolval(true);
            }
#line 1979 "y.tab.c"
    break;

  case 65: /* expr: TOK_FALSE  */
#line 375 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node_boolval(false);
            }
#line 1987 "y.tab.c"
    break;

  case 66: /* expr: ident  */
#line 379 "grammar/grammar.y"
            {
                (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 1995 "y.tab.c"
    break;

  case 67: /* listparamprint: listparamprint TOK_COMMA paramprint  */
#line 385 "grammar/grammar.y"
                {
                    (yyval.ptr) = make_node(NODE_LIST, 2, (yyvsp[-2].ptr), (yyvsp[0].ptr));
                }
#line 2003 "y.tab.c"
    break;

  case 68: /* listparamprint: paramprint  */
#line 389 "grammar/grammar.y"
                {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 2011 "y.tab.c"
    break;

  case 69: /* paramprint: ident  */
#line 395 "grammar/grammar.y"
                {
                    (yyval.ptr) = (yyvsp[0].ptr);
                }
#line 2019 "y.tab.c"
    break;

  case 70: /* paramprint: TOK_STRING  */
#line 399 "grammar/grammar.y"
                {
                    (yyval.ptr) = make_node_strval((yyvsp[0].strval));
                }
#line 2027 "y.tab.c"
    break;

  case 71: /* ident: TOK_IDENT  */
#line 405 "grammar/grammar.y"
            {                
                (yyval.ptr) = make_node_ident((yyvsp[0].strval));
            }
#line 2035 "y.tab.c"
    break;

  case 72: /* ident: TOK_MAIN  */
#line 409 "grammar/grammar.y"
            {
                (yyval.ptr) = make_node_ident("main");
            }
#line 2043 "y.tab.c"
    break;


#line 2047 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (program_root, YY_("syntax error"));
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
                      yytoken, &yylval, program_root);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, program_root);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (program_root, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, program_root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, program_root);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 414 "grammar/grammar.y"


// === NODE MAKER FUNCS === 
node_t make_node(node_nature nature, int nops, ...) {
    va_list ap;
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nops = nops;
    node->lineno = yylineno;
    node->nature = nature;

    va_start(ap, nops);

    node->opr = (node_t *) malloc(nops*sizeof(node_s));

    for(int i=0;i<nops;i++){
        node->opr[i] = va_arg(ap, node_t);
    }
    

    va_end(ap);
    return node;
}

node_t make_node_ident(char* identifier){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_IDENT;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = identifier;
    node->type = TYPE_NONE;         // init but update in passe 1
    node->offset = 0;               // init but update in passe 1
    node->global_decl = false;      // init but update in passe 1
    node->decl_node = NULL;
    node->opr = NULL;
    node->int_value = 0;
    node->float_value = 0;
    return node;
}

node_t make_node_type(node_type type){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_TYPE;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = type;              // init but update in passe 1
    node->offset = 0;               // init but update in passe 1
    node->global_decl = false;      // init but update in passe 1
    node->decl_node = NULL;
    node->opr = NULL;
    node->int_value = 0;
    node->float_value = 0;
    return node;
}

node_t make_node_intval(int32_t value){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_INTVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_INT;          // init but update in passe 1
    node->offset = 0;               // init but update in passe 1
    node->global_decl = false;      // init but update in passe 1
    node->int_value = value;
    node->decl_node = NULL;
    node->opr = NULL;
    return node;
}

node_t make_node_floatval(double value){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_FLOATVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_FLOAT;        // init but update in passe 1
    node->offset = 0;               // init but update in passe 1
    node->global_decl = false;      // init but update in passe 1
    node->float_value = value;
    node->decl_node = NULL;
    node->opr = NULL;
    return node;
}

node_t make_node_boolval(bool value){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_BOOLVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_BOOL;         // init but update in passe 1
    node->offset = 0;               // init but update in passe 1
    node->global_decl = false;      // init but update in passe 1
    node->int_value = value;
    node->decl_node = NULL;
    node->opr = NULL;
    return node;
}

node_t make_node_strval(char* string){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_STRINGVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_NONE;         // init but update in passe 1
    node->offset = 0;               // init but update in passe 1
    node->global_decl = false;      // maj dans passe 1
    node->str = string;
    node->decl_node = NULL;
    node->opr = NULL;
    return node;
}

void analyse_tree(node_t root) {
    dump_tree(root, "apres_syntaxe.dot");
    if (!stop_after_syntax) {
        analyse_passe_1(root);
        dump_tree(root, "apres_passe_1.dot");
        // if (!stop_after_verif) {
        //     create_program(); 
        //     gen_code_passe_2(root);
        //     dump_mips_program(outfile);
        //     free_program();
        // }
        // free_global_strings();
    }
    free_nodes(root);
}


/* Automatically called when error 
 * DON'T CALL IT : value given by yylineno won't be correct after syntaxe analysis
 */
void yyerror(node_t * program_root, char * s) {
    fprintf(stderr, "Error line %d: %s\n", yylineno, s);
    exit(1);
}


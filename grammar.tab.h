/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
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
    TOK_SLL = 295,                 /* TOK_SLL  */
    TOK_PLUS = 296,                /* TOK_PLUS  */
    TOK_MINUS = 297,               /* TOK_MINUS  */
    TOK_MUL = 298,                 /* TOK_MUL  */
    TOK_DIV = 299,                 /* TOK_DIV  */
    TOK_MOD = 300,                 /* TOK_MOD  */
    TOK_UMINUS = 301,              /* TOK_UMINUS  */
    TOK_NOT = 302,                 /* TOK_NOT  */
    TOK_BNOT = 303                 /* TOK_BNOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 54 "grammar/grammar.y"

    int64_t intval;
    double floatval; // double for accuracy
    char * strval;
    node_t ptr;

#line 119 "grammar.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (node_t * program_root);


#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */

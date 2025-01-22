/*  ======================================= */
/*  > Author :   jugen667                   */
/*  > Title  :   lexico.l                   */
/*  > Desc.  :   Translation of code to     */
/*               tokens and main function   */
/*  > Associated header :                   */
/*  ======================================= */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../include/defs.h"
#include "../include/common.h"

#include "../include/y.tab.h"

int yyparse(node_t * program_root);
void analyse_tree(node_t root);


char * infile = NULL;
char * outfile = DEFAULT_OUTFILE;
bool stop_after_syntax = false;
bool stop_after_verif = false;

#if YYDEBUG
extern int yydebug;
#endif

#if LEX_DEBUG
#define RETURN(token) ({ printf("%s \t\"%s\"\n", #token, yytext); return token; })
#else
#define RETURN(token) ({ return token; })
#endif


%}

%option yylineno


LETTER              [a-zA-Z]
FIGURE              [0-9]
FIGURE_NON_NUL      [1-9]
INTEGER_DEC         0|{FIGURE_NON_NUL}{FIGURE}*
LETTER_HEXA         [a-fA-F]
INTEGER_HEXA        0[xX]({FIGURE}|{LETTER_HEXA})+
INTEGER             \-?{INTEGER_DEC}
FLOAT               \-?({INTEGER_DEC}*\.{INTEGER_DEC}*)
IDF                 {LETTER}({LETTER}|{FIGURE}|'_')*
SPECCHAR            [\x09-\x0E]
STRING_CHAR         [\x20-\x21]|[\x23-\x5B]|[\x5D-\x7E] 
STRING              \"({STRING_CHAR}|\\\"|\\n)*\"
COMMENT             \/\/({STRING_CHAR}|{STRING})*(\\n)*
COMMENTMUL          \/\*({STRING_CHAR}|{STRING}|{SPECCHAR})*\*\/
SEPARATOR           [ \t\n]+
/* ==== TO DO POINTERS MAYBE ? ==== */

%%

"void"          RETURN(TOK_VOID);
"int"           RETURN(TOK_INT);
"float"         RETURN(TOK_FLOAT); 
"bool"          RETURN(TOK_BOOL);
"true"          RETURN(TOK_TRUE);
"false"         RETURN(TOK_FALSE);
"if"            RETURN(TOK_IF);
"else"          RETURN(TOK_ELSE);
"while"         RETURN(TOK_WHILE);
"for"           RETURN(TOK_FOR);
"do"            RETURN(TOK_DO);
"printf"        RETURN(TOK_PRINT);
"main"          RETURN(TOK_MAIN);

"+"             RETURN(TOK_PLUS);
"-"             RETURN(TOK_MINUS);
"*"             RETURN(TOK_MUL);
"/"             RETURN(TOK_DIV);
"%"             RETURN(TOK_MOD);
">"             RETURN(TOK_GT);
"<"             RETURN(TOK_LT);
"!"             RETURN(TOK_NOT);
"~"             RETURN(TOK_BNOT);
"&"             RETURN(TOK_BAND);
"|"             RETURN(TOK_BOR);
"^"             RETURN(TOK_BXOR);
"="             RETURN(TOK_AFFECT);
";"             RETURN(TOK_SEMICOL);
","             RETURN(TOK_COMMA);
"("             RETURN(TOK_LPAR);
")"             RETURN(TOK_RPAR);
"{"             RETURN(TOK_LACC);
"}"             RETURN(TOK_RACC);
">>"            RETURN(TOK_SRA);
">>>"           RETURN(TOK_SRL);
"<<"            RETURN(TOK_SLL);
">="            RETURN(TOK_GE);
"<="            RETURN(TOK_LE);
"=="            RETURN(TOK_EQ);
"!="            RETURN(TOK_NE);
"&&"            RETURN(TOK_AND);
"||"            RETURN(TOK_OR);




{IDF} {
                #if !LEX_DEBUG
                yylval.strval = strdupl(yytext);
                #endif
                RETURN(TOK_IDENT);
}

{INTEGER} {
                #if !LEX_DEBUG
                yylval.intval = atoi(yytext);
                #endif
                RETURN(TOK_INTVAL);
}

{INTEGER_HEXA} {
                #if !LEX_DEBUG
                yylval.intval = strtol(yytext, NULL, 16);
                #endif
                RETURN(TOK_INTVAL);
}

{FLOAT} {
                #if !LEX_DEBUG
                yylval.floatval = atof(yytext);
                #endif
                RETURN(TOK_FLOATVAL);
}

{STRING} {
                #if !LEX_DEBUG
                yylval.strval = strdupl(yytext);
                #endif
                RETURN(TOK_STRING);
}

{COMMENT} {
}

{COMMENTMUL} {
}


[ \t\n]+

. {
    fprintf(stderr, RED "Error line" BOLD " %d " NC ": Lexical error\n", yylineno);
    exit(1);
}


%%

int yywrap(void) {
    return 1;
}


int main(int argc, char ** argv) {
    node_t program_root;
    parse_args(argc, argv);
    yyin = fopen(infile, "r");
    #if LEX_DEBUG
        while(yylex());
        fclose(yyin);
    #else
        #if YYDEBUG
            yydebug = 1;
        #endif
        yyparse(&program_root);
        fclose(yyin);
        analyse_tree(program_root);
    #endif
    yylex_destroy();
    return 0;
}




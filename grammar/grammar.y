%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "../include/defs.h"
#include "../include/common.h"



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
node_t make_node_floatval(float value);
node_t make_node_boolval(bool value);
node_t make_node_strval(char* string);

%}

%parse-param { node_t * program_root }

%union {
    int16_t intval;
    float floatval;
    char * strval;
    node_t ptr;
};

%type <intval> TOK_INTVAL;
%type <floatval> TOK_FLOATVAL;
%type <strval> TOK_IDENT TOK_STRING;

%token TOK_VOID TOK_INT TOK_INTVAL TOK_FLOAT TOK_FLOATVAL TOK_BOOL TOK_TRUE TOK_FALSE 
%token TOK_IDENT TOK_IF TOK_ELSE TOK_WHILE TOK_FOR TOK_PRINT
%token TOK_SEMICOL TOK_COMMA TOK_LPAR TOK_RPAR TOK_LACC TOK_RACC
%token TOK_STRING TOK_DO


%nonassoc TOK_THEN
%nonassoc TOK_ELSE 

%right TOK_AFFECT

%left TOK_OR
%left TOK_AND
%left TOK_BOR
%left TOK_BXOR
%left TOK_BAND
%left TOK_EQ TOK_NE
%nonassoc TOK_GT TOK_LT TOK_GE TOK_LE
%nonassoc TOK_SRL TOK_SRA TOK_SLL
/* a / b / c = (a / b) / c AND a - b - c = (a - b) - c */
%left TOK_PLUS TOK_MINUS
%left TOK_MUL TOK_DIV TOK_MOD
%nonassoc TOK_UMINUS TOK_NOT TOK_BNOT



%type <ptr> program listdecl listdeclnonnull vardecl ident type listtypedecl decl maindecl listinst listinstnonnull inst block expr listparamprint paramprint

%%

/* tree creation  */
program:    
        listdeclnonnull maindecl
        {
            $$ = make_node(NODE_PROGRAM, 2, $1, $2);
            *program_root = $$;
        }
        |
        listdeclnonnull
        {
            $$ = make_node(NODE_PROGRAM, 2, $1, NULL);
            *program_root = $$;
        }
        | maindecl
        {
            $$ = make_node(NODE_PROGRAM, 2, NULL, $1);
            *program_root = $$;
        }
        ;

listdecl:   listdeclnonnull
        {
            $$ = $1;
        }
        |
        {
            $$ = NULL;
        }
        ;

listdeclnonnull:vardecl
             { $$ = $1; }
            |
            listdeclnonnull vardecl
            {
                $$ = make_node(NODE_LIST, 2, $1, $2);
            }
            ;

vardecl    : type listtypedecl TOK_SEMICOL
            {
                $$ = make_node(NODE_DECLS, 2, $1, $2);
            }
            ;

type        : TOK_INT
        {
            $$ = make_node_type(TYPE_INT);
        }	
        | TOK_BOOL
        {
            $$ = make_node_type(TYPE_BOOL);
        }
        | TOK_FLOAT
        {
            $$ = make_node_type(TYPE_FLOAT);
        }
        | TOK_VOID
        {
            $$ = make_node_type(TYPE_VOID);
        }
        ;

listtypedecl    : decl
                {
                    $$ = $1;
                }
                | listtypedecl TOK_COMMA decl
                {
                    $$ = make_node(NODE_LIST, 2, $1, $3);
                }
                ;

decl        : ident
            {
                $$ = make_node(NODE_DECL, 2, $1, NULL);
            }
            | ident TOK_AFFECT expr
            {
                $$ = make_node(NODE_DECL, 2, $1, $3);
            }
            ;

maindecl        : type ident TOK_LPAR TOK_RPAR block
                {
                    $$ = make_node(NODE_FUNC, 3, $1, $2, $5);
                }
                ;

listinst        : listinstnonnull
                {
                    $$ =$1;
                }
                |
                {
                    $$ = NULL;
                }
                ;

listinstnonnull : inst
                {
                    $$ = $1;
                }
                | listinstnonnull inst
                {
                    $$ = make_node(NODE_LIST, 2, $1, $2);
                }
                ;

inst        : expr TOK_SEMICOL
            {
                $$ = $1;
            }
            | TOK_IF TOK_LPAR expr TOK_RPAR inst TOK_ELSE inst
            {
                $$ = make_node(NODE_IF, 3, $3, $5, $7);
            }
            | TOK_IF TOK_LPAR expr TOK_RPAR inst %prec TOK_THEN
            {
                $$ = make_node(NODE_IF, 2, $3, $5);
            }
            | TOK_WHILE TOK_LPAR expr TOK_RPAR inst
            {
                $$ = make_node(NODE_WHILE, 2, $3, $5);
            }
            | TOK_FOR TOK_LPAR expr TOK_SEMICOL expr TOK_SEMICOL expr TOK_RPAR inst
            {
                $$ = make_node(NODE_FOR, 4, $3, $5,$7 ,$9);
            }
            | TOK_DO inst TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SEMICOL
            {
                $$ = make_node(NODE_DOWHILE, 2, $2, $5);
            }
            | block
            {
                $$ = $1;
            }
            | TOK_SEMICOL
            {
                $$ = NULL;
            }
            | TOK_PRINT TOK_LPAR listparamprint TOK_RPAR TOK_SEMICOL
            {
                $$ = make_node(NODE_PRINT, 1, $3);
            }
            ;

block       : TOK_LACC listdecl listinst TOK_RACC
            {
                $$ = make_node(NODE_BLOCK, 2, $2, $3);
            }
            ;

expr        : expr TOK_MUL expr
            {
                $$ = make_node(NODE_MUL, 2, $1, $3);
            }
            | expr TOK_DIV expr
            {
                $$ = make_node(NODE_DIV, 2, $1, $3);
            }
            | expr TOK_PLUS expr
            {
                $$ = make_node(NODE_PLUS, 2, $1, $3);
            }
            | expr TOK_MINUS expr
            {
                $$ = make_node(NODE_MINUS, 2, $1, $3);
            }
            | expr TOK_MOD expr
            {
                $$ = make_node(NODE_MOD, 2, $1, $3);
            }
            | expr TOK_LT expr
            {
                $$ = make_node(NODE_LT, 2, $1, $3);
            }
            | expr TOK_GT expr
            {
                $$ = make_node(NODE_GT, 2, $1, $3);
            }
            | TOK_MINUS expr %prec TOK_UMINUS
            {
                $$ = make_node(NODE_UMINUS, 1, $2);
            }
            | expr TOK_GE expr
            {
                $$ = make_node(NODE_GE, 2, $1, $3);
            }
            | expr TOK_LE expr
            {
                $$ = make_node(NODE_LE, 2, $1, $3);
            }
            | expr TOK_EQ expr
            {
                $$ = make_node(NODE_EQ, 2, $1, $3);
            }
            | expr TOK_NE expr
            {
                $$ = make_node(NODE_NE, 2, $1, $3);
            }
            | expr TOK_AND expr
            {
                $$ = make_node(NODE_AND, 2, $1, $3);
            }
            | expr TOK_OR expr
            {
                $$ = make_node(NODE_OR, 2, $1, $3);
            }
            | expr TOK_BAND expr
            {
                $$ = make_node(NODE_BAND, 2, $1, $3);
            }
            | expr TOK_BOR expr
            {
                $$ = make_node(NODE_BOR, 2, $1, $3);
            }
            | expr TOK_BXOR expr
            {
                $$ = make_node(NODE_BXOR, 2, $1, $3);
            }
            | expr TOK_SRL expr
            {
                $$ = make_node(NODE_SRL, 2, $1, $3);
            }
            | expr TOK_SRA expr
            {
                $$ = make_node(NODE_SRA, 2, $1, $3);
            }
            | expr TOK_SLL expr
            {
                $$ = make_node(NODE_SLL, 2, $1, $3);
            }
            | TOK_NOT expr
            {
                $$ = make_node(NODE_NOT, 1, $2);
            }
            | TOK_BNOT expr
            {
                $$ = make_node(NODE_BNOT, 1, $2);
            }
            | TOK_LPAR expr TOK_RPAR
            {
                $$ = $2;
            }
            | ident TOK_AFFECT expr
            {
                $$ = make_node(NODE_AFFECT, 2, $1, $3);
            }
            | TOK_INTVAL
            {
                $$ = make_node_intval($1);
            }
            | TOK_FLOATVAL
            {
                $$ = make_node_floatval($1);
            }
            | TOK_TRUE
            {
                $$ = make_node_boolval(true);
            }
            | TOK_FALSE
            {
                $$ = make_node_boolval(false);
            }
            | ident
            {
                $$ = $1;
            }
            ;

listparamprint  : listparamprint TOK_COMMA paramprint
                {
                    $$ = make_node(NODE_LIST, 2, $1, $3);
                }
                | paramprint
                {
                    $$ = $1;
                }
                ;

paramprint      : ident
                {
                    $$ = $1;
                }
                | TOK_STRING{
                    $$ = make_node_strval($1);
                }
                ;

ident       : TOK_IDENT
            {
                $$ = make_node_ident($1);
            }
            ;

%%

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

node_t make_node_floatval(float value){
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
        // TODO AFTER PASSE 1
        // analyse_passe_1(root);
        // dump_tree(root, "apres_passe_1.dot");
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


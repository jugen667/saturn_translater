// ========================================
// > Author :   jugen 667 
// > Title  :   grammar.y 
// > Desc.  :   Node creation and tree   
//              creation 
// > Associated header : 
// ========================================

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include "../include/defs.h"
#include "../include/common.h"
#include "../include/passe_1.h"
#include "../include/passe_2.h"
// #include "../include/objects.h"



/* Global variables */
extern bool stop_after_syntax;
extern bool stop_after_verif;
extern bool verboseDebug;
extern char * outfile;
extern bool isPrio;

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
node_t make_node_main(node_t node_next);

%}

%parse-param { 
    node_t * program_root
}

%union {
    int64_t intval;
    double floatval; // double for accuracy
    char * strval;
    node_t ptr;
};

// data with variables values
%token <intval> TOK_INTVAL;
%token <floatval> TOK_FLOATVAL;
%token <strval> TOK_IDENT TOK_STRING;
// data types
%token TOK_VOID TOK_INT TOK_FLOAT TOK_BOOL
// data static values
%token TOK_TRUE TOK_FALSE 
// statements 
%token  TOK_IF TOK_ELSE TOK_WHILE TOK_FOR TOK_DO
// special tokens
%token TOK_MAIN TOK_PRINT TOK_SEMICOL TOK_COMMA TOK_LPAR TOK_RPAR TOK_LACC TOK_RACC
%nonassoc TOK_THEN
%nonassoc TOK_ELSE 

// operators
%right TOK_AFFECT

%left TOK_OR
%left TOK_AND
%left TOK_BOR
%left TOK_BXOR
%left TOK_BAND
%left TOK_EQ TOK_NE
%nonassoc TOK_GT TOK_LT TOK_GE TOK_LE
%nonassoc TOK_SRL TOK_SLL
/* a / b / c = (a / b) / c AND a - b - c = (a - b) - c */
%left TOK_PLUS TOK_MINUS
%left TOK_MUL TOK_DIV TOK_MOD
%nonassoc TOK_UMINUS TOK_NOT TOK_BNOT


%type <ptr> program listdecl vardecl ident type listtypedecl decl maindecl listinst inst block expr listparamprint paramprint list 

%%

/* tree creation rules  */
program:                list maindecl // case of inst 
                        {
                            $$ = make_node(NODE_PROGRAM, 2, $1, $2);
                            *program_root = $$;
                        }
                        |   maindecl
                        {
                            $$ = make_node(NODE_PROGRAM, 1, $1);
                            *program_root = $$;
                        }
                        | list 
                        {
                            printf(RED "Fatal error line" NC ": missing " BOLD CYAN "main()" NC " function\n");
                            exit(EXIT_FAILURE);
                        }
                        |
                        {
                            printf(RED "Fatal error " NC ": empty program\n");
                            exit(EXIT_FAILURE);
                        }
                        ;


listdecl:               vardecl
                        {
                            $$ = $1;
                        }
                        ;


vardecl                 : type listtypedecl TOK_SEMICOL
                        {
                            $$ = make_node(NODE_DECLS, 2, $1, $2);
                        }
                        ;

type                    : TOK_INT
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
                        ;


listtypedecl            : decl
                        {
                            $$ = $1;
                        }
                        | listtypedecl TOK_COMMA decl
                        {
                            $$ = make_node(NODE_LIST, 2, $1, $3);
                        }
                        |
                        {
                            printf(RED "Syntax error line " BOLD "%d" NC " : function name must be " BOLD CYAN "main()" NC " of type " BOLD PURPLE "void" NC " \n", yylineno);
                            exit(EXIT_FAILURE);
                        }
                        ;


decl                    :   ident
                        {
                            $$ = make_node(NODE_DECL, 2, $1, NULL);
                        }
                        
                        |   ident TOK_AFFECT expr
                        {
                            $$ = make_node(NODE_DECL, 2, $1, $3);
                        }
                        ;


maindecl                : TOK_VOID TOK_MAIN TOK_LPAR TOK_RPAR block // only valid main (modify to support functions)
                        {
                            $$ = make_node_main($5);
                        }
                        | TOK_VOID ident TOK_LPAR TOK_RPAR block
                        {
                            printf(RED "Syntax error" NC " : function name must be " BOLD CYAN "main()" NC " of type " BOLD PURPLE "void" NC " \n");
                            exit(EXIT_FAILURE);
                        }
                        ;


listinst                : inst
                        {
                            $$ =$1;
                        }
                        ;


inst                    : expr TOK_SEMICOL
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
                            $$ = make_node(NODE_DOWHILE, 2, $5, $2);
                        }
                        | block
                        {
                            $$ = $1;
                        }
                        | TOK_PRINT TOK_LPAR listparamprint TOK_RPAR TOK_SEMICOL
                        {
                            $$ = make_node(NODE_PRINT, 1, $3);
                        }
                        ;


list                    :   listdecl 
                        {
                            $$ = $1;
                        }
                        |   listinst 
                        {
                            $$ = $1;
                        }  
                        |   list listdecl
                        {
                            $$ = make_node(NODE_LIST, 2, $1, $2);
                        }
                        |   list listinst
                        {
                            $$ = make_node(NODE_LIST, 2, $1, $2);
                        }
                        ;


block                   :  TOK_LACC list TOK_RACC
                        {
                            $$ = make_node(NODE_BLOCK, 1, $2);
                        }
                        ;


expr                    : TOK_LPAR expr TOK_RPAR
                        {
                            // priority
                            $$ = make_node(NODE_PRIO, 1, $2);
                        }   
                        | expr TOK_MUL expr
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
                        | TOK_MINUS expr %prec TOK_UMINUS
                        {
                            $$ = make_node(NODE_UMINUS, 1, $2);
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

listparamprint          : listparamprint TOK_COMMA paramprint
                        {
                            $$ = make_node(NODE_LIST, 2, $1, $3);
                        }
                        | paramprint
                        {
                            $$ = $1;
                        }
                        ;
    

paramprint              : ident
                        {
                            $$ = $1;
                        }
                        | TOK_STRING
                        {
                            $$ = make_node_strval($1);
                        }
                        ;


ident                   : TOK_IDENT
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
    node->type = TYPE_NONE;
    node->value = 0;
    node->isPrio = 0;           // update passe 1
    va_start(ap, nops);

    node->opr = (node_t *) calloc(nops, sizeof(node_s)); // ensure every sub nodes are initialized

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
    node->type = TYPE_NONE;              // init but update in passe 1
    node->address = 0;                   // init but update in passe 1
    node->global_decl = false;           // init but update in passe 1
    node->opr = NULL;
    node->value = 0;
    node->isPrio = 0;                   // update passe 1
    return node;
}


node_t make_node_type(node_type type){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_TYPE;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = type;                  // init but update in passe 1
    node->address = 0;                  // init but update in passe 1
    node->global_decl = false;          // init but update in passe 1
    node->opr = NULL;
    node->value = 0;
    node->isPrio = 0;                   // update passe 1
    return node;
}


node_t make_node_intval(int32_t value){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_INTVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_NONE;              // init but update in passe 1
    node->address = 0;                  // init but update in passe 1
    node->global_decl = false;          // init but update in passe 1
    node->value = value;                // to update in passe1
    node->opr = NULL;
    node->isPrio = 0;                   // update passe 1
    return node;
}


node_t make_node_floatval(double value){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_FLOATVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_NONE;            // init but update in passe 1
    node->address = 0;                  // init but update in passe 1
    node->global_decl = false;          // init but update in passe 1
    node->value = value;                // to update in passe 1
    node->opr = NULL;
    node->isPrio = 0;                   // update passe 1
    return node;
}


node_t make_node_boolval(bool value){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_BOOLVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_NONE;             // init but update in passe 1
    node->address = 0;                  // init but update in passe 1
    node->global_decl = false;          // init but update in passe 1
    node->value = (uint64_t) value;
    node->opr = NULL;
    node->isPrio = 0;                   // update passe 1
    return node;
}


node_t make_node_strval(char* string){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_STRINGVAL;
    node->lineno = yylineno;
    node->nops = 0; 
    node->ident = NULL;
    node->type = TYPE_NONE;             // init but update in passe 1
    node->address = 0;                  // init but update in passe 1
    node->global_decl = false;          // maj dans passe 1
    node->str = string;
    node->opr = NULL;
    node->isPrio = 0;                   // update passe 1
    return node;
}


node_t make_node_main(node_t node_next){
    node_t node = (node_t) malloc(sizeof(node_s));
    node->nature = NODE_FUNC;
    node->lineno = yylineno;
    node->nops = 1; 
    node->ident = "main";
    node->type = TYPE_VOID;
    node->address = 0;                  // init but update in passe 1
    node->global_decl = true;      
    node->opr = (node_t *) malloc(sizeof(node_s)); // child block
    node->opr[0] = node_next;
    node->isPrio = 0;                   // update passe 1
    return node;
}


void analyse_tree(node_t root) {
    if(verboseDebug)
    {
        printf(BOLD "> Syntax analysis\n" NC);
    }    
    if(!disable_tree_dump)
    {
        dump_tree(root, "after_syntax.dot");
    }
    if (!stop_after_syntax) {
        if(verboseDebug)
        {
            printf(BOLD "> First parse\n" NC);
        } 
        analyse_passe_1(root);
        if(!disable_tree_dump)
        {
            dump_tree(root, "after_passe_1.dot");
        }
        if (!stop_after_verif)
        {
            outfileDescriptor = outfile_open(outfile);
            gen_code_passe_2(root);
            outfile_close(outfileDescriptor);
        }
        // free_global_strings();
    }
    free_nodes(root);
    if(verboseDebug)
    {
        printf(BOLD "> End of compilation\n" NC);
    }
}


/* Automatically called when error 
 * DON'T CALL IT : value given by yylineno won't be correct after syntaxe analysis
 */
void yyerror(node_t * program_root, char * s) {

    fprintf(stderr, NC BOLD RED "Error line %d : " NC RED "%s\n" NC, yylineno, s);
    exit(1);
}


// ========================================
// > Author :   jugen 667 
// > Title  :   common.c
// > Desc.  :   Compiler options parsing   
//              and utils functions 
// > Associated header : common.h
// ========================================

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <unistd.h>
#include <getopt.h>

#include "../include/defs.h"
#include "../include/common.h"
#include "../include/arch.h"

#define     MAIN_VERSION    "0"                 /*dev phase*/
#define     SUB_VERSION     "1"                 /*first iteration*/

#define     NC              "\e[0m"
#define     BLACK           "\033[30m"          /* Black */
#define     RED             "\033[31m"          /* Red */
#define     GREEN           "\033[32m"          /* Green */
#define     YELLOW          "\033[33m"          /* Yellow */
#define     BLUE            "\033[34m"          /* Blue */
#define     WHITE           "\033[37m"          /* White */
#define     BOLD            "\033[1m"           /* Bold */
#define     BOLDWHITE       "\033[1m\033[37m"   /* Bold White */

extern char * infile;
extern char * outfile;
int trace_level = DEFAULT_TRACE_LEVEL;
extern bool stop_after_syntax;
extern bool stop_after_verif;
bool uncompatible=0;

void print_version(){
    printf("\n");
    printf(BOLD "-------------------- SaturnCC --------------------\n" NC);
    printf("\n");
    printf(BOLD "Translater for simplified C to Saturn HP assembly\n" NC);
    printf(BOLD "Build Version :" NC "v%s.%s\r\n", MAIN_VERSION, SUB_VERSION);
    printf(BOLD "Github link : " NC "https://github.com/jugen667/saturn_translater\n");
    printf("\n");
    printf(BOLD "--------------------------------------------------\n" NC);
    printf("\n");
}


void affiche_help(){
    printf("\n");
	printf(BOLD "Help page Saturncc \n\n" NC);
	printf(BOLD "Translater for simplified C to Saturn HP assembly\n" NC);
    printf("Usage : ./saturncc <options> <infile>\n\n");
	printf("  -o <filename> : Custom output filename\n\t(default : out.s)\n");
	printf("  -t <int> : Trace level between 0 and 5 \n\t(0 = no trace ; 5 = alltraces) (default = 0)\n");
	printf("  -r <int> : Max register to use\n\tbetween 1 and 5 (default : 5)\n");
	printf("  -s : Stop translation after syntax check \n\t(default = no)\n");
	printf("  -c : Stop translation after first phase\n\t(default = no)\n");
	printf("  -h : Print help\n");
    printf("  -v : Print build version of SaturnCC\n\n");
}

void test_int_value(int min, int max, int test, char * argv ){
	if (test > max || test < min){
		fprintf(stderr,NC"value %d out of range for option %s\n",test, argv);
        if (argv[1] == 'r'){
            fprintf(stderr,NC"\t-> value must be between 1 and 5\n");
        }
        else if (argv[1] == 't'){
            fprintf(stderr,NC"\t-> value must be between 0 and 5\n");
        }
		exit(1);	
	}
}

void testValideInFile(char * test){
    int i=0;
    i = strlen(test);
    if (strstr(&test[i-2],".c") == NULL ){
        fprintf(stderr,NC"unvalid file name : %s\n",test);
        exit(1);    
    }
}

void testValideOutFile(char * test){
    int i=0;
    i = strlen(test);
    if (strstr(&test[i-2],".s") == NULL ){
        fprintf(stderr,NC"unvalid file name : %s\n",test);
        exit(1);    
    }
}

void test_arg_compatibility(char *arg_1, char *arg_2, char *test){
	if((strcmp(test, arg_1) || strcmp(test, arg_2)) && uncompatible == 0){
		uncompatible = 1;
	}
	else if((strcmp(test,arg_1) || strcmp(test,arg_2)) && uncompatible == 1){
		fprintf(stderr,NC"uncompatible options  : %s and %s \n", arg_1, arg_2);
		exit(1);
	}
}

void parse_args(int argc, char ** argv) {
	infile = NULL;
    for (int i=1; i<argc; i++){
    	if (argv[i][0] != '-'){
            testValideInFile(argv[i]);
            infile = argv[i];
            //printf("Infile %s \n",argv[i]);
    	}
    	else{
    		if (argv[i][2] == '\0'){
				switch (argv[i][1]){
					case 'o':
						testValideOutFile(argv[i+1]);
						outfile = argv[i+1];
						//printf("output file name : %s \n", outfile);
						i++;
						break;
					case 't':
						test_int_value(0,5,atoi(argv[i+1]), argv[i]);
						trace_level = atoi(argv[i+1]);
						i++;
						break;
					case 'r':
						test_int_value(1,5,atoi(argv[i+1]), argv[i]);
						set_max_registers(atoi(argv[i+1]));
						i++;
						break;
					case 's':
						test_arg_compatibility("-s","-c",argv[i]);
						stop_after_syntax = 1;
						break;
					case 'c':
						test_arg_compatibility("-s","-c",argv[i]);
						stop_after_verif = 1;
						//printf("arrêt après la phase de vérification \n");
						break;
                    case 'v':
                        print_version();
                        exit(1);
                        break;
                    case 'h':
                        affiche_help();
                        exit(1);
                        break;
					default:
						fprintf(stderr,NC "%s is not a valid option\n", argv[i]);
                        fprintf(stderr,NC "Show helps with \"saturncc -h\"\n");
						exit(1);
						break;
				}
			}
		}
    }
	if (infile == NULL){
		fprintf(stderr,NC "No .c file to translate \n\n");
		exit(1);
	}
}


void free_nodes(node_t n) {
    // TO DO
    // input : root node 
    // Parse until no more node
    // come back and free nodes
}


char * strdupl(char * s) {
    // TO CHANGE (MEMORY LEAK INCOMING) = Limit string size
    char * r = malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}


// === DOT FILE CREATION ===

static int32_t dump_tree2dot_rec(FILE * f, node_t n, int32_t node_num) {

    if (n == NULL) {
        fprintf(f, "    N%d [shape=record, label=\"{{NULL}}\"];\n", node_num);
        return node_num;
    }

    switch (n->nature) {
        case NODE_IDENT:
            {
                node_t decl_node = n->decl_node;
                fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{<decl>Decl      |Ident: %s|Offset: %d}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->ident, n->offset);
                if (decl_node != NULL && decl_node != n) {
                    fprintf(f, "    edge[tailclip=false];\n");
                    fprintf(f, "    \"N%d\":decl:c -> \"N%d\" [style=dashed]\n", node_num, decl_node->node_num);
                }
                break;
            }
        case NODE_INTVAL:
        case NODE_BOOLVAL:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{Value: %d}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->int_value);
            break;
        case NODE_FLOATVAL:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{Value: %f}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->float_value);
            break;
        case NODE_STRINGVAL:
            {
                char str[32];
                int32_t i = 1;
                while (true) {
                    str[i - 1] = n->str[i];
                    i += 1;
                    if (n->str[i] == '"') {
                        str[i - 1] = '\0';
                        break;
                    }
                }
                fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{val: %s}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), str);
            }
            break;
        case NODE_TYPE:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type));
            break;
        case NODE_LIST:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE LIST}}\"];\n", node_num);
            break;
        case NODE_PROGRAM:
        case NODE_BLOCK:
        case NODE_DECLS:
        case NODE_DECL:
        case NODE_IF:
        case NODE_WHILE:
        case NODE_FOR:
        case NODE_DOWHILE:
        case NODE_PRINT:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Nb. ops: %d}}\"];\n", node_num, node_nature2string(n->nature), n->nops);
            break;
        case NODE_FUNC:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Nb. ops: %d}|{offset: %d}}\"];\n", node_num, node_nature2string(n->nature), n->nops, n->offset);
            break;
        case NODE_PLUS:
        case NODE_MINUS:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD:
        case NODE_LT:
        case NODE_GT:
        case NODE_LE:
        case NODE_GE:
        case NODE_EQ:
        case NODE_NE:
        case NODE_AND:
        case NODE_OR:
        case NODE_BAND:
        case NODE_BOR:
        case NODE_BXOR:
        case NODE_SRA:
        case NODE_SRL:
        case NODE_SLL:
        case NODE_NOT:
        case NODE_BNOT:
        case NODE_UMINUS:
    	case NODE_ELSE:
    	case NODE_AFFECT:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s|Nb. ops: %d}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->nops);
            break;
	default:
            printf("*** Error in %s: unknown nature : %s\n", __func__, node_nature2string(n->nature));
            assert(false);
    }

    n->node_num = node_num;

    int32_t curr_node_num = node_num + 1;
    for (int32_t i = 0; i < n->nops; i += 1) {
        int32_t new_node_num = dump_tree2dot_rec(f, n->opr[i], curr_node_num);

        fprintf(f, "    edge[tailclip=true];\n");
        fprintf(f, "    N%d -> N%d\n", node_num, curr_node_num);
        curr_node_num = new_node_num + 1;
    }

    return curr_node_num - 1;
}



static void dump_tree2dot(FILE * f, node_t root) {
    assert(root->nature == NODE_PROGRAM);

    int32_t curr_node_num = 1;
    dump_tree2dot_rec(f, root, curr_node_num);
}


void dump_tree(node_t prog_root, const char * dotname) {

    FILE * f;

    f = fopen(dotname, "w");
    fprintf(f, "digraph global_vars {\n");
    dump_tree2dot(f, prog_root);
    fprintf(f, "}");    
    fclose(f);
}


const char * node_type2string(node_type t) {
    switch (t) {
        case TYPE_NONE:
            return "TYPE NONE";
        case TYPE_INT:
            return "TYPE INT";
        case TYPE_BOOL:
            return "TYPE BOOL";
        case TYPE_FLOAT:
            return "TYPE FLOAT";
        case TYPE_VOID:
            return "TYPE VOID";
        default:
            assert(false);
    }
}


const char * node_nature2string(node_nature t) {
    switch (t) {
        case NONE:
            return "NONE";
        case NODE_PROGRAM:
            return "PROGRAM";
        case NODE_BLOCK:
            return "BLOCK";
        case NODE_LIST:
            return "LIST";
        case NODE_DECLS:
            return "DECLS";
        case NODE_DECL:
            return "DECL";
        case NODE_IDENT:
            return "IDENT";
        case NODE_TYPE:
            return "TYPE";
        case NODE_INTVAL:
            return "INTVAL";
        case NODE_FLOATVAL:
            return "FLOATVAL";
        case NODE_BOOLVAL:
            return "BOOLVAL";
        case NODE_STRINGVAL:
            return "STRINGVAL";
        case NODE_FUNC:
            return "FUNC";
        case NODE_IF:
            return "IF";
        case NODE_WHILE:
            return "WHILE";
        case NODE_FOR:
            return "FOR";
        case NODE_DOWHILE:
            return "DOWHILE";
        case NODE_PLUS:
            return "PLUS";
        case NODE_MINUS:
            return "MINUS";
        case NODE_MUL:
            return "MUL";
        case NODE_DIV:
            return "DIV";
        case NODE_MOD:
            return "MOD";
        case NODE_LT:
            return "LT";
        case NODE_GT:
            return "GT";
        case NODE_LE:
            return "LE";
        case NODE_GE:
            return "GE";
        case NODE_EQ:
            return "EQ";
        case NODE_NE:
            return "NE";
        case NODE_AND:
            return "AND";
        case NODE_OR:
            return "OR";
        case NODE_BAND:
            return "BAND";
        case NODE_BOR:
            return "BOR";
        case NODE_BXOR:
            return "BXOR";
        case NODE_SLL:
            return "SLL";
        case NODE_SRA:
            return "SRA";
        case NODE_SRL:
            return "SRL";
        case NODE_NOT:
            return "NOT";
        case NODE_BNOT:
            return "BNOT";
        case NODE_UMINUS:
            return "UMINUS";
        case NODE_AFFECT:
            return "AFFECT";
        case NODE_PRINT:
            return "PRINT";
    	case NODE_ELSE:
    	    return "ELSE";
    	default:
            fprintf(stderr, "*** Error in %s: Unknown node nature: %d\n", __func__, t);
            exit(1);
    }
}




const char * node_nature2symb(node_nature t) {
    switch (t) {
        case NONE:
        case NODE_PLUS:
            return "+";
        case NODE_MINUS:
            return "-";
        case NODE_MUL:
            return "*";
        case NODE_DIV:
            return "/";
        case NODE_MOD:
            return "%";
        case NODE_LT:
            return "<";
        case NODE_GT:
            return ">";
        case NODE_LE:
            return "<=";
        case NODE_GE:
            return ">=";
        case NODE_EQ:
            return "==";
        case NODE_NE:
            return "!=";
        case NODE_AND:
            return "&&";
        case NODE_OR:
            return "||";
        case NODE_BAND:
            return "&";
        case NODE_BOR:
            return "|";
        case NODE_BXOR:
            return "^";
        case NODE_SRA:
            return ">>";
        case NODE_SRL:
            return ">>>";
        case NODE_SLL:
            return "<<";
        case NODE_NOT:
            return "!";
        case NODE_BNOT:
            return "~";
        case NODE_UMINUS:
            return "-";
        default:
            fprintf(stderr, "*** Error in %s: Unknown node nature: %d\n", __func__, t);
            exit(1);
    }
}





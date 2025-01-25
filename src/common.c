// ========================================
// > Author :   jugen 667 
// > Title  :   common.c
// > Desc.  :   Compiler options parsing   
//              and utils functions 
// > Associated header : common.h
// ========================================

// ================================================================================================= //
// =========================================== INCLUDES ============================================ //
// ================================================================================================= //

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/defs.h"
#include "../include/common.h"
#include "../include/passe_1.h"
#include "../include/passe_2.h"


// ================================================================================================= //
// =========================================== GLOBALS ============================================= //
// ================================================================================================= //
static uint32_t current_address = MIN_ADDRESS; // init at base address
extern char * infile;
extern char * outfile;
extern bool stop_after_syntax;
extern bool stop_after_verif;
FILE * outfileDescriptor = NULL;
bool verboseDebug = 0;
short target = 48;
short disable_tree_dump = 1;
bool uncompatible=0;

// ================================================================================================= //
// =========================================== FUNCTIONS =========================================== //
// ================================================================================================= //

void print_version()
{
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

// ------------------------------------------------------------------------------------------------- //

void affiche_help()
{
    printf("\n");
	printf(BOLD "Help page Saturncc \n\n" NC);
	printf(BOLD "Translater for simplified C to Saturn HP assembly\n" NC);
    printf("Usage : ./saturncc <options> <infile>\n\n");
	printf("  -o <filename> : Custom output filename\n\t(default : out.s)\n");
	printf("  -s : Stop translation after syntax check \n\t(default = no)\n");
	printf("  -c : Stop translation after first phase\n\t(default = no)\n");
    printf("  -t : Define compilation target (HP-48 or HP-49)\n\t(default=48)\n");
    printf("  -a : Enable the tree dumping in a file\n\t(default=on)");
    printf("  -d : Activate verbose compilation\n");
	printf("  -h : Print help\n");
    printf("  -v : Print build version of SaturnCC\n\n");
}

// ------------------------------------------------------------------------------------------------- //

void test_int_value(int min, int max, int test, char * argv )
{
	if (test > max || test < min)
    {
		fprintf(stderr,NC"value %d out of range for option %s\n",test, argv);
        if (argv[1] == 't')
        {
            fprintf(stderr,NC"\t > value must be 48 or 49\n");
        }
		exit(EXIT_FAILURE);	
	}
}

// ------------------------------------------------------------------------------------------------- //

void testValideInFile(char * test)
{
    int i=0;
    i = strlen(test);
    if (strstr(&test[i-2],".c") == NULL )
    {
        fprintf(stderr,RED BOLD "unvalid file name : %s\n" NC,test);
        exit(EXIT_FAILURE);    
    }
}

// ------------------------------------------------------------------------------------------------- //

void testValideOutFile(char * test)
{
    int i=0;
    i = strlen(test);
    if (strstr(&test[i-2],".s") == NULL )
    {
        fprintf(stderr,RED BOLD"unvalid file name : %s\n" NC,test);
        exit(EXIT_FAILURE);    
    }
}

// ------------------------------------------------------------------------------------------------- //

void test_arg_compatibility(char *arg_1, char *arg_2, char *test)
{
	if((strcmp(test, arg_1) || strcmp(test, arg_2)) && uncompatible == 0)
    {
		uncompatible = 1;
	}
	else if((strcmp(test,arg_1) || strcmp(test,arg_2)) && uncompatible == 1)
    {
		fprintf(stderr,BOLD "uncompatible options  : %s and %s \n" NC, arg_1, arg_2);
		exit(EXIT_FAILURE);
	}
}

// ------------------------------------------------------------------------------------------------- //

void parse_args(int argc, char ** argv) 
{
	infile = NULL;
    for (int i=1; i<argc; i++)
    {
    	if (argv[i][0] != '-')
        {
            testValideInFile(argv[i]);
            infile = argv[i];
    	}
    	else
        {
    		if (argv[i][2] == '\0')
            {
				switch (argv[i][1])
                {
					case 'o':
						testValideOutFile(argv[i+1]);
						outfile = argv[i+1];
						i++;
					break;
                    case 'a':
                        disable_tree_dump = 0;
                        printf(BOLD "Compilation tree will be dumped\n" NC);
                        printf(BOLD ".dot files will be created\n" NC);
                    break;
					case 't':
						test_int_value(48,49,atoi(argv[i+1]), argv[i]);
                        target = atoi(argv[i+1]);
                        printf(BOLD "Compilation target : HP-%d series\n" NC, target);
						i++;
					break;
					case 's':
						test_arg_compatibility("-s","-c",argv[i]);
						stop_after_syntax = 1;
					break;
					case 'c':
						test_arg_compatibility("-s","-c",argv[i]);
						stop_after_verif = 1;
					break;
                    case 'v':
                        print_version();
                        exit(EXIT_SUCCESS);
                    break;
                    case 'h':
                        affiche_help();
                        exit(EXIT_SUCCESS);
                    break;
                    case 'd':
                        verboseDebug = 1;
                        printf(BOLD "Compilation will be verbose\n" NC);
                    break;
					default:
						fprintf(stderr,RED BOLD "%s is not a valid option\n" NC, argv[i]);
                        fprintf(stderr,BOLD "Show helps with \"saturncc -h\"\n" NC);
						exit(EXIT_FAILURE);
					break;
				}
			}
		}
    }
	if (infile == NULL)
    {
		fprintf(stderr,RED BOLD "No .c file to translate\n" NC);
		exit(EXIT_FAILURE);
	}
}

// ------------------------------------------------------------------------------------------------- //

void free_nodes(node_t n) 
{
    // input : root node 
    // Parse until no more node
    // come back and free nodes
    short currnops;
    if((n->nature == NODE_PROGRAM) && verboseDebug)
    {
        printf(BOLD "> Freeing nodes\n" NC);
    }
    if(n->nops != 0)
    {   
        for(int i = 0; i<n->nops; i++){
            if(n->opr[i] != NULL)
            {
                free_nodes(n->opr[i]);
            }
        }
        if(verboseDebug)
        {
            printf("\t > freeing %s\n", node_nature2string(n->nature));
        }
        free(n->opr); // free the pointer to sub nodes
        free(n);
    }
    else
    {
        if(verboseDebug)
        {
            printf("\t > freeing %s\n", node_nature2string(n->nature));
        }     
        if(n->nature == NODE_IDENT)
        {
            free(n->ident); // free the pointer identifier string
        }
        if(n->nature == NODE_STRINGVAL)
        {
            free(n->str); // free the pointer string value
        }
        free(n);
    }
}

// ------------------------------------------------------------------------------------------------- //

char * strdupl(char * s) 
{
    // TO CHANGE (MEMORY LEAK INCOMING) = Limit string size
    char * r = malloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}

// ------------------------------------------------------------------------------------------------- //

// === DOT FILE CREATION ===
static int32_t dump_tree2dot_rec(FILE * f, node_t n, int32_t node_num) 
{

    if (n == NULL) 
    {
        fprintf(f, "    N%d [shape=record, label=\"{{NULL}}\"];\n", node_num);
        return node_num;
    }

    switch (n->nature) 
    {
        case NODE_IDENT:
            {
                fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{<decl>Global: %d|Ident: %s|address: %05X}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->global_decl, n->ident, n->address);
                break;
            }
        case NODE_INTVAL:
        case NODE_BOOLVAL:
        case NODE_FLOATVAL:
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{Value: %ld}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->value);
            break;
        case NODE_STRINGVAL:
            {
                char str[32];
                int32_t i = 1;
                while (true) {
                    str[i - 1] = n->str[i];
                    i += 1;
                    if (n->str[i] == '"') 
                    {
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
            fprintf(f, "    N%d [shape=record, label=\"{{NODE %s|Type: %s}|{Ident: %s|Nb. ops: %d}|{address: %05X}}\"];\n", node_num, node_nature2string(n->nature), node_type2string(n->type), n->ident, n->nops, n->address);
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
        break;

    }

    n->node_num = node_num;

    int32_t curr_node_num = node_num + 1;
    for (int32_t i = 0; i < n->nops; i += 1) 
    {
        int32_t new_node_num = dump_tree2dot_rec(f, n->opr[i], curr_node_num);
        fprintf(f, "    edge[tailclip=true];\n");
        fprintf(f, "    N%d -> N%d\n", node_num, curr_node_num);
        curr_node_num = new_node_num + 1;
    }

    return curr_node_num - 1;
}

// ------------------------------------------------------------------------------------------------- //

static void dump_tree2dot(FILE * f, node_t root) 
{
    if(root->nature == NODE_PROGRAM)
    {
        int32_t curr_node_num = 1;
        dump_tree2dot_rec(f, root, curr_node_num);
    }
    else
    {
        printf(RED "Fatal error" NC " : root node not a NODE_PROGRAM but %s\n",node_nature2string(root->nature));
        exit(EXIT_FAILURE);
    }

    
}

// ------------------------------------------------------------------------------------------------- //

void dump_tree(node_t prog_root, const char * dotname) 
{

    FILE * f;

    f = fopen(dotname, "w");
    fprintf(f, "digraph global_vars {\n");
    dump_tree2dot(f, prog_root);
    fprintf(f, "}");    
    fclose(f);
}

// ------------------------------------------------------------------------------------------------- //

const char * node_type2string(node_type t) 
{
    switch (t) 
    {
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
            return "";
        break;
    }
}

// ------------------------------------------------------------------------------------------------- //

const char * node_nature2string(node_nature t) 
{
    switch (t) 
    {
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
            return "IF\t"; // \t for debug
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
            return "LT\t"; // \t for debug
        case NODE_GT:
            return "GT\t"; // \t for debug
        case NODE_LE:
            return "LE\t"; // \t for debug
        case NODE_GE:
            return "GE\t"; // \t for debug 
        case NODE_EQ:
            return "EQ\t"; // \t for debug
        case NODE_NE:
            return "NE\t"; // \t for debug
        case NODE_AND:
            return "AND";
        case NODE_OR:
            return "OR\t"; // \t for debug
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
            exit(EXIT_FAILURE);
    }
}

// ------------------------------------------------------------------------------------------------- //

const char * node_nature2symb(node_nature t) 
{
    switch (t) 
    {
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
            exit(EXIT_FAILURE);
    }
}

// ------------------------------------------------------------------------------------------------- //

// =================== Useful functions =================== //
// not that useful I dont either it exist or not
short extract_sign(void * value)
{
    if (*(short*)value < 0 || *(float*)value < 0)
    {
        return 1;           // negative
    }
    else
    {
        return 0;           // positive
    }
}

// not precise floating past 5 decimal points
short extract_exponent(double value)
{
    short i=0;
    if (value < 0)
    {
        value *= -1;
    }
    value = value - (int) value;
    while(value - (int) value >= 0.000001  && i < 256)
    {
        value *= 10;
        printf("value - int = %lf| i= %d\n", value - (int) value,i);
        printf("value = %lf| i= %d\n", value,i);
        i++;
    }
    return i;
}

// convert to BCD (useful for real numbers)
int decimal2BCD(int value)
{
    int result = 0;
    int shift = 0;
    if (value < 0)
    {
        value *= -1;
    }
    while(value > 0)
    {
        result |= (value % 10) << (shift++ << 2);
        value /= 10;
    }
    return result;
}

// assign an address to a node (maybe the most useful func here)
uint32_t assign_address(void)
{
    current_address+=0x20;
    if(current_address >= MAX_PRACTICAL_ADDRESS)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        return(current_address);
    }
}

// ------------------------------------------------------------------------------------------------- //

// =================== Outfile dumping functions =================== //
// open file
FILE * outfile_open(char * outfileName)
{
    FILE * f;
    if(verboseDebug){
        printf(BOLD "> Creating and opening file : %s\n" NC, outfile);
    }
    f = fopen(outfileName, "w");
    if(f != NULL){
        fprintf(f, "%% Source file name : %s\n", infile);
        fprintf(f, "%% Compiled with saturn_translater\n");
        fprintf(f, "%% Target of this program : HP-%d series\n", target);
        fprintf(f, "%% https://github.com/jugen667/saturn_translater\n");
        fprintf(f, "\n\n");
        if(verboseDebug)
        {
            printf(BOLD "\t > %s created and opened\n" NC, outfile);
        }
    }
    else{
        printf(RED "Fatal error : " NC "could not open/create file %s\n", outfile);
        printf(BOLD GREEN "Printing program in stdout\n" NC);
    }
    return f;
}

// close file
void outfile_close(FILE * fileDesc)
{
    if(fileDesc != NULL)
    {
        fprintf(fileDesc, "\n%% End of File \n\n");
        fclose(fileDesc);
        if(verboseDebug)
        {
            printf(BOLD "\t > %s closed\n" NC, outfile);
        }
    }
}

// ------------------------------------------------------------------------------------------------- //


// ================================================================================================= //
// ================================================================================================= //
// ================================================================================================= //

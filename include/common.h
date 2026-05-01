// ========================================
// > Author :   jugen 667 
// > Title  :   common.h 
// > Desc.  :   Header for common.c
//				All utils and globals for 
// 				the executable are defined 
//				in this header
// ========================================

#ifndef _COMMON_H_
#define _COMMON_H_

// ================================================================================================= //
// =========================================== DEFINES ============================================= //
// ================================================================================================= //
#define 	DEFAULT_OUTFILE "out.s"

#define     MAIN_VERSION    "0"                 /*dev phase*/
#define     SUB_VERSION     "7"                 /*iteration*/

// ============== LOGGING =================	\\
// > v0.1 : first iteration = start		 	\\	
// > v0.2 : final dev architecture 		 	\\
// > v0.3 : basic operations support		\\
// > v0.4 : if else integration finished	\\
// > v0.5 : while integration finished		\\
// > v0.6 : for integration finished		\\
// > v0.7 : optimizations and fixes			\\
// > v0.8 : compîler enhancements			\\
// > v1.0 : first release					\\
// > v1.x : test on machine + corrections	\\
// ========================================	\\

#define     NC              "\e[0m"
#define     BLACK           "\033[30m"          /* Black */
#define     RED             "\033[31m"          /* Red */
#define     GREEN           "\033[32m"          /* Green */
#define     YELLOW          "\033[33m"          /* Yellow */
#define     BLUE            "\033[34m"          /* Blue */
#define     PURPLE          "\033[35m"          /* Purple */
#define     CYAN          	"\033[36m"          /* Cyan */
#define     WHITE           "\033[37m"          /* White */
#define     BOLD            "\033[1m"           /* Bold */

extern bool 	g_verboseDebug;
extern short 	g_target;
extern bool 	g_disableTreeDump;
extern FILE * 	g_outfileDescriptor;
extern char * 	g_outfile;
extern char *   g_infile;

#define OPTION_START 		'-'
#define OPTION_DEBUG 		'd'
#define OPTION_VERSION 		'v'
#define OPTION_TREE_DUMP 	'a'
#define OPTION_HELP 		'h'
#define OPTION_OUTPUT 		'o'
#define OPTION_TARGET 		't'



// ================================================================================================= //
// ========================================== PROTOTYPE ============================================ //
// ================================================================================================= //

void parse_args(int argc, char ** argv);
void free_nodes(node_t n);
char * strdupl(char * s);
void dump_tree(node_t prog_root, const char * filename);
const char * node_type2string(node_type t);
const char * node_nature2string(node_nature t);
const char * node_nature2symb(node_nature t);
void print_node_info(node_t root);

short extract_sign(void * value);
short extract_exponent(double value);
int decimal2BCD(int value);

uint32_t assign_address(void);

// open file
FILE * outfile_open(char * outfileName);
void outfile_close(FILE * fileDesc);
void dump_instruction(char * inst, FILE * fDest);

// NODE MAKING FUNCTIONS
int yylex(void);
extern int yylineno;

void yyerror(node_t * program_root, char * s);
node_t make_node(node_nature nature, int nops, ...);
node_t make_node_special_affect(node_nature nature, char * ident, node_t expr);
node_t make_node_ident(char* identifier);
node_t make_node_type(node_type type);
node_t make_node_intval(int32_t value);
node_t make_node_floatval(double value);
node_t make_node_boolval(bool value);
node_t make_node_strval(char* string);
node_t make_node_main(node_t node_next);


// FUNCTION THAT RUN THE PARSING, CHECKS AND TRANSLATION
void run_translation(node_t root);


#endif


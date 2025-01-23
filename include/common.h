// ========================================
// > Author :   jugen 667 
// > Title  :   common.h 
// > Desc.  :   Header for common.c
// ========================================

#ifndef _COMMON_H_
#define _COMMON_H_

// ================================================================================================= //
// =========================================== DEFINES ============================================= //
// ================================================================================================= //
#define DEFAULT_OUTFILE "out.s"
#define DEFAULT_TRACE_LEVEL 0

#define     MAIN_VERSION    "0"                 /*dev phase*/
#define     SUB_VERSION     "1"                 /*iteration*/

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
#define     BOLDWHITE       "\033[1m\033[37m"   /* Bold White */

extern bool verboseDebug;
extern short target;
extern short disable_tree_dump;
extern FILE * outfileDescriptor;

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

short extract_sign(void * value);
short extract_exponent(double value);
int decimal2BCD(int value);

uint32_t assign_address(void);

// open file
FILE * outfile_open(char * outfileName);
void outfile_close(FILE * fileDesc);


#endif


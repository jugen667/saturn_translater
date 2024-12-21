// ========================================
// > Author :   jugen 667 
// > Title  :   passe_1.h 
// > Desc.  :   Header for the first parse
// ========================================

#ifndef _PASSE_1_
#define _PASSE_1_

#include "../include/defs.h"

// DEBUG FUNCTIONS
void print_decl_table(void);
void print_node_info(node_t root);

// CHECKUP FUNCTIONS
node_t get_decl_node(node_t node);
void change_int2float(node_t node, double value);
bool check_var_number(void);
void check_ident_size(node_t node);
void check_int_op_type(node_t node);
void check_bool_cond(node_t node, int positionnal);
void check_affect_type(node_t node);
void check_global_decl(node_t node);
void check_intval_domain(node_t node);

void analyse_passe_1(node_t root);
#endif

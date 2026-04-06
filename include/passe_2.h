// ========================================
// > Author :   jugen 667 
// > Title  :   passe_2.h 
// > Desc.  :   Header for the second parse
// ========================================

#ifndef _PASSE_2_H_
#define _PASSE_2_H_

#include "../include/defs.h"


void create_new_label(unsigned int index);
char * get_label(unsigned int index);

void manage_priority(node_t node, int position);
void decl_inblock(node_t node);
void affect_variable(node_t node);

void create_uminus_instr(node_t node);
void create_bnot_instr(node_t node);
void create_raw_op(node_t node);
void create_raw_not_op(node_t node);
void create_operation(node_t node);
void create_NOT_operation(node_t node);

void create_sll_instr(node_t node); // prototype only not implemented
void create_srl_instr(node_t node); // prototype only not implemented

void gen_code_passe_2(node_t root);
void create_cond_instruction(node_t node, node_t root, unsigned int loc_label, int statement);

#endif

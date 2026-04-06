// ========================================
// > Author :   jugen 667 
// > Title  :   passe_2.h 
// > Desc.  :   Header for the second parse
// ========================================

#ifndef _PASSE_2_H_
#define _PASSE_2_H_

#include "../include/defs.h"

#define LABEL_STR_SIZE 	16
#define MAX_LABEL_AMT	65535 // max int

typedef struct
{
	char labelStr[LABEL_STR_SIZE];
}label_string;



void gen_code_passe_2(node_t root);

void manage_priority(node_t node, int position);
void decl_inblock(node_t node);
void create_uminus_instr(node_t node);

void create_operation(node_t node);
void create_NOT_operation(node_t node);
void create_bnot_instr(node_t node);
void create_sll_instr(node_t node);
void create_srl_instr(node_t node);

void create_cond_instruction(node_t node, node_t root, unsigned int loc_label, int statement);

#endif

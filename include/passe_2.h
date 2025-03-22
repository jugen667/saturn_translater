// ========================================
// > Author :   jugen 667 
// > Title  :   passe_2.h 
// > Desc.  :   Header for the second parse
// ========================================

#ifndef _PASSE_2_H_
#define _PASSE_2_H_

#include "../include/defs.h"

void gen_code_passe_2(node_t root);

void decl_inblock(node_t node);
void affect_variable(node_t node);

void create_operation(node_t node);
void manage_priority(node_t node, int position);

void create_lt_instr(node_t node);
void create_le_instr(node_t node);
void create_eq_instr(node_t node);
void create_neq_instr(node_t node);
void create_gt_instr(node_t node);
void create_ge_instr(node_t node);
void create_plus_instr(node_t node);
void create_minus_instr(node_t node);
void create_uminus_instr(node_t node);
void create_mul_instr(node_t node);
void create_div_instr(node_t node);
void create_mod_instr(node_t node);
void create_band_instr(node_t node);
void create_bor_instr(node_t node);
void create_bnot_instr(node_t node);
void create_bxor_instr(node_t node);
void create_sll_instr(node_t node);
void create_srl_instr(node_t node);
void create_not_instr(node_t node);

#endif

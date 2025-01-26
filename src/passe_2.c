// ========================================
// > Author :   jugen 667 
// > Title  :   passe_2.c 
// > Desc.  :   Second parse to generate
//				assembly code
// > Associated header : passe_2.h
// ========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defs.h"
#include "../include/common.h"
#include "../include/passe_2.h"
#include "../include/instruction_set.h"


// global utility variables
int launch = 1;
int label = 0;
char labelStr[16];
int inFunc_Decl = 0;
int inBlockFunc = 0;
int parsingLoopFor = 0;
int parsingLoopWhile = 0;
int parsingLoopIf = 0;
int parsingLoopDo = 0;
int inLoopFor = 0;
int inLoopWhile = 0;
int current_reg;
int jmpLabelDecl = 0;
int blockParsed = 0;
int inLoopDo = 0;
int inIf = 0;


/* --------------- Instruction creation functions --------------- */

// automation of label creation
char * label_formatting(void)
{
	memset(labelStr, 0x0, 16);
	sprintf(labelStr, "L%d", label);
	label++; 						// create a new label
	return labelStr;
}

// declaration of variable inside the function
void decl_inblock(node_t node)
{
	create_comment(node->opr[0]->ident);
	if(node->opr[1] != NULL)
	{
		if(node->opr[1]->nature == NODE_IDENT)
		{
			// pointer = address 
			load_pointer(D0, node->opr[0]->address);
			load_pointer(D1, node->opr[1]->address);
			// read memory into A
			reading_memory(D1, A, W_FIELD);
			// exchnage A and DAT
			writing_memory(D0, A, W_FIELD);
		}
		else // IT IS A IMMEDIATE 
		{
			// pointer = address 
			load_pointer(D0, node->opr[0]->address);
			// A = value
			load_register(node->opr[1]->value, 0);
			// exchnage A and DAT
			writing_memory(D0, A, W_FIELD);
		}
	}
	else
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// A = value
		load_register(0, 0);
		// exchnage A and DAT
		writing_memory(D0, A, W_FIELD);
	}
}

// affectation of a variable
void affect_variable(node_t node)
{
	// affect an ident with an ident
	if(node->opr[0]->nature == NODE_IDENT && 
		node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		load_pointer(D1, node->opr[1]->address);
		// read memory into A
		reading_memory(D1, A, W_FIELD);
		// exchnage A and DAT
		writing_memory(D0, A, W_FIELD);
	}

	// affect an ident with a intval
	if((node->opr[0]->nature == NODE_IDENT && 
		node->opr[0]->type == TYPE_INT) && 
		node->opr[1]->nature == NODE_INTVAL)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// A = value
		load_register(node->opr[1]->value, 0);
		// exchnage A and DAT
		writing_memory(D0, A, W_FIELD);
	}

	// affect an ident with a floatval
	if((node->opr[0]->nature == NODE_IDENT && 
		node->opr[0]->type == TYPE_FLOAT) && 
		node->opr[1]->nature == NODE_FLOATVAL)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// A = value
		load_register(node->opr[1]->value, 0);
		// exchnage A and DAT
		writing_memory(D0, A, W_FIELD);
	}

	// affect an ident with a boolval
	if((node->opr[0]->nature == NODE_IDENT && 
		node->opr[0]->type == TYPE_BOOL) && 
		node->opr[1]->nature == NODE_BOOLVAL)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// A = value
		load_register(node->opr[1]->value, 0);
		// exchnage A and DAT
		writing_memory(D0, A, S_FIELD);	// value of bool on a S field only
	}
}

// create an lt condition
void create_lt_instr(node_t node)
{
	// check register available
	// handling experssion such as addition or substraction
	if (node->opr[1]->nature == NODE_INTVAL || 
		node->opr[1]->nature == NODE_FLOATVAL)
	{
		switch(node->opr[1]->nature){
			case NODE_PLUS :
			case NODE_MINUS :
			case NODE_UMINUS :
			case NODE_DIV :
			case NODE_MUL :
			case NODE_MOD :
			case NODE_BNOT :
			case NODE_BAND :
			case NODE_BOR :
			case NODE_BXOR :
			case NODE_SRL :
			case NODE_SLL :
			default : 
			break;
		}
	}
	// if we are in a loop 
	else if (inLoopFor || inLoopWhile) 
	{
		if(node->opr[1]->global_decl)
		{
		}
		else
		{
		}
	}

	//creation of branchement
	if(inLoopFor || inLoopWhile)
	{
	}
	else if(inLoopDo)
	{
	}
	else if(inIf)
	{
	}
}

// dupe above for every condition possible
// NODE_LT
// NODE_GT
// NODE_EQ
// NODE_NE
// NODE_GE
// NODE_LE
// NODE_AND
// NODE_OR
// NODE_NOT


// create an addition
void create_plus_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		register_zero(A, W_FIELD);
		add_const_register(A, W_FIELD, node->opr[0]->value);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		add_const_register(A, W_FIELD, node->opr[1]->value);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an substraction
void create_minus_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		register_zero(A, W_FIELD);
		sub_const_register(A, W_FIELD, node->opr[0]->value);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		sub_const_register(A, W_FIELD, node->opr[1]->value);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an multiplication
void create_mul_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		mul_register(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		mul_register(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an division
void create_div_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		div_register(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		div_register(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an modulo
void create_mod_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		mod_register(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		mod_register(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an bitwise and
void create_band_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		logical_AND(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		logical_AND(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an bitwise or
void create_bor_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		logical_OR(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		logical_OR(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}

	}
}

// create an bitwise xor
void create_bxor_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		logical_XOR(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		logical_XOR(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}

// create an bitwise not
void create_bnot_instr(node_t node)
{
	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchnage A and DAT
		reading_memory(D0, A, W_FIELD);
	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
	}
	else
	{
		switch(node->opr[0]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[0]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[0]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[0]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[0]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[0]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[0]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[0]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[0]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[1]->address);
		// exchnage A and DAT
		reading_memory(D0, C, W_FIELD);
		logical_XOR(A, C, W_FIELD);
	}
	else if (node->opr[1]->nature == NODE_INTVAL 	|| 
			 node->opr[1]->nature == NODE_FLOATVAL	||
			 node->opr[1]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[1]->value, 1);
		logical_XOR(A, C, W_FIELD);
	}
	else
	{
		switch(node->opr[1]->nature)
		{
			case NODE_PLUS :
				create_plus_instr(node->opr[1]);
			break;
			case NODE_MINUS :
				create_minus_instr(node->opr[1]);
			break;
			case NODE_MUL :
				create_mul_instr(node->opr[1]);
			break;
			case NODE_DIV :
				create_div_instr(node->opr[1]);
			break;
			case NODE_MOD :
				create_mod_instr(node->opr[1]);
			break;
			case NODE_BAND :
				create_band_instr(node->opr[1]);
			break;
			case NODE_BOR :
				create_bor_instr(node->opr[1]);
			break;
			case NODE_BXOR :
				create_bxor_instr(node->opr[1]);
			break;
			case NODE_BNOT :
			case NODE_SLL :
			case NODE_SRL :
			break;
		}
	}
}
// dupe above for every operation possible
// NODE_PLUS 	OK
// NODE_MINUS 	OK
// NODE_MUL 	OK
// NODE_DIV 	OK
// NODE_MOD 	OK
// NODE_BAND	OK
// NODE_BOR 	OK
// NODE_BXOR	OK
// NODE_BNOT
// NODE_SLL
// NODE_SRL



/* --------------- Main functions --------------- */

void gen_code_passe_2(node_t root) 
{
	if (launch)
	{
		// launching the program
		launch = 0;
	}
	for(int i = 0; i < root->nops; i++)
	{
		//set_current_node(root->opr[i]);
		if (root->opr[i] != NULL)
		{
			switch(root->opr[i]->nature)
			{
				// declaration of variables
				case NODE_DECL :
					if(root->opr[i]->opr[0]->global_decl)
					{
						create_comment(root->opr[i]->opr[0]->ident);
						if(root->opr[i]->opr[1] != NULL)
						{
							// pointer = address
							load_pointer(D0, root->opr[i]->opr[0]->address);
							// A = value
							load_register(root->opr[i]->opr[1]->value, 0);
							// exchange A and DAT
							writing_memory(D0, A, W_FIELD);
						}
						else // IF NO VALUE : VALUE = 0
						{
							load_pointer(D0, root->opr[i]->opr[0]->address);
							// A = value
							load_register(0, 0);
							// exchnage A and DAT
							writing_memory(D0, A, W_FIELD);
						}
					}
					else
					{
						decl_inblock(root->opr[i]);
					}
				break;

				// FUNC initilization 
				case NODE_FUNC :
					// create label
					create_label("MAIN_FUNC");
				break;		

				case NODE_AFFECT :
					// in 'for' loop block must be parsed before incrementing the index
					if (root->opr[i+1] != NULL && root->opr[i+1]->nature == NODE_BLOCK)
					{
						gen_code_passe_2(root->opr[i+1]);
						blockParsed = 1;
					}

					switch(root->opr[i]->opr[1]->nature)
					{
						case NODE_PLUS :
							create_plus_instr(root->opr[i]->opr[1]);
						break;
						case NODE_MINUS :
							create_minus_instr(root->opr[i]->opr[1]);
						break;
						case NODE_MUL :
							create_mul_instr(root->opr[i]->opr[1]);
						break;
						case NODE_DIV :
							create_div_instr(root->opr[i]->opr[1]);
						break;
						case NODE_MOD :
							create_mod_instr(root->opr[i]->opr[1]);
						break;
						case NODE_BAND :
							create_band_instr(root->opr[i]->opr[1]);
						break;
						case NODE_BOR :
							create_bor_instr(root->opr[i]->opr[1]);
						break;
						case NODE_BXOR :
							create_bxor_instr(root->opr[i]->opr[1]);
						break;
						case NODE_BNOT :
						case NODE_SLL :
						case NODE_SRL :
						break;
						default:
						break;
					}
					load_pointer(D0, root->opr[i]->opr[0]->address);
					writing_memory(D0, A, W_FIELD);
				break;
				
				//loop instruction determination
				case NODE_LT :
				case NODE_GT :
				case NODE_EQ :
				case NODE_NE :
				case NODE_GE :
				case NODE_LE :
				break;

				// case if the FOR index initialisation is a ident not an affectation
				case NODE_FOR :
					create_comment("STARTING FOR LOOP :");
					create_label(label_formatting());
					inLoopFor = 1;
				break;

				// creation of the While loop
				case NODE_WHILE :
					inLoopWhile = 1;
					create_comment("STARTING WHILE LOOP :");
					create_label(label_formatting());
					break;

				// creation of the Do While loop
				case NODE_DOWHILE :
					create_comment("STARTING DO_WHILE LOOP :");
					create_label(label_formatting());
					break;

				// creation of the If Statement
				case NODE_IF :
					inIf = 1;
					create_comment("IF :");
					create_label(label_formatting());
					break;	
			}		
		}

		// RECURSION
		if(root->opr[i] != NULL)
		{
			if (!(root->opr[i]->nature == NODE_BLOCK && blockParsed))
			{
				gen_code_passe_2(root->opr[i]);
			}
		}

		// End the program
		if(root->nature == NODE_PROGRAM)
		{
			if (inFunc_Decl)
			{
				// declare in main
				if(root->opr[1] != NULL)
				{
				}
			}
			else
			{
				// declare global 
				// declare the string in global
				for (int i = 0; i < 10; i++)
				{
				}
				inFunc_Decl = 1;
			}
		}

		// create a syscall for a print ?
		if(root->nature == NODE_PRINT)
		{
		}

		// creation of label for 'for' loop
		if(root->nature == NODE_FOR){
			if( parsingLoopFor == 0){
				label++;
				// create label
				parsingLoopFor++;
				inLoopFor = 1;
			}
			else if (parsingLoopFor == root->nops - 1)
			{
				// jump creation
				label++;
				// create label
				parsingLoopFor = 0;
				inLoopFor = 0;
				blockParsed = 0;
			}
			else
			{
				parsingLoopFor++;
			}
		}
		// creation of label for 'while' loop
		if (root->nature == NODE_WHILE)
		{
			if(parsingLoopWhile == root->nops - 1)
			{
				// create jump 
				label++;
				// create label
				parsingLoopWhile = 0;
				inLoopWhile = 0;
				blockParsed = 0;
			}
			else
			{
				parsingLoopWhile++;
			}
		}
		// creation of label for 'dowhile' loop
		if(root->nature == NODE_DOWHILE)
		{
			inLoopDo = 1;
			if(parsingLoopDo == root->nops - 1)
			{
				parsingLoopDo = 0;
				inLoopDo = 0;
			}
			else
			{
				parsingLoopDo++;
			}			
		}
		// creation of label for 'if' statement
		if(root->nature == NODE_IF)
		{
			if (parsingLoopIf == root->nops-1)
			{
				label++;
				// create label	
				parsingLoopIf = 0;
				inIf = 0;
			}
			else
			{
				parsingLoopIf++;
			}
		}
	}
}

 

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
static bool launch = false;
static unsigned int label = 0;
static char labelStr[16];
static bool inIf = false;
static bool inWhile = false;
static bool inDoWhile = false;
static bool inFor = 0;
static bool blockParsed = false;
static unsigned int countInCond = 0; // less then  2^31-1 '&&' or '||' in if condition or maybe you're trying something crazy

/*
static int current_reg;
static int inBlockFunc = 0;
static int parsingLoopFor = 0;
static int jmpLabelDecl = 0;
static int inFunc_Decl = 0;
*/


/* --------------- Instruction creation functions --------------- */

// automation of label creation
char * label_formatting(void)
{
	memset(labelStr, 0x0, 16);
	sprintf(labelStr, "L%d", label);
	label++; 						// create a new label
	return labelStr;
}

char * get_label(void)
{
	return labelStr;
}

void update_label_string(char* dest)
{
	memcpy(dest, label_formatting(), 16);
}

// priority management
void manage_priority(node_t node, int position) // position left or right 
{
	switch(node->nature)
	{
		case NODE_DIV :
		case NODE_MUL :
		case NODE_MOD :
			create_operation(node);
			// load the result in save reg
			ex_reg_work_save(A, position, W_FIELD);
			save_reg_available(node, YES);
		break;
		case NODE_PRIO:
			create_operation(node->opr[0]);
			// load the result in a save reg 
			ex_reg_work_save(A, position, W_FIELD); 
			save_reg_available(node->opr[0], YES);
		break;
		default:
		break;
	}
}

// ------------ VARIABLE MANAGEMENT ------------ //

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
			// exchange A and DAT
			writing_memory(D0, A, W_FIELD);
		}
		else // IT IS A IMMEDIATE 
		{
			// pointer = address 
			load_pointer(D0, node->opr[0]->address);
			// A = value
			load_register(node->opr[1]->value, 0);
			// exchange A and DAT
			writing_memory(D0, A, W_FIELD);
		}
	}
	else
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// A = value
		load_register(0, 0);
		// exchange A and DAT
		writing_memory(D0, A, W_FIELD);
	}
}

// affectation of a variable (unused)
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
		// exchange A and DAT
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
		// exchange A and DAT
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
		// exchange A and DAT
		writing_memory(D0, A, S_FIELD);	// value of bool on a S field only
	}
}
// --------------------------------------------- //


// ------------ OPERATIONS CREATIONS ------------ //

// create an opposite 
void create_uminus_instr(node_t node)
{
	// prio management
	if(node->opr[0]->isPrio)
	{
		manage_priority(node->opr[0], LEFT);
	}

	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchange A and DAT
		reading_memory(D0, A, W_FIELD);
		two_complement(A, W_FIELD);

	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
		two_complement(A, W_FIELD);				
	}
	else
	{
		if(!node->opr[0]->isPrio)
		{
			create_operation(node->opr[0]);
		}
		else
		{
			copy_reg_save_work(R0, A, W_FIELD);
			two_complement(A, W_FIELD);
		}
	}
}

// create a bitwise not
void create_bnot_instr(node_t node)
{
	// prio management
	if(node->opr[0]->isPrio)
	{
		manage_priority(node->opr[0], LEFT);
	}

	if(node->opr[0]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D0, node->opr[0]->address);
		// exchange A and DAT
		reading_memory(D0, A, W_FIELD);
		one_complement(A, W_FIELD);

	}
	else if (node->opr[0]->nature == NODE_INTVAL 	|| 
			 node->opr[0]->nature == NODE_FLOATVAL	||
			 node->opr[0]->nature == NODE_BOOLVAL)
	{
		load_register(node->opr[0]->value, 0);
		one_complement(A, W_FIELD);				
	}
	else
	{
		if(!node->opr[0]->isPrio)
		{
			create_operation(node->opr[0]);
		}
		else
		{
			copy_reg_save_work(R0, A, W_FIELD);
			one_complement(A, W_FIELD);
		}
	}
}

// create operation 
/* PRECISION FOR CONDITIONNAL OPERATIONS
--
--	case of parsing a condition
-- 	-> manage condition bool operation
-- 	-> parse block 
-- 	-> if condition respected (opposite of what expected) jump to else
--	-> example : wrinting [if(x<0)] translate to [if(x>=0) then jump to end of block]
--
*/
void create_operation(node_t node)
{
	switch(node->nature)
	{
		// special cases 1 operand
		case NODE_UMINUS :
			create_uminus_instr(node);
		break;
		case NODE_BNOT :
			create_bnot_instr(node);
		break;
		// case ident is used as a condition in a if
		case NODE_IDENT :
			if(inIf == true) // security
			{
				load_pointer(D0, node->address);
				// exchange A and DAT
				reading_memory(D0, A, W_FIELD);
				//if value = 0 skip the if
				different_from_zero(A, W_FIELD);
			}
		break;
		// else 2 operand
		default:
		 	// prio management
			if(node->opr[0]->isPrio)
			{
				manage_priority(node->opr[0], LEFT);
			}
			if(node->opr[1]->isPrio)
			{
				manage_priority(node->opr[1], RIGHT);
			}

			// left operand
			if(node->opr[0]->nature == NODE_IDENT)
			{
				// pointer = address 
				load_pointer(D0, node->opr[0]->address);
				// exchange A and DAT
				reading_memory(D0, A, W_FIELD);
				if(node->opr[1]->isPrio)
				{
					copy_reg_save_work(R1, C, W_FIELD);	
					if(save_reg_available(NULL, NO)) // to ensure that the prio has been treated
					{
						switch(node->nature)
						{
							case NODE_PLUS :
								add_register(A, C, W_FIELD);
							break;
							case NODE_MINUS :
								sub_register(A, C, W_FIELD);
							break;
							case NODE_MUL :
								mul_register(A, C, W_FIELD);
							break;
							case NODE_DIV :
								div_register(A, C, W_FIELD);
							break;
							case NODE_MOD :
								mod_register(A, C, W_FIELD);
							break;
							case NODE_BAND :
								logical_AND(A, C, W_FIELD);
							break;
							case NODE_BOR :
								logical_OR(A, C, W_FIELD);
							break;
							case NODE_BXOR :
								logical_XOR(A, C, W_FIELD);
							break;
							case NODE_LT : // opposite op : GTE
								register_GTE(A, C, W_FIELD);
							break;
							case NODE_GT : // opposite op : LTE
								register_LTE(A, C, W_FIELD);
							break;
							case NODE_EQ : // opposite op : NE
								register_not_equal(A, C, W_FIELD);
							break;
							case NODE_NE : // opposite op : EQ
								register_equal(A, C, W_FIELD);
							break;
							case NODE_GE : // opposite op : LT
								register_LT(A, C, W_FIELD);
							break;
							case NODE_LE : // opposite op : GT
								register_GT(A, C, W_FIELD);
							break;
							case NODE_SLL :
							case NODE_SRL :
							default:
							break;
						}
					}	
				}
			}
			else if (node->opr[0]->nature == NODE_INTVAL 	|| 
					 node->opr[0]->nature == NODE_FLOATVAL	||
					 node->opr[0]->nature == NODE_BOOLVAL)
			{
				load_register(node->opr[0]->value, 0);
				if(node->opr[1]->isPrio)
				{
					copy_reg_save_work(R1, C, W_FIELD);	
					if(save_reg_available(NULL, NO)) // to ensure that the prio has been treated
					{
						switch(node->nature)
						{
							case NODE_PLUS :
								add_register(A, C, W_FIELD);
							break;
							case NODE_MINUS :
								sub_register(A, C, W_FIELD);
							break;
							case NODE_MUL :
								mul_register(A, C, W_FIELD);
							break;
							case NODE_DIV :
								div_register(A, C, W_FIELD);
							break;
							case NODE_MOD :
								mod_register(A, C, W_FIELD);
							break;
							case NODE_BAND :
								logical_AND(A, C, W_FIELD);
							break;
							case NODE_BOR :
								logical_OR(A, C, W_FIELD);
							break;
							case NODE_BXOR :
								logical_XOR(A, C, W_FIELD);
							break;
							case NODE_LT : // opposite op : GTE
								register_GTE(A, C, W_FIELD);
							break;
							case NODE_GT : // opposite op : LTE
								register_LTE(A, C, W_FIELD);
							break;
							case NODE_EQ : // opposite op : NE
								register_not_equal(A, C, W_FIELD);
							break;
							case NODE_NE : // opposite op : EQ
								register_equal(A, C, W_FIELD);
							break;
							case NODE_GE : // opposite op : LT
								register_LT(A, C, W_FIELD);
							break;
							case NODE_LE : // opposite op : GT
								register_GT(A, C, W_FIELD);
							break;
							case NODE_SLL :
							case NODE_SRL :
							default:
							break;
						}
					}				
				}

			}
			else
			{
				if(!node->opr[0]->isPrio)
				{
					create_operation(node->opr[0]);
				}
			}

			//right operand
			if(node->opr[1]->nature == NODE_IDENT)
			{
				// pointer = address 
				load_pointer(D1, node->opr[1]->address);
				// exchange A and DAT
				reading_memory(D1, C, W_FIELD);
				if(node->opr[0]->isPrio)
				{
					copy_reg_save_work(R0, A, W_FIELD);
				}
				switch(node->nature)
				{
					case NODE_PLUS :
						add_register(A, C, W_FIELD);
					break;
					case NODE_MINUS :
						sub_register(A, C, W_FIELD);
					break;
					case NODE_MUL :
						mul_register(A, C, W_FIELD);
					break;
					case NODE_DIV :
						div_register(A, C, W_FIELD);
					break;
					case NODE_MOD :
						mod_register(A, C, W_FIELD);
					break;
					case NODE_BAND :
						logical_AND(A, C, W_FIELD);
					break;
					case NODE_BOR :
						logical_OR(A, C, W_FIELD);
					break;
					case NODE_BXOR :
						logical_XOR(A, C, W_FIELD);
					break;
					case NODE_LT : // opposite op : GTE
						register_GTE(A, C, W_FIELD);
					break;
					case NODE_GT : // opposite op : LTE
						register_LTE(A, C, W_FIELD);
					break;
					case NODE_EQ : // opposite op : NE
						register_not_equal(A, C, W_FIELD);
					break;
					case NODE_NE : // opposite op : EQ
						register_equal(A, C, W_FIELD);
					break;
					case NODE_GE : // opposite op : LT
						register_LT(A, C, W_FIELD);
					break;
					case NODE_LE : // opposite op : GT
						register_GT(A, C, W_FIELD);
					break;
					case NODE_SLL :
					case NODE_SRL :
					default:
					break;
				}
			}
			else if (node->opr[1]->nature == NODE_INTVAL 	|| 
					 node->opr[1]->nature == NODE_FLOATVAL	||
					 node->opr[1]->nature == NODE_BOOLVAL) 
			{
				load_register(node->opr[1]->value, 1);
				if(	node->opr[0]->isPrio)
				{
					copy_reg_save_work(R0, A, W_FIELD);
				}
				switch(node->nature)
				{
					case NODE_PLUS :
						add_register(A, C, W_FIELD);
					break;
					case NODE_MINUS :
						sub_register(A, C, W_FIELD);
					break;
					case NODE_MUL :
						mul_register(A, C, W_FIELD);
					break;
					case NODE_DIV :
						div_register(A, C, W_FIELD);
					break;
					case NODE_MOD :
						mod_register(A, C, W_FIELD);
					break;
					case NODE_BAND :
						logical_AND(A, C, W_FIELD);
					break;
					case NODE_BOR :
						logical_OR(A, C, W_FIELD);
					break;
					case NODE_BXOR :
						logical_XOR(A, C, W_FIELD);
					break;
					case NODE_LT : // opposite op : GTE
						register_GTE(A, C, W_FIELD);
					break;
					case NODE_GT : // opposite op : LTE
						register_LTE(A, C, W_FIELD);
					break;
					case NODE_EQ : // opposite op : NE
						register_not_equal(A, C, W_FIELD);
					break;
					case NODE_NE : // opposite op : EQ
						register_equal(A, C, W_FIELD);
					break;
					case NODE_GE : // opposite op : LT
						register_LT(A, C, W_FIELD);
					break;
					case NODE_LE : // opposite op : GT
						register_GT(A, C, W_FIELD);
					break;
					case NODE_SLL :
					case NODE_SRL :
					default:
					break;
				}
			}
			else
			{
				if(!node->opr[1]->isPrio)
				{
					create_operation(node->opr[1]);
				}
			}
		break;
	}
}


// for managing conditional operation with NOT
void create_NOT_operation(node_t node)
{
	switch(node->nature)
	{
		// 1 operand ident
		// else 2 operand
		default:
		 	// prio management
			if(node->opr[0]->isPrio)
			{
				manage_priority(node->opr[0], LEFT);
			}
			if(node->opr[1]->isPrio)
			{
				manage_priority(node->opr[1], RIGHT);
			}

			// left operand
			if(node->opr[0]->nature == NODE_IDENT)
			{
				// pointer = address 
				load_pointer(D0, node->opr[0]->address);
				// exchange A and DAT
				reading_memory(D0, A, W_FIELD);
				if(node->opr[1]->isPrio)
				{
					copy_reg_save_work(R1, C, W_FIELD);	
					if(save_reg_available(NULL, NO)) // to ensure that the prio has been treated
					{
						switch(node->nature)
						{
							case NODE_LT : // opposite op of GTE 
								register_LT(A, C, W_FIELD);
							break;
							case NODE_GT : // opposite op of GT
								register_GT(A, C, W_FIELD);
							break;
							case NODE_EQ : // opposite op of NE
								register_equal(A, C, W_FIELD);
							break;
							case NODE_NE : // opposite op of EQ
								register_not_equal(A, C, W_FIELD);
							break;
							case NODE_GE : // opposite op of LT
								register_GTE(A, C, W_FIELD);
							break;
							case NODE_LE : // opposite op of GT
								register_LTE(A, C, W_FIELD);
							break;
							case NODE_SLL :
							case NODE_SRL :
							default:
							break;
						}
					}	
				}
			}
			else if (node->opr[0]->nature == NODE_INTVAL 	|| 
					 node->opr[0]->nature == NODE_FLOATVAL	||
					 node->opr[0]->nature == NODE_BOOLVAL)
			{
				load_register(node->opr[0]->value, 0);
				if(node->opr[1]->isPrio)
				{
					copy_reg_save_work(R1, C, W_FIELD);	
					if(save_reg_available(NULL, NO)) // to ensure that the prio has been treated
					{
						switch(node->nature)
						{
							case NODE_LT : // opposite op of GTE 
								register_LT(A, C, W_FIELD);
							break;
							case NODE_GT : // opposite op of GT
								register_GT(A, C, W_FIELD);
							break;
							case NODE_EQ : // opposite op of NE
								register_equal(A, C, W_FIELD);
							break;
							case NODE_NE : // opposite op of EQ
								register_not_equal(A, C, W_FIELD);
							break;
							case NODE_GE : // opposite op of LT
								register_GTE(A, C, W_FIELD);
							break;
							case NODE_LE : // opposite op of GT
								register_LTE(A, C, W_FIELD);
							break;
							case NODE_SLL :
							case NODE_SRL :
							default:
							break;
						}
					}				
				}

			}
			else
			{
				if(!node->opr[0]->isPrio)
				{
					create_operation(node->opr[0]);
				}
			}

			//right operand
			if(node->opr[1]->nature == NODE_IDENT)
			{
				// pointer = address 
				load_pointer(D0, node->opr[1]->address);
				// exchange A and DAT
				reading_memory(D0, A, W_FIELD);
				if(node->opr[0]->isPrio)
				{
					copy_reg_save_work(R0, A, W_FIELD);
				}
				switch(node->nature)
				{
					case NODE_LT : // opposite op of GTE 
						register_LT(A, C, W_FIELD);
					break;
					case NODE_GT : // opposite op of GT
						register_GT(A, C, W_FIELD);
					break;
					case NODE_EQ : // opposite op of NE
						register_equal(A, C, W_FIELD);
					break;
					case NODE_NE : // opposite op of EQ
						register_not_equal(A, C, W_FIELD);
					break;
					case NODE_GE : // opposite op of LT
						register_GTE(A, C, W_FIELD);
					break;
					case NODE_LE : // opposite op of GT
						register_LTE(A, C, W_FIELD);
					break;
					case NODE_SLL :
					case NODE_SRL :
					default:
					break;
				}
			}
			else if (node->opr[1]->nature == NODE_INTVAL 	|| 
					 node->opr[1]->nature == NODE_FLOATVAL	||
					 node->opr[1]->nature == NODE_BOOLVAL) 
			{
				load_register(node->opr[1]->value, 1);
				if(	node->opr[0]->isPrio)
				{
					copy_reg_save_work(R0, A, W_FIELD);
				}
				switch(node->nature)
				{
					case NODE_LT : // opposite op of GTE 
						register_LT(A, C, W_FIELD);
					break;
					case NODE_GT : // opposite op of GT
						register_GT(A, C, W_FIELD);
					break;
					case NODE_EQ : // opposite op of NE
						register_equal(A, C, W_FIELD);
					break;
					case NODE_NE : // opposite op of EQ
						register_not_equal(A, C, W_FIELD);
					break;
					case NODE_GE : // opposite op of LT
						register_GTE(A, C, W_FIELD);
					break;
					case NODE_LE : // opposite op of GT
						register_LTE(A, C, W_FIELD);
					break;
					case NODE_SLL :
					case NODE_SRL :
					default:
					break;
				}
			}
			else
			{
				if(!node->opr[1]->isPrio)
				{
					create_operation(node->opr[1]);
				}
			}
		break;
	}
}

// every integer/float operation possible
// NODE_SLL		TO DO BUT ANNOYING
// NODE_SRL		TO DO BUT ANNOYING

// ------------------------------------------------- //


// -------------- OPERATIONS FOR TESTS ------------- //
// !!! beware : big function !!! -> modify at your own risk (to optimize imo)
// functions to parse conditionnal instructions
// input : 	node -> current node to parse
//			loc_label-> current label used
// 			statement -> conditionnal statement currently parsing (while, do_while, if, for)
void create_cond_instruction(node_t node, char * loc_label, int statement)
{
	char label_in_use[16]; // creating a temporary label for recursion
	char label_in_use_1[16]; 	// creating a temporary label for recursion

	memcpy(label_in_use,loc_label,16);

	if(statement == WHILE_STATEMENT || statement == DOWHILE_STATEMENT)
	{
		update_label_string(loc_label);
		memcpy(label_in_use_1,loc_label,16);
		create_label(label_in_use_1);
	}

	switch(node->opr[0]->nature) // treatment of condition
	{
		case NODE_AND:
			if(countInCond < 2 && statement == DOWHILE_STATEMENT)
			{
				gen_code_passe_2(node->opr[1]);
			}
			switch(node->opr[0]->opr[0]->nature)
			{
				case NODE_AND :
					countInCond++; // for recursion entry point 
					switch(statement)
					{
						case IF_STATEMENT :
							create_cond_instruction(node->opr[0], label_in_use, IF_STATEMENT);
						break;
						
						case WHILE_STATEMENT :
							create_cond_instruction(node->opr[0], label_in_use, WHILE_STATEMENT);
						break;
						
						case DOWHILE_STATEMENT :
							create_cond_instruction(node->opr[0], label_in_use, WHILE_STATEMENT);
						break;

						case FOR_STATEMENT :
						break;
					}
					countInCond--; // for recursion exit point
				break;
				// --- CURRENTLY BUGGY : TO IMPROVE ---
				// case NODE_OR : 
				// 	countInCond++; // for recursion entry point 
				// 	create_if_instruction(node->opr[0], label_formatting());
				// 	countInCond--; // for recursion exit point
				// break;
				// ------------------------------------
				case NODE_PRIO:
					create_operation(node->opr[0]->opr[0]->opr[0]);
					if(node->opr[0]->opr[0]->opr[0]->type != TYPE_BOOL) // test for int operations
					{
						equal_to_zero(A, W_FIELD);
					}
					GOYES(label_in_use);
				break;

				case NODE_BOOLVAL:
				case NODE_INTVAL:
				case NODE_FLOATVAL:
					switch(node->opr[0]->opr[0]->value)
					{
						case 0 : // in a AND make the value always false
							// skip the entire cond
							goto end_of_cond;
						break;
						default :
						break;
					}
				break;

				default:
					create_operation(node->opr[0]->opr[0]);	
					if(node->opr[0]->opr[0]->type != TYPE_BOOL) // test for int operations
					{
						equal_to_zero(A, W_FIELD);
					}
					GOYES(label_in_use);	
				break;
			}
			
			switch(node->opr[0]->opr[1]->nature)
			{
				// --- CURRENTLY BUGGY : TO IMPROVE ---
				// case NODE_OR : 
				// 	countInCond++; // for recursion entry point 
				// 	create_if_instruction(node->opr[0], label_formatting());
				// 	countInCond--; // for recursion exit point
				// break;
				// case NODE_AND :
				// 	countInCond++; // for recursion entry point 
				// 	create_if_instruction(node->opr[0], label_in_use);
				// 	countInCond--; // for recursion exit point
				// break;
				// ------------------------------------
				case NODE_PRIO:
					switch(statement)
					{
						case IF_STATEMENT:
							create_operation(node->opr[0]->opr[1]->opr[0]);
							if(node->opr[0]->opr[1]->opr[0]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_formatting());
								create_label(label_in_use);
							}
						break;

						case WHILE_STATEMENT:
							create_operation(node->opr[0]->opr[1]->opr[0]);
							if(node->opr[0]->opr[1]->opr[0]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case DOWHILE_STATEMENT:
							create_operation(node->opr[0]->opr[1]->opr[0]);
							if(node->opr[0]->opr[1]->opr[0]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case FOR_STATEMENT:
						break;
					}
				break;

				case NODE_BOOLVAL:
				case NODE_INTVAL:
				case NODE_FLOATVAL:
					switch(node->opr[0]->opr[1]->value)
					{
						case 0 : // in a AND make the value always false
							// jump automatically to label (can be optimized and skip the entire if)
							go_very_long(label_in_use);
							create_label(label_in_use);
							goto end_of_cond;
						break;
						default :
						break;
					}
				break;

				default:
					switch(statement)
					{
						case IF_STATEMENT:
							create_operation(node->opr[0]->opr[1]);	
							if(node->opr[0]->opr[1]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);	
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_formatting());
								create_label(label_in_use);
							}
						break;

						case WHILE_STATEMENT:
							create_operation(node->opr[0]->opr[1]);	
							if(node->opr[0]->opr[1]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case DOWHILE_STATEMENT:
							create_operation(node->opr[0]->opr[1]);	
							if(node->opr[0]->opr[1]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);	
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case FOR_STATEMENT:
						break;
					}
				break;
			}
		break;

		case NODE_OR:
			// create a register use B
			if(countInCond < 2)
			{
				register_zero(B, W_FIELD);
				if(statement == DOWHILE_STATEMENT)
				{
					gen_code_passe_2(node->opr[1]);
				}
			}
			switch(node->opr[0]->opr[0]->nature)
			{
				case NODE_OR : 
					countInCond++; // for recursion entry point 
					switch(statement)
					{
						case IF_STATEMENT:
							create_cond_instruction(node->opr[0], label_formatting(), IF_STATEMENT);
						break;

						case WHILE_STATEMENT:
							create_cond_instruction(node->opr[0], label_formatting(), WHILE_STATEMENT);
						break;

						case DOWHILE_STATEMENT:
							create_cond_instruction(node->opr[0], label_formatting(), DOWHILE_STATEMENT);
						break;

						case FOR_STATEMENT:
						break;
					}
					countInCond--; // for recursion exit point
				break;
				// --- CURRENTLY BUGGY : TO IMPROVE ---
				// case NODE_AND : 
				// 	countInCond++; // for recursion entry point 
				// 	create_if_instruction(node->opr[0], label_formatting());
				// 	countInCond--; // for recursion exit point
				// break;
				// ------------------------------------
				case NODE_PRIO:
					// do operation
					create_operation(node->opr[0]->opr[0]->opr[0]); 
					if(node->opr[0]->opr[0]->opr[0]->type != TYPE_BOOL) // test for int operations
					{
						equal_to_zero(A, W_FIELD);
					}
					GOYES(label_in_use);
					// increment register if true
					inc_register(B, W_FIELD);
					create_label(label_in_use);
					update_label_string(label_in_use);

				break;

				case NODE_BOOLVAL:
				case NODE_INTVAL:
				case NODE_FLOATVAL:
						// no impact in an or
				break;

				default:
					// do operation
					create_operation(node->opr[0]->opr[0]);
					if(node->opr[0]->opr[0]->type != TYPE_BOOL) // test for int operations
					{
						equal_to_zero(A, W_FIELD);
					}
					GOYES(label_in_use);
					// increment register if true
					inc_register(B, W_FIELD);
					create_label(label_in_use);
					update_label_string(label_in_use);
				break;
			}
			
			switch(node->opr[0]->opr[1]->nature)
			{

				// --- CURRENTLY BUGGY : TO IMPROVE ---
				// case NODE_OR : 
				// 	countInCond++; // for recursion entry point 
				// 	create_if_instruction(node->opr[0], label_formatting());
				// 	countInCond--; // for recursion exit point
				// break;
				// case NODE_AND :
				// 	countInCond++; // for recursion entry point 
				// 	create_if_instruction(node->opr[0], label_in_use);
				// 	countInCond--; // for recursion exit point
				// break;
				// ------------------------------------
				case NODE_PRIO:
					switch(statement)
					{
						case IF_STATEMENT:
							// do operation 
							create_operation(node->opr[0]->opr[1]->opr[0]);
							if(node->opr[0]->opr[1]->opr[0]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							// increment register if true
							inc_register(B, W_FIELD);
							create_label(label_in_use);
							update_label_string(label_in_use);
							// evaluate the register if is null, skip if
							equal_to_zero(B, W_FIELD);
				 			GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_formatting());
								create_label(label_in_use);
							}
						break;

						case WHILE_STATEMENT:
							// do operation 
							create_operation(node->opr[0]->opr[1]->opr[0]);
							if(node->opr[0]->opr[1]->opr[0]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							// increment register if true
							inc_register(B, W_FIELD);
							create_label(label_in_use);
							update_label_string(label_in_use);
							// evaluate the register if is null, skip if
							equal_to_zero(B, W_FIELD);
				 			GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case DOWHILE_STATEMENT:
							// do operation 
							create_operation(node->opr[0]->opr[1]->opr[0]);
							if(node->opr[0]->opr[1]->opr[0]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);
							// increment register if true
							inc_register(B, W_FIELD);
							create_label(label_in_use);
							update_label_string(label_in_use);
							// evaluate the register if is null, skip if
							equal_to_zero(B, W_FIELD);
				 			GOYES(label_in_use);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case FOR_STATEMENT:
						break;
					}
					
				break;

				case NODE_BOOLVAL:
				case NODE_INTVAL:
				case NODE_FLOATVAL:
						// no impact in an or
				break;

				default:
					switch(statement)
					{
						case IF_STATEMENT:
							// do operation 
							create_operation(node->opr[0]->opr[1]);	
							if(node->opr[0]->opr[1]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);	
							// increment register if true
							inc_register(B, W_FIELD);
							create_label(label_in_use);
							update_label_string(label_in_use);
							// evaluate the register if is null, skip if
							equal_to_zero(B, W_FIELD);
				 			GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_formatting());
								create_label(label_in_use);
							}
						break;

						case WHILE_STATEMENT:
							// do operation 
							create_operation(node->opr[0]->opr[1]);	
							if(node->opr[0]->opr[1]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);	
							// increment register if true
							inc_register(B, W_FIELD);
							create_label(label_in_use);
							update_label_string(label_in_use);
							// evaluate the register if is null, skip if
							equal_to_zero(B, W_FIELD);
				 			GOYES(label_in_use);
							gen_code_passe_2(node->opr[1]);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case DOWHILE_STATEMENT:
							// do operation 
							create_operation(node->opr[0]->opr[1]);	
							if(node->opr[0]->opr[1]->type != TYPE_BOOL) // test for int operations
							{
								equal_to_zero(A, W_FIELD);
							}
							GOYES(label_in_use);	
							// increment register if true
							inc_register(B, W_FIELD);
							create_label(label_in_use);
							update_label_string(label_in_use);
							// evaluate the register if is null, skip if
							equal_to_zero(B, W_FIELD);
				 			GOYES(label_in_use);
							if(countInCond < 2) // for recursion
							{
								go_very_long(label_in_use_1);
								create_label(label_in_use);
							}
						break;

						case FOR_STATEMENT:
						break;
					}
				break;
			}
		break;

		case NODE_NOT:
			switch(statement)
			{
				case IF_STATEMENT:
					if(node->opr[0]->opr[0]->nature == NODE_PRIO)
					{
						switch(node->opr[0]->opr[0]->opr[0]->type)
						{
							case TYPE_BOOL :
								create_NOT_operation(node->opr[0]->opr[0]->opr[0]);
							break;
							case TYPE_INT:
							case TYPE_FLOAT:
								create_operation(node->opr[0]->opr[0]->opr[0]);
								if( node->opr[0]->opr[0]->opr[0]->nature != NODE_INTVAL && 
									node->opr[0]->opr[0]->opr[0]->nature != NODE_FLOATVAL && 
									node->opr[0]->opr[0]->opr[0]->nature != NODE_BOOLVAL  ) 
								{
									one_complement(A, W_FIELD); // take the one complement of the result of a int operation
								}
								equal_to_zero(A, W_FIELD);
							break;

						}
					}
					else if(node->opr[0]->opr[0]->nature == NODE_IDENT)
					{
						load_pointer(D0, node->opr[0]->address);
						// exchange A and DAT
						reading_memory(D0, A, W_FIELD);
						//if value != 0 skip the if
						equal_to_zero(A, W_FIELD);
					}
					else
					{
						create_NOT_operation(node->opr[0]->opr[0]);
					}
					GOYES(label_in_use);	
					gen_code_passe_2(node->opr[1]);
					go_very_long(label_formatting());
					create_label(label_in_use);
				break;

				case WHILE_STATEMENT:
					if(node->opr[0]->opr[0]->nature == NODE_PRIO)
					{
						switch(node->opr[0]->opr[0]->opr[0]->type)
						{
							case TYPE_BOOL :
								create_NOT_operation(node->opr[0]->opr[0]->opr[0]);
							break;
							case TYPE_INT:
							case TYPE_FLOAT:
								create_operation(node->opr[0]->opr[0]->opr[0]);
								if( node->opr[0]->opr[0]->opr[0]->nature != NODE_INTVAL && 
									node->opr[0]->opr[0]->opr[0]->nature != NODE_FLOATVAL && 
									node->opr[0]->opr[0]->opr[0]->nature != NODE_BOOLVAL  )
								{
									one_complement(A, W_FIELD); // take the one complement of the result of a int operation
								}
								equal_to_zero(A, W_FIELD);
							break;

						}
					}
					else if(node->opr[0]->opr[0]->nature == NODE_IDENT)
					{
						load_pointer(D0, node->opr[0]->address);
						// exchange A and DAT
						reading_memory(D0, A, W_FIELD);
						//if value != 0 skip the if
						equal_to_zero(A, W_FIELD);
					}
					else
					{
						create_NOT_operation(node->opr[0]->opr[0]);
					}
					GOYES(label_in_use);	
					gen_code_passe_2(node->opr[1]);
					go_very_long(label_in_use_1);
					create_label(label_in_use);
				break;
				
				case DOWHILE_STATEMENT:
					gen_code_passe_2(node->opr[1]);
					if(node->opr[0]->opr[0]->nature == NODE_PRIO)
					{
						switch(node->opr[0]->opr[0]->opr[0]->type)
						{
							case TYPE_BOOL :
								create_NOT_operation(node->opr[0]->opr[0]->opr[0]); 
							break;
							case TYPE_INT:
							case TYPE_FLOAT:
								create_operation(node->opr[0]->opr[0]->opr[0]);
								if( node->opr[0]->opr[0]->opr[0]->nature != NODE_INTVAL && 
									node->opr[0]->opr[0]->opr[0]->nature != NODE_FLOATVAL && 
									node->opr[0]->opr[0]->opr[0]->nature != NODE_BOOLVAL  )
								{
									one_complement(A, W_FIELD); // take the one complement of the result of a int operation
								}
								equal_to_zero(A, W_FIELD);
							break;

						}
					}
					else if(node->opr[0]->opr[0]->nature == NODE_IDENT)
					{
						load_pointer(D0, node->opr[0]->address);
						// exchange A and DAT
						reading_memory(D0, A, W_FIELD);
						//if value != 0 skip the if
						equal_to_zero(A, W_FIELD);
					}
					else
					{
						create_NOT_operation(node->opr[0]->opr[0]);
					}
					GOYES(label_in_use);	
					go_very_long(label_in_use_1);
					create_label(label_in_use);
				break;

				case FOR_STATEMENT:
				break;
			}
		break;

		case NODE_BOOLVAL:
		case NODE_INTVAL:
		case NODE_FLOATVAL:
			switch(node->opr[0]->value)
			{
				// if 0 / false dont do it or only once for do while
				case 0 :
					if(statement == DOWHILE_STATEMENT)
					{
						gen_code_passe_2(node->opr[1]);	
					}
				break;
				// else do it
				default :
					gen_code_passe_2(node->opr[1]);	
					if(statement == DOWHILE_STATEMENT || statement == WHILE_STATEMENT)
					{
						go_very_long(label_in_use_1);
						create_label(label_in_use);
					}
				break;
			}
		break;

		default :
			switch(statement)
			{
				case IF_STATEMENT:
					if(node->opr[0]->nature == NODE_PRIO)
					{
						create_operation(node->opr[0]->opr[0]);
						if(node->opr[0]->opr[0]->type != TYPE_BOOL)
						{
							equal_to_zero(A, W_FIELD); // operation so type int
						}
					}
					else
					{
						create_operation(node->opr[0]);
						if(node->opr[0]->type != TYPE_BOOL)
						{
							equal_to_zero(A, W_FIELD); // operation so type int
						}
					}
					GOYES(label_in_use);	
					gen_code_passe_2(node->opr[1]);
					go_very_long(label_formatting());
					create_label(label_in_use);
				break;

				case WHILE_STATEMENT:
					if(node->opr[0]->nature == NODE_PRIO)
					{
						create_operation(node->opr[0]->opr[0]);
						if(node->opr[0]->opr[0]->type != TYPE_BOOL)
						{
							equal_to_zero(A, W_FIELD); // operation so type int
						}
					}
					else
					{
						create_operation(node->opr[0]);
						if(node->opr[0]->opr[0]->type != TYPE_BOOL)
						{
							equal_to_zero(A, W_FIELD); // operation so type int
						}
					}
					GOYES(label_in_use);	
					gen_code_passe_2(node->opr[1]);
					go_very_long(label_in_use_1);
					create_label(label_in_use);
				break;

				case DOWHILE_STATEMENT:
					gen_code_passe_2(node->opr[1]);
					if(node->opr[0]->nature == NODE_PRIO)
					{
						create_operation(node->opr[0]->opr[0]);
						if(node->opr[0]->opr[0]->type != TYPE_BOOL)
						{
							equal_to_zero(A, W_FIELD); // operation so type int
						}
					}
					else
					{
						create_operation(node->opr[0]);
						if(node->opr[0]->opr[0]->type != TYPE_BOOL)
						{
							equal_to_zero(A, W_FIELD); // operation so type int
						}
					}
					GOYES(label_in_use);	
					go_very_long(label_in_use_1);
					create_label(label_in_use);
				break;

				case FOR_STATEMENT:
				break;
			}
		break;
	}

end_of_cond: // jump for skip when cond is always false
	
	blockParsed = true; // force block parsing
}

// -------------------------------------------- //

void create_for(node_t node, char* loc_label)
{
	// while with stop condition
	char label_in_use[16]; 		// creating a temporary label for recursion
	char label_in_use_1[16]; 	// creating a temporary label for recursion
	memcpy(label_in_use,loc_label,16);
	update_label_string(loc_label);
	memcpy(label_in_use_1,loc_label,16);
	create_label(label_in_use_1);

	gen_code_passe_2(node->opr[1]);
	create_operation(node->opr[0]);
	GOYES(label_in_use);	
	go_very_long(label_in_use_1);
	create_label(label_in_use);
	blockParsed = true; // force block parsing
}

/* -------------------------------------------------------------- */

/* --------------------- Parsing functions ---------------------- */

void gen_code_passe_2(node_t root) 
{
	if (!launch)
	{
		// launching the program
		launch = true;
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
							// exchange A and DAT
							writing_memory(D0, A, W_FIELD);
						}
					}
					else
					{
						decl_inblock(root->opr[i]);
					}
				break;

				// FUNC initialization 
				case NODE_FUNC :
					// create label
					create_label("MAIN_FUNC");
				break;		

				case NODE_AFFECT :
					// in 'for' loop block must be parsed before incrementing the index
					if (root->opr[i+1] != NULL && root->opr[i+1]->nature == NODE_BLOCK)
					{
						gen_code_passe_2(root->opr[i+1]);
						blockParsed = true;
					}
					switch(root->opr[i]->opr[1]->nature)
					{
						case NODE_PRIO:
							create_operation(root->opr[i]->opr[1]->opr[0]);
							load_pointer(D0, root->opr[i]->opr[0]->address);
							writing_memory(D0, A, W_FIELD);
							flush_save_reg(); // reset save_reg pointers from our side : to test if useful
						break;

						case NODE_INTVAL:
						case NODE_BOOLVAL:
						case NODE_FLOATVAL:
						case NODE_IDENT:
							affect_variable(root->opr[i]);
						break;

						default:
							create_operation(root->opr[i]->opr[1]);
							load_pointer(D0, root->opr[i]->opr[0]->address);
							writing_memory(D0, A, W_FIELD);
							flush_save_reg(); // reset save_reg pointers from our side : to test if useful
						break;
					}
				break;
				
				// creation of the While loop
				case NODE_WHILE :
					create_comment("--- WHILE ---");
					inWhile = true;
					label_formatting();
					countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i], get_label(), WHILE_STATEMENT);
					countInCond--; 														// = 0 for recursion, last exit point
					inWhile = false;
					create_comment("--- ENDWHILE ---");
				break;

				// creation of the Do While loop
				case NODE_DOWHILE :
					create_comment("--- DOWHILE ---");
					inDoWhile = true;
					label_formatting();
					countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i], get_label(), DOWHILE_STATEMENT);
					countInCond--; 														// = 0 for recursion, last exit point
					inDoWhile = false;
					create_comment("--- ENDOWHILE ---");
				break;

				// creation of the If Statement
				case NODE_IF :
					create_comment("--- IF ---"); 										// to delete for debug in dump file
					inIf = true;
					label_formatting();
					countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i], get_label(), IF_STATEMENT);
					countInCond--; 														// = 0 for recursion, last exit point
					if(root->opr[i]->opr[2] != NULL) 									// else
					{
						create_comment("--- ELSE ---"); 								// to delete for debug in dump file
						gen_code_passe_2(root->opr[i]->opr[2]);
						create_comment("-- ENDELSE --"); 								// to delete for debug in dump file
					}
					create_label(get_label()); 											// to skip the else if the if is valid
					inIf = false;
					create_comment("-- ENDIF --"); 										// to delete for debug in dump file
				break;
				
				// case if the FOR index initialization is a ident not an affectation
				case NODE_FOR :
					create_comment("STARTING FOR LOOP :");
					inFor = true;
					inFor = false;
					create_label(label_formatting());
				break;

				default:
				case NODE_LIST :
				break;
			}		
		}

		// RECURSION
		if(root->opr[i] != NULL)
		{
			if (!(root->opr[i]->nature == NODE_BLOCK && blockParsed) && // block managed in the  
				(root->opr[i]->nature != NODE_ELSE)) // else managed in if 
			{
				gen_code_passe_2(root->opr[i]);
			}
			else
			{
				blockParsed = false;
			}
		}
	}
}

 

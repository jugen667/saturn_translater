// ========================================
// > Author :   jugen 667 
// > Title  :   gen_code.c 
// > Desc.  :   Second parse to generate
//				assembly code
// 				This second parsing does 
//				assembly output 
//				(manages jump label, cond
//				management, operations 
//				creations, priorities, ...)
// > Associated header : gen_code.h
// ========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/defs.h"
#include "../include/common.h"
#include "../include/gen_code.h"
#include "../include/instruction_set.h"


// global utility variables
static unsigned int g_curLabelIdx = 0;
static label_string g_labelTable[MAX_LABEL_AMT];
static bool g_isBlockParsed = false;
static unsigned int g_countInCond = 0; // less then  2^31-1 '&&' or '||' in if condition or maybe you're trying something crazy

static node_t g_currentNode = NULL; //unused atm 


/* --------------- Instruction creation functions --------------- */
void create_new_label(unsigned int index)
{
	snprintf(g_labelTable[index].labelStr, LABEL_STR_SIZE, "L%d", index);
	if(g_verboseDebug)
	{
		printf("Creating label %d : %s\n",index, g_labelTable[index].labelStr);
	}
	g_curLabelIdx++;
}


char * get_label(unsigned int index)
{
	return g_labelTable[index].labelStr;
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
		break;
		case NODE_PRIO:
			create_operation(node->opr[0]);
			// load the result in a save reg 
			ex_reg_work_save(A, position, W_FIELD); 
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
	// pointer = address 
	load_pointer(D0, node->opr[0]->address);
	if(node->opr[1] != NULL)
	{
		if(node->opr[1]->nature == NODE_IDENT)
		{
			load_pointer(D1, node->opr[1]->address);
			// read memory into A
			reading_memory(D1, A, W_FIELD);
		}
		else // IT IS A IMMEDIATE 
		{
			// A = value
			load_register(node->opr[1]->value, 0);
		}
	}
	else
	{
		// A = value
		load_register(0, 0);
	}
	// exchange A and DAT
	writing_memory(D0, A, W_FIELD);
}

// affectation of a variable
void affect_variable(node_t node)
{
	// pointer = address 
	load_pointer(D0, node->opr[0]->address);
	// affect an ident with an ident
	if(node->opr[0]->nature == NODE_IDENT && 
		node->opr[1]->nature == NODE_IDENT)
	{
		// pointer = address 
		load_pointer(D1, node->opr[1]->address);
		// read memory into A
		reading_memory(D1, A, W_FIELD);
	}
	// affect an ident with a value
	else
	{
		// A = value
		load_register(node->opr[1]->value, 0);
	}
	// exchange A and DAT
	writing_memory(D0, A, W_FIELD);	// value of bool on a S field only (for further optimization)
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

	switch(node->opr[0]->nature)
	{
		case NODE_IDENT:
			// pointer = address 
			load_pointer(D0, node->opr[0]->address);
			// exchange A and DAT
			reading_memory(D0, A, W_FIELD);
		break;

		case NODE_INTVAL:
		case NODE_FLOATVAL:
		case NODE_BOOLVAL:
			load_register(node->opr[0]->value, 0);
		break;

		default:
			if(!node->opr[0]->isPrio)
			{
				create_operation(node->opr[0]);
			}
			else
			{
				copy_reg_work_save(A, R0, W_FIELD);
			}
		break;
	}
	two_complement(A, W_FIELD);
}

// create a bitwise not
void create_bnot_instr(node_t node)
{
	// prio management
	if(node->opr[0]->isPrio)
	{
		manage_priority(node->opr[0], LEFT);
	}

	switch(node->opr[0]->nature)
	{
		case NODE_IDENT:
			// pointer = address 
			load_pointer(D0, node->opr[0]->address);
			// exchange A and DAT
			reading_memory(D0, A, W_FIELD);
		break;

		case NODE_INTVAL:
		case NODE_FLOATVAL:
		case NODE_BOOLVAL:
			load_register(node->opr[0]->value, 0);
		break;

		default:
			if(!node->opr[0]->isPrio)
			{
				create_operation(node->opr[0]);
			}
			else
			{
				copy_reg_work_save(A, R0, W_FIELD);
			}
		break;
	}
	one_complement(A, W_FIELD);
}


// create a primitive operation 
void create_raw_op(node_t node)
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


// create a primitive operation for not
void create_raw_not_op(node_t node)
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


// create operation 
// inNotCond : if parsing a NOT node
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
		case NODE_PRIO:
			create_operation(node->opr[0]);
		break;
		// case ident is used as a condition in a if
		case NODE_IDENT :							
			load_pointer(D0, node->address);
			// exchange A and DAT
			reading_memory(D0, A, W_FIELD);
			//if value = 0 skip the if
			equal_to_zero(A, W_FIELD);
		break;
		// else 2 operand
		default:
		 	// prio management
			if(node->opr[0] != NULL && node->opr[0]->isPrio)
			{
				manage_priority(node->opr[0], LEFT);
			}
			if(node->opr[1] != NULL && node->opr[1]->isPrio)
			{
				manage_priority(node->opr[1], RIGHT);
			}


			// left operand
			if(node->opr[0] != NULL)
			{
				switch(node->opr[0]->nature)
				{
					case NODE_IDENT :
						// pointer = address 
						load_pointer(D0, node->opr[0]->address);
						// exchange A and DAT
						reading_memory(D0, A, W_FIELD);
						if(node->opr[1] != NULL && node->opr[1]->isPrio)
						{
							copy_reg_work_save(C, R1, W_FIELD);
						}
				    break;

					case NODE_INTVAL :
					case NODE_FLOATVAL : 
					case NODE_BOOLVAL :
						// pointer = address 
						load_register(node->opr[0]->value, 0);
						if(node->opr[1] != NULL && node->opr[1]->isPrio)
						{
							copy_reg_work_save(C, R1, W_FIELD);
						}
					break;

					default:
						// if(!node->opr[0]->isPrio) // not sure is useful ??
						{
							create_operation(node->opr[0]);
							if(node->opr[1] != NULL && node->opr[1]->isPrio)
							{
								copy_reg_work_save(C, R1, W_FIELD);
							}
						}
					break;

				}
			}


			//right operand
			if(node->opr[1] != NULL)
			{
				switch(node->opr[1]->nature)
				{
					case NODE_IDENT:
						// pointer = address 
						load_pointer(D1, node->opr[1]->address);
						// exchange A and DAT
						reading_memory(D1, C, W_FIELD);
						if(node->opr[0]->isPrio)
						{
							copy_reg_work_save(A, R0, W_FIELD);
						}
					break;

					case NODE_INTVAL:
					case NODE_FLOATVAL:
					case NODE_BOOLVAL:
						load_register(node->opr[1]->value, 1);
						if(	node->opr[0]->isPrio)
						{
							copy_reg_work_save(A, R0, W_FIELD);
						}
					break;	

					default:
						if(!node->opr[1]->isPrio)  // not sure is useful ??
						{
							create_operation(node->opr[1]);
						}
						else if(node->opr[0]->isPrio && node->opr[1]->isPrio)
						{
							copy_reg_work_save(A, R0, W_FIELD);
							copy_reg_work_save(C, R1, W_FIELD);
						}
					break;
				}
			}
			create_raw_op(node);
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
		case NODE_PRIO:
			create_NOT_operation(node->opr[0]);
		break;
		case NODE_IDENT :
			load_pointer(D0, node->address);
			// exchange A and DAT
			reading_memory(D0, A, W_FIELD);
			//if value != 0 skip the if
			different_from_zero(A, W_FIELD);
		break;
		case NODE_INTVAL :
		case NODE_FLOATVAL : 
		case NODE_BOOLVAL :
			// pointer = address 
			load_register(node->value, 0);
			different_from_zero(A, W_FIELD);
		break;
		default:
		 	// prio management
			if(node->opr[0] != NULL /*&& node->opr[0]->isPrio*/)
			{
				manage_priority(node->opr[0], LEFT);
			}
			if(node->opr[1] != NULL && node->opr[1]->isPrio)
			{
				manage_priority(node->opr[1], RIGHT);
			}

			/// left operand
			if(node->opr[0] != NULL)
			{
				switch(node->opr[0]->nature)
				{
					case NODE_IDENT :
						// pointer = address 
						load_pointer(D0, node->opr[0]->address);
						// exchange A and DAT
						reading_memory(D0, A, W_FIELD);
						if(node->opr[1] != NULL && node->opr[1]->isPrio)
						{
							copy_reg_save_work(R1, C, W_FIELD);	
						}
				    break;

					case NODE_INTVAL :
					case NODE_FLOATVAL : 
					case NODE_BOOLVAL :
						// pointer = address 
						load_register(node->opr[0]->value, 0);
						if(node->opr[1] != NULL && node->opr[1]->isPrio)
						{
							copy_reg_save_work(R1, C, W_FIELD);	
						}
					break;

					default:
						if(!node->opr[0]->isPrio)
						{
							create_NOT_operation(node->opr[0]);
						}
					break;

				}
			}


			//right operand
			if(node->opr[1] != NULL)
			{
				switch(node->opr[1]->nature)
				{
					case NODE_IDENT:
						// pointer = address 
						load_pointer(D1, node->opr[1]->address);
						// exchange A and DAT
						reading_memory(D1, C, W_FIELD);
						if(node->opr[0]->isPrio)
						{
							copy_reg_save_work(R0, A, W_FIELD);
						}
						// create_raw_op(node);
					break;

					case NODE_INTVAL:
					case NODE_FLOATVAL:
					case NODE_BOOLVAL:
						load_register(node->opr[1]->value, 1);
						if(	node->opr[0]->isPrio)
						{
							copy_reg_save_work(R0, A, W_FIELD);
						}
					break;	

					default:
						if(!node->opr[1]->isPrio)
						{
							create_NOT_operation(node->opr[1]);
						}
						else if(node->opr[0]->isPrio && node->opr[1]->isPrio)
						{
							copy_reg_work_save(A, R0, W_FIELD);
							copy_reg_work_save(C, R1, W_FIELD);
						}
					break;
				}
			}
			create_raw_not_op(node);
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
// input : 	node -> current node to parse (with the condition)
// 			root -> current node - 1 to parse for statement 
//			loc_label-> current label used
// 			statement -> conditionnal statement currently parsing (while, do_while, if, for)
void create_cond_instruction(node_t node, node_t root, unsigned int loc_label, int statement)
{

// unsigned int labelIndex1, labelIndex2;

	// distribute labels: need 2 labels 
	unsigned int labelIndex1 = loc_label;
	unsigned int labelIndex2 = loc_label + 1;

	if(statement == IF_STATEMENT)
	{
		create_new_label(labelIndex1);
	}
	// labelIndex1 already created at start (for, while & dowhile)
	create_new_label(labelIndex2);	

	switch(node->nature) // treatment of condition
	{
		case NODE_AND:
		case NODE_OR:
			
		break;

		case NODE_NOT:
			if(statement == DOWHILE_STATEMENT)
			{
				gen_code(root->opr[1]);
			}
			create_NOT_operation(node->opr[0]);
		break;

		case NODE_BOOLVAL:
		case NODE_INTVAL:
		case NODE_FLOATVAL:
			switch(node->value)
			{
				// if 0 / false dont do it or only once for do while
				case 0 :
					if(statement == DOWHILE_STATEMENT)
					{
						gen_code(root->opr[1]);	
					}
				break;
				// else do it
				default :
					if(root->opr[1] != NULL && statement != FOR_STATEMENT)
		 			{
						gen_code(root->opr[1]);
		 			}
		 			else if(root->opr[3] != NULL && statement == FOR_STATEMENT)
		 			{
		 				gen_code(root->opr[3]);
		 			}
					if(statement == DOWHILE_STATEMENT || statement == WHILE_STATEMENT)
					{
						go_very_long(get_label(labelIndex1));
						create_label(get_label(labelIndex2));
					}
				break;
			}
			goto end_of_cond;
		break;

		default :
			if(DOWHILE_STATEMENT == statement)
			{
				gen_code(root->opr[1]);
			}
			create_operation(node);
		break;
	}

	switch(statement)
	{
		case IF_STATEMENT:
			if(root != NULL && root->opr[2] != NULL) // there is a ELSE
			{
				GOYES(get_label(labelIndex1));
				gen_code(root->opr[1]);
				go_very_long(get_label(labelIndex2));
				create_comment("--- ELSE ---"); 								// to delete for debug in dump file
				create_label(get_label(labelIndex1));
				gen_code(root->opr[2]);
				create_label(get_label(labelIndex2));
				create_comment("-- ENDELSE --"); 								// to delete for debug in dump file
			}
			else
			{
				GOYES(get_label(labelIndex1));
				gen_code(root->opr[1]);
				go_very_long(get_label(labelIndex1));
				create_label(get_label(labelIndex1));
			}
		break;

		case DOWHILE_STATEMENT:

			
			GOYES(get_label(labelIndex2));	
			go_very_long(get_label(labelIndex1));
			create_label(get_label(labelIndex2));
		break;

		case WHILE_STATEMENT:
			GOYES(get_label(labelIndex2));	
			if(root->opr[1] != NULL)
 			{
				gen_code(root->opr[1]);
 			}
			go_very_long(get_label(labelIndex1));
			create_label(get_label(labelIndex2));

		break;


		case FOR_STATEMENT:
			GOYES(get_label(labelIndex2));	
			if(root->opr[3] != NULL)
 			{
				gen_code(root->opr[3]);
 			}
 			// -- incrementing the variable
 			switch(root->opr[2]->opr[1]->nature)
			{
				case NODE_PRIO:
					create_operation(root->opr[2]->opr[1]->opr[0]);
					load_pointer(D0, root->opr[2]->opr[0]->address);
					writing_memory(D0, A, W_FIELD);
				break;

				case NODE_INTVAL:
				case NODE_BOOLVAL:
				case NODE_FLOATVAL:
				case NODE_IDENT:
					affect_variable(root->opr[2]);
				break;

				default:
					create_operation(root->opr[2]->opr[1]);
					load_pointer(D0, root->opr[2]->opr[0]->address);
					writing_memory(D0, A, W_FIELD);
				break;
			}
			// --
			go_very_long(get_label(labelIndex1));
			create_label(get_label(labelIndex2));
		break;
	}

end_of_cond: // jump for skip when cond is always false
	
	g_isBlockParsed = true; // force block parsing
}

/* -------------------------------------------------------------- */

/* --------------- Actually generating the codes ---------------- */

void gen_code(node_t root) 
{
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
						// pointer = address
						load_pointer(D0, root->opr[i]->opr[0]->address);
						if(root->opr[i]->opr[1] != NULL)
						{
							// A = value
							load_register(root->opr[i]->opr[1]->value, 0);
						}
						else // IF NO VALUE : VALUE = 0
						{
							// A = value
							load_register(0, 0);
						}
						// exchange A and DAT
						writing_memory(D0, A, W_FIELD);
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
					if (root->opr[i+1] != NULL && root->opr[i+1]->nature == NODE_BLOCK )
					{
						gen_code(root->opr[i+1]);
						g_isBlockParsed = true;
					}
					if(root->nature != NODE_FOR)
					{
						switch(root->opr[i]->opr[1]->nature)
						{
							case NODE_PRIO:
								create_operation(root->opr[i]->opr[1]->opr[0]);
								load_pointer(D0, root->opr[i]->opr[0]->address);
								writing_memory(D0, A, W_FIELD);
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
							break;
						}
					}
				break;
				
				// creation of the If Statement
				case NODE_IF :
					create_comment("--- IF ---"); 										// to delete for debug in dump file
					g_countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i]->opr[0], root->opr[i], g_curLabelIdx, IF_STATEMENT);
					g_countInCond--; 														// = 0 for recursion, last exit point
					create_comment("-- ENDIF --"); 										// to delete for debug in dump file
				break;

				// creation of the Do While loop
				case NODE_DOWHILE :
					create_comment("--- DOWHILE ---");
					create_new_label(g_curLabelIdx);
					create_label(get_label(g_curLabelIdx-1));
					g_countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i]->opr[0], root->opr[i], g_curLabelIdx-1, DOWHILE_STATEMENT);
					g_countInCond--; 														// = 0 for recursion, last exit point
					create_comment("--- ENDDOWHILE ---");
				break;

				// creation of the While loop
				case NODE_WHILE :
					create_comment("--- WHILE ---");
					create_new_label(g_curLabelIdx);
					create_label(get_label(g_curLabelIdx-1));
					g_countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i]->opr[0], root->opr[i], g_curLabelIdx-1, WHILE_STATEMENT);
					g_countInCond--; 														// = 0 for recursion, last exit point
					create_comment("--- ENDWHILE ---");
				break;


				
				// creation of FOR loop
				case NODE_FOR :
					create_comment("--- FOR --- ");
					create_new_label(g_curLabelIdx);
					create_label(get_label(g_curLabelIdx-1));
					// -- affectation for looping variable
					switch(root->opr[i]->opr[0]->opr[1]->nature)
					{
						case NODE_PRIO:
							create_operation(root->opr[i]->opr[0]->opr[1]->opr[0]);
							load_pointer(D0, root->opr[i]->opr[0]->opr[0]->address);
							writing_memory(D0, A, W_FIELD);
						break;

						case NODE_INTVAL:
						case NODE_BOOLVAL:
						case NODE_FLOATVAL:
						case NODE_IDENT:
							affect_variable(root->opr[i]->opr[0]);
						break;

						default:
							create_operation(root->opr[i]->opr[0]->opr[1]);
							load_pointer(D0, root->opr[i]->opr[0]->opr[0]->address);
							writing_memory(D0, A, W_FIELD);
						break;
					}
					// --
					g_countInCond++; 														// = 1 for recursion, first entry point
					create_cond_instruction(root->opr[i]->opr[1], root->opr[i], g_curLabelIdx-1, FOR_STATEMENT);
					g_countInCond--;														// = 0 for recursion, last exit point
					g_isBlockParsed = true;
					create_comment("--- ENDFOR --- ");
				break;

				default:
					// nothing happens
				break;
			}		
		}

		// RECURSION
		if(root->opr[i] != NULL)
		{
			if (!(root->opr[i]->nature == NODE_BLOCK && g_isBlockParsed) && // block managed in the condition
				((root->opr[i]->nature != NODE_ELSE) && (root->opr[i]->nature != NODE_FOR))) // block already parsed 
			{
				gen_code(root->opr[i]);
			}
			else
			{
				g_isBlockParsed = false;
			}
		}
	}
}

 

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

char * get_label(void)
{
	return labelStr;
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
// --------------------------------------------- //

// ------------ OPERATIONS ON BOOL ------------ //

void create_if_instruction(node_t node)
{
	switch(node->opr[0]->nature) // treatement of condition
	{
		case NODE_AND:
		case NODE_OR:
		case NODE_NOT:
		break;
		case NODE_BOOLVAL:
		break;
		default :
			create_operation(node->opr[0]);
		break;
	}
	GOYES(get_label());
	gen_code_passe_2(node->opr[1]);
	blockParsed = 1; // force block parsing
}

// dupe above for every condition possible
// NODE_AND
// NODE_OR
// NODE_NOT

// -------------------------------------------- //


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
		// exchnage A and DAT
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
		// exchnage A and DAT
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

// create operation on int/float
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
				// exchnage A and DAT
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
								logical_AND(A, C, W_FIELD);
							break;
							case NODE_BXOR :
								logical_AND(A, C, W_FIELD);
							break;
							case NODE_LT :
								register_LT(A, C, W_FIELD);
							break;
							case NODE_GT :
								register_GT(A, C, W_FIELD);
							break;
							case NODE_EQ :
								register_equal(A, C, W_FIELD);
							break;
							case NODE_NE :
								register_not_equal(A, C, W_FIELD);
							break;
							case NODE_GE :
								register_GTE(A, C, W_FIELD);
							break;
							case NODE_LE :
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
								logical_AND(A, C, W_FIELD);
							break;
							case NODE_BXOR :
								logical_AND(A, C, W_FIELD);
							break;
							case NODE_LT :
								register_LT(A, C, W_FIELD);
							break;
							case NODE_GT :
								register_GT(A, C, W_FIELD);
							break;
							case NODE_EQ :
								register_equal(A, C, W_FIELD);
							break;
							case NODE_NE :
								register_not_equal(A, C, W_FIELD);
							break;
							case NODE_GE :
								register_GTE(A, C, W_FIELD);
							break;
							case NODE_LE :
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
				// exchnage A and DAT
				reading_memory(D0, A, W_FIELD);
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
						logical_AND(A, C, W_FIELD);
					break;
					case NODE_BXOR :
						logical_AND(A, C, W_FIELD);
					break;
					case NODE_LT :
						register_LT(A, C, W_FIELD);
					break;
					case NODE_GT :
						register_GT(A, C, W_FIELD);
					break;
					case NODE_EQ :
						register_equal(A, C, W_FIELD);
					break;
					case NODE_NE :
						register_not_equal(A, C, W_FIELD);
					break;
					case NODE_GE :
						register_GTE(A, C, W_FIELD);
					break;
					case NODE_LE :
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
						logical_AND(A, C, W_FIELD);
					break;
					case NODE_BXOR :
						logical_AND(A, C, W_FIELD);
					break;
					case NODE_LT :
						register_LT(A, C, W_FIELD);
					break;
					case NODE_GT :
						register_GT(A, C, W_FIELD);
					break;
					case NODE_EQ :
						register_equal(A, C, W_FIELD);
					break;
					case NODE_NE :
						register_not_equal(A, C, W_FIELD);
					break;
					case NODE_GE :
						register_GTE(A, C, W_FIELD);
					break;
					case NODE_LE :
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


// every integrer/float operation possible
// NODE_SLL		TO DO BUT ANNOYING
// NODE_SRL		TO DO BUT ANNOYING

// ------------------------------------------------- //

/* -------------------------------------------------------------- */

/* --------------------- Parsing functions ---------------------- */

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
						case NODE_PRIO:
							create_operation(root->opr[i]->opr[1]->opr[0]);
						break;
						default:
							create_operation(root->opr[i]->opr[1]);
						break;
					}
					load_pointer(D0, root->opr[i]->opr[0]->address);
					writing_memory(D0, A, W_FIELD);
					flush_save_reg(); // reset save_reg pointers from our side : to test if useful
				break;
				
				// //loop instruction determination
				// case NODE_LT :
				// case NODE_GT :
				// case NODE_EQ :
				// case NODE_NE :
				// case NODE_GE :
				// case NODE_LE :
				// 	printf("bool condition\n");
				// break;

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
					create_comment("--- IF ---");
					inIf = 1;
					label_formatting();
					create_if_instruction(root->opr[i]);
					create_label(get_label());
					create_comment("-- ENDIF --");
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
			else
			{
				blockParsed = 0;
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

 

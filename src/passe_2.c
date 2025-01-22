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
	short index;
	create_comment(node->opr[0]->ident);
	// TO DO OPTIMIZE THE VALUE
	if(node->opr[1] != NULL)
	{
		if(node->opr[1]->type == NODE_IDENT)
		{
			index = get_node_ident(T_SAVE, node->opr[1]->ident);
			if(index >= 0)
			{
				switch (node->opr[1]->type)
				{
					case TYPE_INT:
					case TYPE_FLOAT:
						load_register(get_node_val(T_SAVE, index)->value, 0);
					break;
					default :
					break;
				}
			}
		}
		else
		{
			switch (node->opr[1]->type)
			{
				case TYPE_INT:
				case TYPE_FLOAT:
					load_register(node->opr[1]->value, 0);
				break;
				default :
				break;
			}
		}
	}
	else
	{
		load_register(0, 0); // default value = 0 => maybe not save it for optimisation ? 
	}
	if(save_reg_available() >= 0)
	{
		ex_reg_work_save(A, save_reg_available(), W_FIELD); // global var => in save reg direct
		add_node_register(T_SAVE, node->opr[1], node->opr[0], save_reg_available());
	}
}

// affectation of a variable
void affect_variable(node_t node)
{
	// affetcation = UPDATE NODES 

	// affect an ident with an ident
	if(node->opr[0]->nature == NODE_IDENT && 
		node->opr[1]->nature == NODE_IDENT)
	{
		switch(node->opr[0]->type)
		{
			case TYPE_INT:
			case TYPE_FLOAT:
				node->opr[0]->value = node->opr[1]->value;
			break;
			default :
			break;
		}
	}

	// affect an ident with a intval
	if((node->opr[0]->nature == NODE_IDENT && 
		node->opr[0]->type == TYPE_INT) && 
		(node->opr[1]->nature == NODE_INTVAL))
	{
	}

	// affect an ident with a floatval
	if((node->opr[0]->nature == NODE_IDENT && 
		node->opr[0]->type == TYPE_FLOAT)&& 
		(node->opr[1]->nature == NODE_FLOATVAL))
	{
	}

	// affect an ident with a boolval
	if((node->opr[0]->nature == NODE_IDENT && 
		node->opr[0]->type == TYPE_BOOL) && 
		node->opr[1]->nature == NODE_BOOLVAL)
	{	
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
			case NODE_SRA :
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


// create an addition
void create_plus_instr(node_t node)
{
	short index;
	// check register available
	if(node->opr[0]->nature == NODE_IDENT)
	{
		index = get_node_ident(T_SAVE, node->opr[0]->ident);
		if(index >= 0)
		{
			ex_reg_work_save(A, index, W_FIELD);
		}
	}

	// handling multiples operations
	else if (node->opr[0]->nature == NODE_PLUS)
	{
		create_plus_instr(node->opr[0]);
	}
	else
	{
		switch (node->opr[0]->type)
		{
			case TYPE_INT:
			case TYPE_FLOAT:
				add_const_register(A, W_FIELD, node->opr[0]->value);
			break;
			default :
			break;
		}
	}
	if(node->opr[1]->nature == NODE_IDENT)
	{
		index = get_node_ident(T_SAVE, node->opr[1]->ident);
		if(index >= 0)
		{
			ex_reg_work_save(A, index, W_FIELD);
		}
	}
	else if (node->opr[1]->nature == NODE_PLUS)
	{
		create_plus_instr(node->opr[1]);
	}
	else
	{
		switch (node->opr[1]->type)
		{
			case TYPE_INT:
			case TYPE_FLOAT:
				add_const_register(A, W_FIELD, node->opr[1]->value);
			break;
			default :
			break;
		}
	}
}

// dupe above for every operation possible
// NODE_PLUS
// NODE_MINUS
// NODE_UMINUS
// NODE_MUL
// NODE_DIV
// NODE_MOD
// NODE_BAND
// NODE_BOR
// NODE_BXOR
// NODE_BNOT
// NODE_AND
// NODE_OR
// NODE_NOT
// NODE_SRA
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
							switch (root->opr[i]->opr[1]->type)
							{
								case TYPE_INT:
								case TYPE_FLOAT:
									load_register(root->opr[i]->opr[1]->value, 0);
								break;
								default :
								break;
							}
						}
						else
						{
							load_register(0, 0); // default value = 0 => maybe not save it for optimisation ? 
						}
						if(save_reg_available() >= 0)
						{
							ex_reg_work_save(A, save_reg_available(), W_FIELD); // global var => in save reg direct
							add_node_register(T_SAVE, root->opr[i]->opr[1], root->opr[i]->opr[0], save_reg_available());
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
					create_comment("label for main (useless ?)");
					create_label("MAIN_FUNC");
				break;		

				case NODE_AFFECT :
					// in 'for' loop block must be parsed before incrementing the index
					if (root->opr[i+1] != NULL && root->opr[i+1]->nature == NODE_BLOCK)
					{
						gen_code_passe_2(root->opr[i+1]);
						blockParsed = 1;
					}

					// instruction creation
					if (root->opr[i]->opr[1]->nature == NODE_PLUS)
					{
						create_plus_instr(root->opr[i]->opr[1]);
					}
					if (root->opr[i]->opr[1]->nature == NODE_MINUS)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_UMINUS)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_MUL)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_DIV)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_MOD)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_BAND)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_BOR)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_BXOR)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_BNOT)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_AND)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_OR)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_NOT)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_SRA)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_SLL)
					{
					}
					if (root->opr[i]->opr[1]->nature == NODE_SRL)
					{
					}
					else
					{
					}
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
					label++;
					// create a label
					break;

				// creation of the Do While loop
				case NODE_DOWHILE :
					label++;
					// create a label
					break;

				// creation of the If Statement
				case NODE_IF :
					inIf = 1;
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

 

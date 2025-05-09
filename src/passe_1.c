// ========================================
// > Author :   jugen 667 
// > Title  :   passe_1.c 
// > Desc.  :   First parse to check tree
//				and program consistence
// > Associated header : passe_1.h
// ========================================

// ================================================================================================= //
// =========================================== INCLUDES ============================================ //
// ================================================================================================= //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/defs.h"
#include "../include/passe_1.h"
#include "../include/common.h"


// ================================================================================================= //
// ========================================== PROTOTYPES =========================================== //
// ================================================================================================= //

static decl_table declaration_table[VAR_MAX_NUMBER]; // max 32 variable

extern int trace_level;

// ================================================================================================= //
// =========================================== GLOBALS ============================================= //
// ================================================================================================= //

short currentVar = -1; 		// declaration index 
bool declaration = 0;		// in a declaration part
bool isGlobal = 1;			// in global scope
node_type current_type= 0;  // typing nodes

// ================================================================================================= //
// =========================================== FUNCTIONS =========================================== //
// ================================================================================================= //

/* ========================= Debug funcs ========================= */
void print_decl_table(void)
{
	for (int i=0; i < VAR_MAX_NUMBER; i++)
	{
		if (declaration_table[i].node == NULL)
		{
			printf("\n"); 	
			break;
		}
		printf("Variable n°%d - %s | ", i, declaration_table[i].varName);
	}
}

// ------------------------------------------------------------------------------------------------- //

void print_node_info(node_t root)
{
	printf("Node Nature:%s \t\t| Node Type:%s \t\t| Nbr. Ops:%d\t\t|\n",node_nature2string(root->nature), node_type2string(root->type), root->nops);
}

// ------------------------------------------------------------------------------------------------- //

/* ========================= Check-Up functions ========================= */

bool check_var_number(void)
{
	if(currentVar <= VAR_MAX_NUMBER)
	{
		return true;
	}
	return false;
}

// ------------------------------------------------------------------------------------------------- //

void check_ident_size(node_t node)
{
	if(strlen(node->ident) > VAR_MAX_SIZE)
	{
		printf(RED "Error line" BOLD " %d " NC ": identifier name too long (max character : %d)\n", node->lineno, VAR_MAX_SIZE);
		exit(EXIT_FAILURE);
	}
}

// ------------------------------------------------------------------------------------------------- //

// reading a declaration table : returns a pointer to a node
node_t get_decl_node(node_t node) 
{
	for(short i = 0; i <= currentVar; i++)
	{
		if(strncmp(declaration_table[i].varName, node->ident, VAR_MAX_SIZE))
		{
			// diff in strings : not the droid we are looking for
			continue;
		}
		else
		{
			return(declaration_table[i].node);
		}
	}
	return NULL;
}

// ------------------------------------------------------------------------------------------------- //

void add_decl_node(node_t node) 
{
	// checks on ident
	check_ident_size(node);
	if(check_var_number){					
		if(currentVar == -1 || get_decl_node(node) == NULL)
		{
			currentVar++;
			declaration_table[currentVar].node = node;
			strncpy(declaration_table[currentVar].varName,node->ident, VAR_MAX_SIZE);
		} 
	}
	else
	{
		printf(RED "Error line" BOLD " %d " NC ": variable number overflow (max variable : %d)\n", node->lineno, VAR_MAX_NUMBER);
		exit(EXIT_FAILURE);
	}
}

// ------------------------------------------------------------------------------------------------- //

// check that operations have 2 same types
void check_int_op_type(node_t node)
{
	if (node->opr[0]->type && node->opr[1]->type) // type != NONE
	{	
		if(node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT) 
		{
			printf(RED "Error line" BOLD " %d " NC ": operator " BOLD "%s" NC " wrong type on left operand\n", node->opr[0]->lineno, node_nature2symb(node->nature));
			exit(EXIT_FAILURE);
		}
		else if(node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT)
		{
			printf(RED "Error line" BOLD " %d " NC ": operator " BOLD "%s" NC " wrong type on right operand\n", node->opr[1]->lineno, node_nature2symb(node->nature));
			exit(EXIT_FAILURE);
		}
	}
	// case 'ident + number for' ex and recursion
	else if (node->opr[0]->nature == NODE_PLUS)
	{
		check_int_op_type(node->opr[0]);
	}
	else if (node->opr[1]->nature == NODE_PLUS)
	{
		check_int_op_type(node->opr[1]);
	}
}

// ------------------------------------------------------------------------------------------------- //

// check that IF, DOWHILE, WHILE and FOR gives boolean type expression
void check_bool_cond(node_t node, int positionnal)
{
	if (node->opr[positionnal]->type != TYPE_BOOL && 
		node->opr[positionnal]->type != TYPE_INT && 
		node->opr[positionnal]->type != TYPE_FLOAT && 
		node->opr[positionnal]->type != TYPE_NONE)
	{
		switch(node->nature)
		{
			case NODE_IF:
			case NODE_WHILE :
			case NODE_DOWHILE :
			case NODE_FOR :
				printf(RED "Error line" BOLD " %d " NC ": " BOLD CYAN "%s" NC " statement incorrect\n", node->opr[0]->lineno, node_nature2string(node->nature));
				exit(EXIT_FAILURE);
			break;

			default:
			break;
		}
	}
}

// ------------------------------------------------------------------------------------------------- //

// check that boolean operations are between 2 same types
void check_bool_op(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type)
		{
			if (node->opr[0]->type != node->opr[1]->type)
			{	
				printf(RED "Error line" BOLD " %d " NC ": operation " BOLD "%s" NC " only between " PURPLE "bool" NC " variables\n", node->opr[0]->lineno, node_nature2symb(node->nature));
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (node->opr[0]->type != TYPE_BOOL && node->opr[0]->nature != NODE_PRIO)
		{	
			printf(RED "Error line" BOLD " %d " NC ": operation " BOLD "%s" NC " only between " PURPLE "bool" NC " variables\n", node->opr[0]->lineno, node_nature2symb(node->nature));
			exit(EXIT_FAILURE);
		}
	}

}

// ------------------------------------------------------------------------------------------------- //

void check_int_op(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type)
		{
			if ((node->opr[0]->type != node->opr[1]->type) ||
				((node->opr[0]->type != TYPE_INT) ||
				 (node->opr[1]->type != TYPE_INT)))
			{	
				printf(RED "Error line" BOLD " %d " NC ": operation " BOLD "'%s'" NC " only between " PURPLE "int" NC " variables\n", node->opr[0]->lineno, node_nature2symb(node->nature));
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (node->opr[0]->type != TYPE_INT && node->opr[0]->nature != NODE_PRIO) 
		{	
			printf(RED "Error line" BOLD " %d " NC ": operation " BOLD "'%s'" NC " only between " PURPLE "int" NC " variables\n", node->opr[0]->lineno, node_nature2symb(node->nature));
			exit(EXIT_FAILURE);
		}
	}
}

// ------------------------------------------------------------------------------------------------- //

void check_same_type(node_t node) // return a warning but will compile
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type)
		{
			if ((node->opr[0]->type != node->opr[1]->type))
			{	
				printf(PURPLE "Warning line" BOLD " %d " NC ": operation " BOLD "'%s'" NC " between %s and %s\n", node->opr[0]->lineno, node_nature2symb(node->nature), node_type2string(node->opr[0]->type), node_type2string(node->opr[1]->type));
			}
		}
	}
	else
	{
		// not possible but ...
		if (node->opr[0]->type != TYPE_INT && node->opr[0]->nature != NODE_PRIO) 
		{	
			printf(PURPLE "Warning line" BOLD " %d " NC ": operation " BOLD "'%s'" NC " between %s and %s\n", node->opr[0]->lineno, node_nature2symb(node->nature), node_type2string(node->opr[0]->type), node_type2string(node->opr[1]->type));
		}
	}
}

// ------------------------------------------------------------------------------------------------- //

// check that affect are same types
void check_affect_type(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type) 
	    {
			if ((node->opr[0]->type != node->opr[1]->type) &&
				((node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT) ||
				 (node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT))) 
			{	
				printf(RED "Error line" BOLD " %d " NC ": incompatible affectation\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
			else
			{
				node->type = node->opr[0]->type;  //type of root node = type of the operation
			}
		}
		// check that FLOAT are not considered INTVAL and that float value are not affected to INT
		if (node->opr[0]->type != node->opr[1]->type) 
	    {
			if(node->opr[0]->type == TYPE_INT && node->opr[1]->type == TYPE_FLOAT)
	    	{
	    		printf(RED "Error line" BOLD " %d " NC ": " PURPLE "float" NC " value on " PURPLE "int" NC " variable\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
	    	}
	    	else if((node->opr[0]->type == TYPE_FLOAT && node->opr[1]->type == TYPE_INT)) // not a problem but warning
	    	{
	    		printf(PURPLE "Error line" BOLD " %d " NC ": integer value assigned to a float variable '%s'\n", node->opr[0]->lineno, node->opr[0]->ident);
	    	}

	    }
	}
}

// ------------------------------------------------------------------------------------------------- //

// check that global declaration are not expression
void check_global_decl(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->global_decl)
		{
			if (	(node->opr[1]->nature != NODE_INTVAL)
				&&  (node->opr[1]->nature != NODE_BOOLVAL)
				&& 	(node->opr[1]->nature != NODE_FLOATVAL))
			{
				printf(RED "Error line" BOLD " %d " NC ": global variables not constant\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------- //

// ================================================================================================= //

/* ========================= Tree parsing ========================= */

void analyse_passe_1(node_t root) 
{	
	node_t variableDecl;
	
	// printf("declaration flag : %d\n", declaration);
	if (root->nature == NODE_PROGRAM)
	{
		//flag to update the global_decl attribute
		isGlobal=1; 
	}
	if (root->nature == NODE_FUNC)
	{ 
		//flag to update the global_decl attribute
		isGlobal=0; 
	}
	// parsing the tree
	for(int i = 0; i < root->nops; i++)
	{
		if(root->opr[i] != NULL)
		{
			switch(root->opr[i]->nature)
			{
				case NODE_TYPE :
					if (root->opr[i]->type != TYPE_NONE)
					{
						current_type = root->opr[i]->type;
					}
					declaration = 1;
				break;

				case NODE_INTVAL :
					root->opr[i]->type = TYPE_INT;
				break;

				case NODE_BOOLVAL :
					root->opr[i]->type = TYPE_BOOL;
				break;

				case NODE_FLOATVAL :
					root->opr[i]->type = TYPE_FLOAT;
				break;

				case NODE_PRIO :
					root->opr[i]->isPrio = true;
					if(root->opr[i]->opr[0] != NULL)
					{
						root->opr[i]->opr[0]->isPrio = true;
					}
				break;


				case NODE_IDENT :
					// Check if variable has been declared already
					variableDecl = get_decl_node(root->opr[i]);  // 2 ENTRY ARRAY FOR IDENT ASSOCIATION WITH A NODE
					root->opr[i]->type = current_type; 
					
					// if first time seeing the ident (not fully operationnal : to pair with declaration flag)
					if (variableDecl == NULL && declaration == 1)
					{
						//If undeclared, we add it to the table
						root->opr[i]->address = assign_address();
						add_decl_node(root->opr[i]);
						declaration = 0;
					}
					else 
					{
						// Else we get the address of declaration and associate it with the current variable
						// using the variable
						if (variableDecl != NULL && declaration == 0)
						{
							root->opr[i]->address = variableDecl->address;
							root->opr[i]->global_decl = variableDecl->global_decl;
							root->opr[i]->type = variableDecl->type;
							switch(root->opr[i]->type)
							{
    							case TYPE_INT :
							    case TYPE_FLOAT :
									root->opr[i]->value = variableDecl->value;
								break;
								default :
								break;  
							}
						}
						// if trying to re declare	
						else if(variableDecl != NULL && declaration == 1)
						{
							printf(RED "Error line" BOLD " %d " NC ": variable " BOLD "'%s'" NC " already declared : previous declaration line %d\n", root->opr[i]->lineno, root->opr[i]->ident, variableDecl->lineno);
							exit(EXIT_FAILURE);
						}
						// if undeclared
						else 
						{
							printf(RED "Error line" BOLD " %d " NC ": undeclared variable " BOLD "'%s'" NC" \n", root->opr[i]->lineno, root->opr[i]->ident);
							exit(EXIT_FAILURE);
						}					
					}
					// Update of the global_decl
					if(isGlobal && !root->opr[i]->global_decl)
					{
						root->opr[i]->global_decl = true;
					}
				break;
					
				// Operators that returns int expressions (do with float too)
				case NODE_DIV :
				case NODE_MUL :
				case NODE_MOD :
					root->opr[i]->isPrio = true;
				case NODE_PLUS :
				case NODE_MINUS :
				case NODE_UMINUS :
				case NODE_BNOT :
				case NODE_BAND :
				case NODE_BOR :
				case NODE_BXOR :
				case NODE_SRL :
				case NODE_SLL :
					root->opr[i]->type = TYPE_INT;
				break;

				// Operators that returns boolean expressions
				case NODE_EQ :
				case NODE_NE :
				case NODE_LT :
				case NODE_GT :
				case NODE_LE : 
				case NODE_GE :
				case NODE_AND :
				case NODE_OR :
				case NODE_NOT :
					root->opr[i]->type = TYPE_BOOL;
				break;

				case NODE_DECL :
					declaration = 1;
				break;

				case NODE_BLOCK :
					isGlobal=0;
					declaration = 0;
				break;

				case NODE_AFFECT :
				break;

				case NODE_FUNC :
					root->opr[i]->address = assign_address();
			    	add_decl_node(root->opr[i]);
					root->opr[i]->type = TYPE_VOID;
				break;
	
				case NODE_STRINGVAL :
				break;

				default:
				break;			
			}	
		}

		//Recursion 
		if(root->opr[i] != NULL)
		{
			analyse_passe_1(root->opr[i]);
		}

		// CHECKS 
		if(root->nature == NODE_FUNC)
		{
			if(root->type != TYPE_VOID)
			{
				printf(RED "Error line" BOLD " %d " NC ": " BOLD CYAN "main()" NC " declaration must have " PURPLE "void" NC " return type\n", root->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
			if(strcmp(root->ident, "main")) // only 1 func allowed : main -- REDUNDANT checks done at syntax
			{
				printf(RED "Error line" BOLD " %d " NC ": function name must be " BOLD CYAN "main()" NC " \n", root->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
		}
		// check that operations are between INT
		if(root->nature == NODE_PLUS ||
		   root->nature == NODE_MINUS || 
		   root->nature == NODE_MUL ||
		   root->nature == NODE_DIV ||
		   root->nature == NODE_MOD)
		{
			check_int_op_type(root);
		}
		// check that condition returns boolean 
		if(	root->nature == NODE_DOWHILE ||
			root->nature == NODE_FOR)
		{
			//the 'do_while' & 'for' bool expression is the second son
			if(root->opr[1] != NULL)
				check_bool_cond(root, 1);
		}
		if (root->nature == NODE_WHILE ||
			root->nature == NODE_IF )
		{
			//the 'if' & 'while' bool expression is the first son
			check_bool_cond(root, 0);
		}
		// check the coherence of type affectation
		if(root->nature == NODE_AFFECT)
		{
			check_affect_type(root);

		}
		if(root->nature == NODE_DECLS){
			if (root->opr[0]->type && root->opr[1]->type)
			{
				if (root->opr[0]->type != root->opr[1]->type)
				{
					printf(RED "Error line" BOLD " %d " NC ": variable already declared\n", root->lineno);
					exit(EXIT_FAILURE);
				}	
			}
		}
		if(root->nature == NODE_DECL)
		{
			// check the global declaration : not an expression and check the coherence of the types
			root->type = root->opr[0]->type;
			check_global_decl(root);
			check_affect_type(root);
		}
		
		// case if(...) else ...
		if(root->nature == NODE_IF && root->nops == 3)
		{
			// if 3 node then 3rd is else statement (to check) (statement, block, else)
			root->opr[2]->nature = NODE_ELSE;
		}

		// check if the type is the same for the two arguments
		if(	root->nature == NODE_EQ ||
			root->nature == NODE_NE ||
			root->nature == NODE_LT ||
			root->nature == NODE_GT ||
			root->nature == NODE_LE ||
			root->nature == NODE_GE ||
			root->nature == NODE_BNOT ||
			root->nature == NODE_BAND ||
			root->nature == NODE_BOR ||
			root->nature == NODE_BXOR ||
			root->nature == NODE_SRL ||
			root->nature == NODE_SLL )
		{
			check_same_type(root);
		}

	}
}

// ================================================================================================= //
// ================================================================================================= //
// ================================================================================================= //


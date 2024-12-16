// ========================================
// > Author :   jugen 667 
// > Title  :   passe_1.c 
// > Desc.  :   First parse to check tree
//				and program consistence
// > Associated header : passe_1.h
// ========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/defs.h"
#include "../include/passe_1.h"

static decl_table declaration_table[VAR_MAX_NUMBER]; // max 256 variable

extern int trace_level;

// global variables
short currentVar = -1; 		// declaration index (-1 for the case we dont declare variable)
int declaration = 0;		// in a declaration part
int isGlobal = 1;			// in global scope
node_type current_type= 0;  // typing nodes



/* --------------- Check-Up functions --------------- */
bool check_var_number(void)
{
	if(currentVar <= VAR_MAX_NUMBER)
	{
		return true;
	}
	return false;
}

void check_ident_size(node_t node)
{
	if(strlen(node->ident) > VAR_MAX_SIZE)
	{
		printf("Error line %d: identifier name too long (max character : %d)\n", node->lineno, VAR_MAX_SIZE);
		exit(EXIT_FAILURE);
	}
}


// reading a declaration table : returns a pointer to a node
node_t get_decl_node(node_t node) 
{
	for(short i = 0; i < currentVar; i++)
	{
		printf("get decl node : %s\n", declaration_table[i].varName);
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
		printf("Error line %d: variable number overflow (max variable : %d)\n", node->lineno, VAR_MAX_NUMBER);
		exit(EXIT_FAILURE);
	}
}


// check that operations have 2 same types
void check_add_type(node_t node)
{
	if (node->opr[0]->type && node->opr[1]->type)
	{	
		if(node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '+' wrong type on left operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if(node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '+' wrong type on left operand\n", node->opr[1]->lineno);
			exit(EXIT_FAILURE);
		}	
	}
	// case 'ident + number for' ex
	else if (node->opr[0]->nature == NODE_PLUS)
	{
		check_add_type(node->opr[0]);
	}
	else if (node->opr[1]->nature == NODE_PLUS)
	{
		check_add_type(node->opr[1]);
	}
}

void check_minus_type(node_t node)
{
	if (node->opr[0]->type && node->opr[1]->type)
	{
		if(node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '-' wrong type on left operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if(node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT )
		{
			printf("Error line %d: operator '-' wrong type on left operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
	}
	// case 'ident - number' for ex
	else if (node->opr[0]->nature == NODE_MINUS)
	{
		check_minus_type(node->opr[0]);
	}
	else if (node->opr[1]->nature == NODE_MINUS)
	{
		check_minus_type(node->opr[1]);
	}
}

void check_mul_type(node_t node)
{
	if (node->opr[0]->type && node->opr[1]->type)
	{		
		if(node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '*' wrong type on left operand \n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if(node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '*' wrong type on right operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
	}
	// case 'ident * number' for ex
	else if (node->opr[0]->nature == NODE_MUL)
	{
		check_mul_type(node->opr[0]);
	}
	else if (node->opr[1]->nature == NODE_MUL)
	{
		check_mul_type(node->opr[1]);
	}
}

void check_div_type(node_t node)
{
	if (node->opr[0]->type && node->opr[1]->type)
	{		
		if(node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT)
		{
				printf("Error line %d: operator '/' wrong type on left operand\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
		}
		else if(node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '/' wrong type on left operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
	}	
	// case 'ident / number' for ex
	else if (node->opr[0]->nature == NODE_DIV)
	{
		check_div_type(node->opr[0]);
	}
	else if (node->opr[1]->nature == NODE_DIV)
	{
		check_div_type(node->opr[1]);
	}
}

void check_mod_type(node_t node)
{
	if (node->opr[0]->type && node->opr[1]->type)
	{		
		if(node->opr[0]->type != TYPE_INT && node->opr[0]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '%%' wrong type on left operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if(node->opr[1]->type != TYPE_INT && node->opr[1]->type != TYPE_FLOAT)
		{
			printf("Error line %d: operator '%%' wrong type on left operand\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}	
	}
	// case 'ident % number' for ex
	else if (node->opr[0]->nature == NODE_MOD)
	{
		check_div_type(node->opr[0]);
	}
	else if (node->opr[1]->nature == NODE_MOD)
	{
		check_div_type(node->opr[1]);
	}
}

// check that IF, DOWHILE, WHILE and FOR gives boolean type expression
void check_bool_expr(node_t node, int positionnal)
{
	if (node->opr[positionnal]->type != TYPE_BOOL && node->opr[positionnal]->type != TYPE_NONE)
	{
		if (node->nature == NODE_IF)
		{
			printf("Error line %d: 'if' statement incorrect\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if (node->nature == NODE_WHILE)
		{
			printf("Error line %d: 'while' statement incorrect\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if (node->nature == NODE_DOWHILE)
		{
			printf("Error line %d: 'do ... while' statement incorrect\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
		else if (node->nature == NODE_FOR)
		{
			printf("Error line %d: 'for' statement incorrect\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
	}
}

// check that boolean operations are between 2 same types
void check_bool_op(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type)
		{
			if (node->opr[0]->type != node->opr[1]->type)
			{	
				printf("Error line %d: non 'bool' operands\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (node->opr[0]->type != TYPE_BOOL)
		{	
			printf("Error line %d: non 'bool' operands\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
	}

}

// unecessary float and int can coexist*
// =====================================================================================
void check_int_op(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type)
		{
			if (node->opr[0]->type != node->opr[1]->type)
			{	
				printf("Error line %d: non 'int' or 'float' operands\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		if (node->opr[0]->type != TYPE_INT || node->opr[0]->type != TYPE_FLOAT)
		{	
			printf("Error line %d: non 'int' or 'float' operands\n", node->opr[0]->lineno);
			exit(EXIT_FAILURE);
		}
	}
}
// =====================================================================================

// check that affect are same types
void check_affect_type(node_t node)
{
	if (node->opr[1] != NULL)
	{
		if (node->opr[0]->type && node->opr[1]->type)
		{
			if (node->opr[0]->type != node->opr[1]->type)
			{	
				printf("Error line %d: uncompatible affectation\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
			else
			{
				node->type = node->opr[0]->type;  //type of root node = type of the operation
			}
		}
	}
}

// check that global declaration are not expression
void check_global_decl(node_t node){
	if (node->opr[1] != NULL){
		if (node->opr[0]->global_decl){
			if (	(node->opr[1]->nature != NODE_INTVAL)
				&&  (node->opr[1]->nature != NODE_BOOLVAL)
				&& 	(node->opr[1]->nature != NODE_FLOATVAL)){
				printf("Error line %d: global variables not constant\n", node->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
		}
	}
}

// to do better and add a float version
void check_intval_domain(node_t node){
	if(node->int_value > 0xffffffff7fffffff){
		printf("Error line %d: integer out of range\n", node->lineno);
		exit(EXIT_FAILURE);
	}
}





/* --------------- Tree parsing --------------- */

void analyse_passe_1(node_t root) 
{	
	node_t variableDecl;
	if (root->nature == NODE_PROGRAM)
	{
		//flag to update the global_decl attribute
		isGlobal=1; 
	}	

	// parsing the tree
	for(int i = 0; i < root->nops; i++)
	{
		if(root->opr[i] != NULL)
		{
			printf("declaration %d | node_type : %d\n",declaration,root->opr[i]->type);
			switch(root->opr[i]->nature)
			{
				case NODE_TYPE :
					if (root->opr[i]->type != 0)
					{
						current_type = root->opr[i]->type;
					}
					declaration = 1;
				break;

				case NODE_INTVAL :
				case NODE_FLOATVAL :
					check_intval_domain(root->opr[i]);
					// add float range 
				break;

				case NODE_IDENT : // ENHANCE 
					// Check if variable has been declared already
					variableDecl = get_decl_node(root->opr[i]);  // 2 ENTRY ARRAY FOR IDENT ASSOCIATION WITH A NODE

					// If ident == 'main' => setup the type to void and jump to the next node
					if (!(strcmp(root->opr[i]->ident, "main")))
				    {
						root->opr[i]->type = TYPE_VOID;
						break;
					}
					root->opr[i]->type = current_type;
					
					// if first time seeing the ident (not fully operationnal : to pair with declaration flag)
					if (variableDecl == NULL){
						//If undeclared, we add it to the table
						add_decl_node(root->opr[i]);
					}
					else {
						// Else we get the adress of declaration and associate it with the current variable
						// using the variable
						if (variableDecl != NULL && declaration == 0)
						{
							root->opr[i]->offset = variableDecl->offset;
							root->opr[i]->type = variableDecl->type;
							root->opr[i]->global_decl = variableDecl->global_decl;
						}
						// if trying to redeclare	
						else if(variableDecl != NULL && declaration == 1)
						{
							printf("Error line %d : variable '%s' already declared : previous declaration line %d\n", root->opr[i]->lineno, root->opr[i]->ident, variableDecl->lineno);
							exit(EXIT_FAILURE);
						}
						// if undeclared
						else {
							printf("Error line %d : undeclared variable '%s'\n", root->opr[i]->lineno, root->opr[i]->ident);
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
					root->opr[i]->type = TYPE_INT;
				break;

				// Opreators that returns boolean expressions
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
					//declaration = 1; // Correction to apply (not reset) : maybe useless
				break;

				case NODE_BLOCK :
					isGlobal=0;
					//push_context();
					break;

				case NODE_FUNC :
					//reset_env_current_offset();
					break;
	
				case NODE_STRINGVAL :
					// Offset update
					// root->opr[i]->offset = add_string(root->opr[i]->str);
					break;
			}	
		}

		//Recursion 
		if(root->opr[i] != NULL){
			analyse_passe_1(root->opr[i]);
		}
		// get offset of the function
		if(root->nature == NODE_FUNC){
			// root->offset = get_env_current_offset();
			if(root->opr[0]->type != TYPE_VOID){
				printf("Error line %d: 'main()' declaration must have a 'void' return type\n", root->opr[0]->lineno);
				exit(EXIT_FAILURE);
			}
		}
		// check that operations are between INT
		if(root->nature == NODE_PLUS){
			check_add_type(root);
		}
		if(root->nature == NODE_MINUS){
			check_minus_type(root);
		}
		if(root->nature == NODE_DIV){
			check_div_type(root);
		}
		if(root->nature == NODE_MUL){
			check_mul_type(root);
		}
		if(root->nature == NODE_MOD){
			check_mod_type(root);
		}
		// check that condition returns boolean 
		if(	root->nature == NODE_DOWHILE ||
			root->nature == NODE_FOR){
			check_bool_expr(root, 1);
			//the do_while bool expression is the second son
		}
		if (root->nature == NODE_WHILE ||
			root->nature == NODE_IF ){
			check_bool_expr(root, 0);
			//the if & while bool expression is the first son
		}
		// check the coherence of type affectation
		if(root->nature == NODE_AFFECT){
			check_affect_type(root);
		}
		if(root->nature == NODE_DECLS){
			if (root->opr[0]->type && root->opr[1]->type){
				if (root->opr[0]->type != root->opr[1]->type){
					printf("Error line %d: variable already declared\n", root->lineno);
					exit(EXIT_FAILURE);
				}	
			}
		}
		if(root->nature == NODE_DECL ){
			// check the global declaration : not an expression and check the coherence of the types
			root->type = root->opr[0]->type;
			check_global_decl(root);
			check_affect_type(root);
			declaration = 0;
		}
		
		// case if(...) else ...
		if(root->nature == NODE_IF && root->nops == 3){
			// if 3 node then 3rd is else stamenet (to check)
			printf("Debug >> Nops %d\n", root->nops);
			for(int i=0;i<root->nops;i++){
        			printf("Debug >> Nopr %d %d\n", i, root->opr[i]->nature);
    			}
			root->opr[2]->nature = NODE_ELSE;
		}

		// check if the type is the same for the two arguments
		if(	root->nature == NODE_EQ ||
			root->nature == NODE_NE ||
			root->nature == NODE_LT ||
			root->nature == NODE_GT ||
			root->nature == NODE_LE ||
			root->nature == NODE_GE ||
			root->nature == NODE_AND ||
			root->nature == NODE_OR ){
			check_bool_op(root);
		}
		if(	root->nature == NODE_BNOT ||
			root->nature == NODE_BAND ||
			root->nature == NODE_BOR ||
			root->nature == NODE_BXOR||
			root->nature == NODE_SRL||
			root->nature == NODE_SRA ||
			root->nature == NODE_SLL ){
			check_int_op(root);
		}
	}
}

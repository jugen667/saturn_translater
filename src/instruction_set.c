// ========================================
// > Author :   jugen 667 
// > Title  :   instruction_set.c 
// > Desc.  :   Function for assembly 
//				generation
// > Associated header : instruction_set.h
// ========================================

// ================================================================================================= //
// =========================================== INCLUDES ============================================ //
// ================================================================================================= //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/defs.h"
#include "../include/common.h"
#include "../include/instruction_set.h"


// ================================================================================================= //
// =========================================== GLOBALS ============================================= //
// ================================================================================================= //
static bool available_reg[4] = {1, 1, 1, 1};

// ================================================================================================= //
// =========================================== FUNCTIONS =========================================== //
// ================================================================================================= //

// check if register available for saving data
short reg_available(void)
{
	for (short i = 0; i < 4; i++)
	{
		if(available_reg[i])
		{
			return i;
		}
	}
	return -1;
}
// increment P value of 1
void increment_P(void)
{
	char retStr[6];
	sprintf(retStr, "P=P+1");
	//for debug
	printf("%s\n",retStr);
}

// decrement P value of 1
void decrement_P(void)
{
	char retStr[6];
	sprintf(retStr, "P=P-1");
	//for debug
	printf("%s\n",retStr);
}

// set value of P
void set_PField_value(char value)
{
	char retStr[10];
	sprintf(retStr, "P= %d",(short)value);
	//for debug
	printf("%s\n",retStr);
}

// reset P value (should be called at end of program)
void reset_P(void)
{
	char retStr[5];
	sprintf(retStr, "P= 0");
	//for debug
	printf("%s\n",retStr);
}

// loading a register (ensure P value is correct)
void load_register(short value, bool speedFlag)
{
	char retStr[24];
	if(speedFlag) // need speed
	{
		sprintf(retStr, "LC %x",(short)value);
		available_reg[C] = 0;
	}
	else
	{
		sprintf(retStr, "LA %x",(short)value);
		available_reg[A] = 0;

	}
	//for debug
	printf("%s\n",retStr);
}

// set a register to zero
void register_zero(short field, short reg_name)
{
	char cReg[2];
	char cField[3];
	char retStr[10];
	switch(reg_name)
	{
		case A:
			strcpy(cReg,"A");
		break;
		case B:
			strcpy(cReg,"B");
		break;
		case C:
			strcpy(cReg,"C");
		break;
		case D:
			strcpy(cReg,"D");
		break;
		default:
		break;
	}
	switch(field)
	{
		case W_FIELD:
			strcpy(cField,"W");
		break;
		case A_FIELD:		
			strcpy(cField,"A");
		break;
		case X_FIELD:	
			strcpy(cField,"X");
		break;	
		case XS_FIELD:
			strcpy(cField,"XS");
		break;
		case M_FIELD:
			strcpy(cField,"M");
		break;			
		case S_FIELD:
			strcpy(cField,"S");
		break;	
		case B_FIELD:
			strcpy(cField,"B");
		break;

		default:
		break;
	}
	sprintf(retStr, "%s=0 %s",cReg,cField);

	//for debug
	printf("%s\n",retStr);
}


// ================================================================================================= //
// ================================================================================================= //
// ================================================================================================= //

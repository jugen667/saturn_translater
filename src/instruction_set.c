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
static bool work_available_reg[MAX_WORKING_REGISTER] = {1, 1, 1, 1};
static char * direction_str[MAX_DIRECTION] = {
	"R",
	"L"
};
static char * working_register_str[MAX_WORKING_REGISTER] = {
	"A",
	"B",
	"C",
	"D"
};
static char * save_register_str[MAX_SAVE_REGISTER] = {
	"R0",
	"R1",
	"R2",
	"R3",
	"R4"
};
static char * pointer_register_str[MAX_POINTER_REGISTER] = {
	"D0",
	"D1"
};
static char * field_str[MAX_FIELD] = {
	"W",
	"A",
	"B",
	"X",
	"XS",
	"M",
	"S",
	"WP"
};
// ================================================================================================= //
// =========================================== FUNCTIONS =========================================== //
// ================================================================================================= //

// dumping management in this scope only
void dump_instruction(char * inst, FILE * fDest)
{
	if(fDest != NULL)
	{
		fprintf(fDest, "%s\n", inst);
	}
	else
	{
		printf("%s\n",inst);
	}
}

// check if register available for saving data
short work_reg_available(void)
{
	for (short i = 0; i < MAX_WORKING_REGISTER; i++)
	{
		if(work_available_reg[i])
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
	dump_instruction(retStr, outfileDescriptor);
}

// decrement P value of 1
void decrement_P(void)
{
	char retStr[6];
	sprintf(retStr, "P=P-1");
	dump_instruction(retStr, outfileDescriptor);
}

// set value of P (char atm because less than 256)
void set_PField_value(unsigned char value)
{
	char retStr[10];
	sprintf(retStr, "P= %d",(short)value);
	dump_instruction(retStr, outfileDescriptor);
}

// reset P value (should be called at end of program)
void reset_P(void)
{
	char retStr[5];
	sprintf(retStr, "P= 0");
	dump_instruction(retStr, outfileDescriptor);
}

// ----- Operations on working registers -----

// set a bit to zero (reg A and C only)
void clear_bit(short reg_name, char bit_nbr)
{
	char retStr[12];
	sprintf(retStr, "%sBIT=0 %d",working_register_str[reg_name],(short) bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// set a bit to one (reg A and C only)
void set_bit(short reg_name, char bit_nbr)
{
	char retStr[12];
	sprintf(retStr, "%sBIT=1 %d",working_register_str[reg_name],(short) bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// loading a register (ensure P value is correct)
void load_register(short value, bool speedFlag)
{
	char retStr[12];
	if(speedFlag) // need speed
	{
		sprintf(retStr, "LC %x",(short)value);
		work_available_reg[C] = 0;
	}
	else
	{
		sprintf(retStr, "LA %x",(short)value);
		work_available_reg[A] = 0;

	}
	dump_instruction(retStr, outfileDescriptor);
}

// set a register to zero
void register_zero(short reg_name, short field)
{
	char retStr[10];
	sprintf(retStr, "%s=0 %s",working_register_str[reg_name],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// exchanging register (in alphabetical order)
void ex_register(short reg_1, short reg_2, short field)
{
	char retStr[7];
	sprintf(retStr, "%s%sEX %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// copying register 
// BEWARE !
// Register links : 
// 		A
//      | \
// 	 D--C--B
// 
void copy_register(short src_reg_name, short dest_reg_name, short field)
{
	char retStr[7];
	sprintf(retStr, "%s=%s %s",working_register_str[dest_reg_name],working_register_str[src_reg_name],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// incrementing register
void inc_register(short reg_name, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s+1 %s",working_register_str[reg_name],working_register_str[reg_name],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// decrementing register
void dec_register(short reg_name, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s-1 %s",working_register_str[reg_name],working_register_str[reg_name],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// adding two registers
void add_register(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s+%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// adding a const to registers
void add_const_register(short dest_reg, short field, short constant)
{
	// BUG : if constant > 1 and field = S,XS,WP,P => carry bug 
	if((constant > 1) && 
	  ((field == S_FIELD)||(field == XS_FIELD)||(field == WP_FIELD)))
	{
		// do increment instead
		for(short i = 0; i < constant; i++)
		{
			inc_register(dest_reg, field);
		}
	}
	else
	{
		char retStr[15];
		sprintf(retStr, "%s=%s+%d %s",working_register_str[dest_reg],working_register_str[dest_reg],constant,field_str[field]);
		dump_instruction(retStr, outfileDescriptor);
	}
}

// sub two registers
void sub_register(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s-%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// sub a const to registers
void sub_const_register(short dest_reg, short field, short constant)
{
	// BUG : if constant > 1 and field = S,XS,WP,P => carry bug 
	if((constant > 1) && 
	  ((field == S_FIELD)||(field == XS_FIELD)||(field == WP_FIELD)))
	{
		// do decrement instead
		for(short i = 0; i < constant; i++)
		{
			dec_register(dest_reg, field);
		}
	}
	else
	{
		char retStr[12];
		sprintf(retStr, "%s=%s-%d %s",working_register_str[dest_reg],working_register_str[dest_reg],constant,field_str[field]);
		dump_instruction(retStr, outfileDescriptor);
	}
}

// mul two registers
void mul_register(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s*%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// mod two registers
void mod_register(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s%%%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// div two registers
void div_register(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s/%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// one's complement
void one_complement(short dest_reg, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=-%s-1 %s",working_register_str[dest_reg],working_register_str[dest_reg],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// two's complement
void two_complement(short dest_reg, short field)
{
	char retStr[7];
	sprintf(retStr, "%s=-%s %s",working_register_str[dest_reg],working_register_str[dest_reg],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// logical OR
void logical_OR(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s|%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// logical AND
void logical_AND(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s&%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// logical XOR
void logical_XOR(short dest_reg, short reg_1, short field)
{
	char retStr[9];
	sprintf(retStr, "%s=%s^%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[reg_1],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// shift nibble
void shift_nibble(short dest_reg, short field, short direction)
{
	char retStr[7];
	sprintf(retStr, "%sS%s %s",working_register_str[dest_reg],direction_str[direction],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// rotating nibble
void rotate_nibble(short dest_reg, short direction)
{
	char retStr[5];
	sprintf(retStr, "%sS%sC",working_register_str[dest_reg],direction_str[direction]);
	dump_instruction(retStr, outfileDescriptor);
}

// shifting 64 bits to right
void shift_bit_right(short dest_reg, short field) 
{
	char retStr[8];
	sprintf(retStr, "%sSRB %s",working_register_str[dest_reg],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// shift right with reg value 
void shift_reg_right(short dest_reg, short value_reg, short field) 
{
	char retStr[9];
	sprintf(retStr, "%s=%s>%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[value_reg],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// shift left with reg value
void shift_reg_left(short dest_reg, short value_reg, short field) 
{
	char retStr[9];
	sprintf(retStr, "%s=%s<%s %s",working_register_str[dest_reg],working_register_str[dest_reg],working_register_str[value_reg],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------




// ------- Operations on save registers ------

// saving save register to work register (A or C) 
void copy_reg_save_work(short reg_1, short reg_2, short field) 
{
	char retStr[8];
	sprintf(retStr, "%s=%s %s",save_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// saving working register (A or C) to save register and vice verso
void copy_reg_work_save(short reg_1, short reg_2, short field) 
{
	char retStr[8];
	sprintf(retStr, "%s=%s %s",working_register_str[reg_1],save_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// exchange working register (A or C) and save register
void ex_reg_work_save(short reg_1, short reg_2, short field) 
{
	char retStr[9];
	sprintf(retStr, "%s%sEX %s",working_register_str[reg_1],save_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------



// ----- Operations on pointers registers ----

// load a pointer (adress or nibble is size 2, 4 or 5 only)
void load_pointer(short reg_1, int adress) 
{
	char retStr[9];
	sprintf(retStr, "%s= %.05x",pointer_register_str[reg_1],adress);
	dump_instruction(retStr, outfileDescriptor);
}

// adding in pointer (n from 1 to 16)
void adding_pointer(short reg_1, short n) 
{
	char retStr[12];
	sprintf(retStr, "%s=%s+ %d",pointer_register_str[reg_1],pointer_register_str[reg_1],n);
	dump_instruction(retStr, outfileDescriptor);
}

// sub-ing in pointer (n from 1 to 16)
void subing_pointer(short reg_1, short n) 
{
	char retStr[12];
	sprintf(retStr, "%s=%s- %d",pointer_register_str[reg_1],pointer_register_str[reg_1],n);
	dump_instruction(retStr, outfileDescriptor);
}

// copyng A or C in pointer (copying A field ?), LSBflag only for copying four LSB nibbles of A
void copying_pointer(short reg_1, short reg_2, short LSBFlag) 
{
	char retStr[6];
	if(LSBFlag)
	{
		sprintf(retStr, "%s=%sS",pointer_register_str[reg_1],working_register_str[reg_2]);
		dump_instruction(retStr, outfileDescriptor);
	}
	else
	{
		sprintf(retStr, "%s=%s",pointer_register_str[reg_1],working_register_str[reg_2]);
		dump_instruction(retStr, outfileDescriptor);
	}
}

// exchanging the field A of  A or C in pointer, LSBflag only for copying four LSB nibbles of A
void exchanging_pointer(short reg_1, short reg_2, short LSBFlag) 
{
	char retStr[6];
	if(LSBFlag)
	{
		sprintf(retStr, "%s%sXS",pointer_register_str[reg_1],working_register_str[reg_2]);
		dump_instruction(retStr, outfileDescriptor);
	}
	else
	{
		sprintf(retStr, "%s%sEX",working_register_str[reg_1],pointer_register_str[reg_2]);
		dump_instruction(retStr, outfileDescriptor);
	}
}

// -------------------------------------------



// ----------- Operations on memory ----------

// reading memory ( read the dat pointed by Dx in a register) TO DO with value
void reading_memory(short pointer, short working, short field)
{
	char retStr[12];
	sprintf(retStr, "%s=DAT%d %s",working_register_str[working],pointer, field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// writing memory ( read the dat pointed by Dx in a register) TO DO with value
void writing_memory(short pointer, short working, short field)
{
	char retStr[12];
	sprintf(retStr, "DAT%d=%s %s",pointer,working_register_str[working],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------



// ------------- Jumping and tests -----------

// create label lets say 16 char max
void create_label(char * label)
{
	char retStr[18];
	sprintf(retStr, "*%s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// jump if carry is set (+127 nibbles or -128 niblles afetr present position)
void go_if_carry(char * label)
{
	char retStr[21];
	sprintf(retStr, "GOC %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// jump if carry is not set (+127 nibbles or -128 niblles afetr present position)
void go_if_no_carry(char * label)
{
	char retStr[22];
	sprintf(retStr, "GONC %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// unconditionnal (+2047 nibbles or -2048 niblles afetr present position)
void go_to(char * label)
{
	char retStr[22];
	sprintf(retStr, "GOTO %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// unconditionnal (+32767 nibbles or -32768 niblles afetr present position)
void go_long(char * label)
{
	char retStr[24];
	sprintf(retStr, "GOLONG %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// unconditionnal (any point in memory position)
void go_very_long(char * label)
{
	char retStr[24];
	sprintf(retStr, "GOVLNG %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// unconditionnal jump to adress in A or C, copy A or C in PC
void go_reg_adress(short reg_1)
{
	char retStr[5];
	sprintf(retStr, "PC=%s",working_register_str[reg_1]);
	dump_instruction(retStr, outfileDescriptor);
}

// unconditionnal jump to adress in A and C and exchange PC with A field
void goex_reg_adress(short reg_1)
{
	char retStr[6];
	sprintf(retStr, "%sPCEX",working_register_str[reg_1]);
	dump_instruction(retStr, outfileDescriptor);
}

// indirect jump to adress in A and C (read the adress stored in A field of register and jump at this adress)
void ind_jump(short reg_1)
{
	char retStr[7];
	sprintf(retStr, "PC=(%s)",working_register_str[reg_1]);
	dump_instruction(retStr, outfileDescriptor);
}

// save content of PC in A field of A or C
void save_PC(short reg_1)
{
	char retStr[5];
	sprintf(retStr, "%s=PC",working_register_str[reg_1]);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------



// ---------------- Subroutines --------------

// go to subroutine (+2047 nibbles or -2048 niblles afetr present position)
void go_subroutine(char * label)
{
	char retStr[23];
	sprintf(retStr, "GOSUB %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// go to subroutine long (+32767 nibbles or -32768 niblles afetr present position)
void go_subroutine_long(char * label)
{
	char retStr[24];
	sprintf(retStr, "GOSUBL %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// go to subroutine very long (everywhere in code)
void go_subroutine_very_long(char * label)
{
	char retStr[24];
	sprintf(retStr, "GOSBVL %s",label);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------
// ================================================================================================= //
// ================================================================================================= //
// ================================================================================================= //

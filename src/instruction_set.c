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
// array to point to registers
static node_t work_reg_val[MAX_WORKING_REGISTER] = {NULL, NULL,NULL, NULL};
static node_t work_reg_ident[MAX_WORKING_REGISTER] = {NULL, NULL, NULL, NULL};

static node_t save_reg_val[MAX_SAVE_REGISTER] = {NULL, NULL, NULL, NULL, NULL};
static node_t save_reg_ident[MAX_SAVE_REGISTER] = {NULL, NULL, NULL, NULL, NULL};

static node_t point_reg_val[MAX_POINTER_REGISTER] = {NULL, NULL};
static node_t point_reg_ident[MAX_POINTER_REGISTER] = {NULL, NULL};

// for association with parsing
static node_t current_node;

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
static char * hst_str[MAX_HST] = {
	"SR",
	"SB",
	"MP",
	"XM"
};
// ================================================================================================= //
// =========================================== FUNCTIONS =========================================== //
// ================================================================================================= //


// ------------- Specific functions -----------
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

// check if register available for working with data
short work_reg_available(void)
{
	for (short i = 0; i < MAX_WORKING_REGISTER; i++)
	{
		if(save_reg_ident[i] == NULL)
		{
			return i;
		}
	}
	return -1;
}

// check if register available for saving data
short save_reg_available(void)
{
	for (short i = 0; i < MAX_SAVE_REGISTER; i++)
	{
		if(save_reg_ident[i] == NULL)
		{
			return i;
		}
	}
	return -1;
}

// check if register available for pointers
short point_reg_available(void)
{
	for (short i = 0; i < MAX_POINTER_REGISTER; i++)
	{
		if(save_reg_ident[i] == NULL)
		{
			return i;
		}
	}
	return -1;
}

// getter for  current node
node_t get_current_node(void)
{
	return current_node;
}

// setter for current node
void set_current_node(node_t node)
{
	current_node = node;
}

//add node to register descriptor and add the ident
void add_node_register(short reg_type, node_t node_val, node_t node_ident, short index)
{
	switch(reg_type)
	{
		case T_WORKING: 
			work_reg_val[index] = node_val;
			work_reg_ident[index] = node_ident;
		break;
		case T_SAVE: 
			save_reg_val[index] = node_val;
			save_reg_ident[index] = node_ident;
		break;
		case T_POINTER: 
			point_reg_val[index] = node_val;
			point_reg_ident[index] = node_ident;
		break;
		default : 
		break;
	}
}

//getting the node value stored
node_t get_node_val(short reg_type, short index)
{
	switch(reg_type)
	{
		case T_WORKING: 
			return work_reg_val[index];
		break;
		case T_SAVE: 
			return save_reg_val[index];
		break;
		case T_POINTER: 
			return point_reg_val[index];
		break;
		default : 
		break;
	}
}

//getting the node ident stored
short get_node_ident(short reg_type, char * ident)
{
	short max_index;
	node_t * reg_desc;
	switch(reg_type)
	{
		case T_WORKING: 
			max_index = MAX_WORKING_REGISTER;
			reg_desc = work_reg_ident;
		break;
		case T_SAVE: 
			max_index = MAX_SAVE_REGISTER;
			reg_desc = save_reg_ident;
		break;
		case T_POINTER: 
			max_index = MAX_POINTER_REGISTER;
			reg_desc = point_reg_ident;
		break;
		default : 
		break;
	}
	for(int i = 0; i < max_index; i++)
	{
		if(reg_desc[i] != NULL)
		{
			//printf("%s\n", reg_desc[i]->ident);
			if(!strncmp(reg_desc[i]->ident, ident, VAR_MAX_SIZE))
			{

				return i;
			}
		}
	}
	return -1;
}

// -------------------------------------------



// ------------ Special instructions ----------

// save pointer at start
void save_pointers(void)
{
	char retStr[13];
	sprintf(retStr, "GOSBVL 0679B");
	dump_instruction(retStr, outfileDescriptor);
}

// restore pointers 
void restore_pointers(void)
{
	char retStr[13];
	sprintf(retStr, "GOSBVL 067D2");
	dump_instruction(retStr, outfileDescriptor);
}

// set Saturn to Hex mode
void set_hexmode(void)
{
	char retStr[7];
	sprintf(retStr, "SETHEX");
	dump_instruction(retStr, outfileDescriptor);
}

// set Saturn to dec mode
void set_decmode(void)
{
	char retStr[7];
	sprintf(retStr, "SETDEC");
	dump_instruction(retStr, outfileDescriptor);
}

// filler (not recognised by MASD or HP-ASM)
void filler(short nibble_amount)
{
	char retStr[10];
	sprintf(retStr, "NOP%d", nibble_amount);
	dump_instruction(retStr, outfileDescriptor);
}

// filler using the opcode for 3nibble
void filler_3n(void)
{
	char retStr[5];
	sprintf(retStr, "$420");
	dump_instruction(retStr, outfileDescriptor);
}

// filler using the opcode for 4nibble
void filler_4n(void)
{
	char retStr[6];
	sprintf(retStr, "$6300");
	dump_instruction(retStr, outfileDescriptor);
}

// filler using the opcode for 5nibble
void filler_5n(void)
{
	char retStr[7];
	sprintf(retStr, "$64000");
	dump_instruction(retStr, outfileDescriptor);
}

void create_comment(const char* comment)
{
	char retStr[128];
	sprintf(retStr, "%% %s", comment);
	dump_instruction(retStr, outfileDescriptor);
}

// -------------------------------------------



// ------------------ P Value ----------------

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
void set_PField_value(short value)
{
	char retStr[10];
	sprintf(retStr, "P= %d",value);
	dump_instruction(retStr, outfileDescriptor);
}

// reset P value (should be called at end of program)
void reset_P(void)
{
	char retStr[5];
	sprintf(retStr, "P= 0");
	dump_instruction(retStr, outfileDescriptor);
}

// set value of P to nibble n of register C
void set_PField_C_value(short nibble_nbr)
{
	char retStr[12];
	sprintf(retStr, "C=P %d",nibble_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// set value of nibble n of register C to P
void set_C_value_PField(short nibble_nbr)
{
	char retStr[12];
	sprintf(retStr, "P=C %d",nibble_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// exchnage nibble
void exchange_C_P(short nibble_nbr)
{
	char retStr[12];
	sprintf(retStr, "CPEX %d",nibble_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// value of field A of C + P + 1 to field A of C - always hexa mode (dont ask me)
void strange_instruction(void)
{
	char retStr[6];
	sprintf(retStr, "C+P+1");
	dump_instruction(retStr, outfileDescriptor);
}

// === ALWAYS FOLLOWED BY 'GOYES label' or 'RTNYES' ===
// test equal to n (carry will be set if true)
void check_P_value(short n)
{
	char retStr[12];
	sprintf(retStr, "?P= %d",n);
	dump_instruction(retStr, outfileDescriptor);
}

// test different to n (carry will be set if true)
void check_P_diff_value(short n)
{
	char retStr[12];
	sprintf(retStr, "?P# %d",n);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------



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
void load_register(uint64_t value, bool speedFlag)
{
	char retStr[20];
	if(speedFlag) // need speed
	{
		sprintf(retStr, "LC %lX",(uint64_t)value);
	}
	else
	{
		sprintf(retStr, "LA %lX",(uint64_t)value);
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
	char retStr[10];
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

// jump if test true (always put after test)
void GOYES(char * label)
{
	char retStr[24];
	sprintf(retStr, "GOYES %s",label);
	dump_instruction(retStr, outfileDescriptor);
}

// return if test true (always put after test)
void RTNYES(char * label)
{
	char retStr[24];
	sprintf(retStr, "RTNYES %s",label);
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

// return from subroutine
void sub_return(void)
{
	char retStr[4];
	sprintf(retStr, "RTN");
	dump_instruction(retStr, outfileDescriptor);
}

// return from subroutine set carry
void sub_return_set_carry(void)
{
	char retStr[6];
	sprintf(retStr, "RTNSC");
	dump_instruction(retStr, outfileDescriptor);
}

// return from subroutine clear carry
void sub_return_clear_carry(void)
{
	char retStr[6];
	sprintf(retStr, "RTNCC");
	dump_instruction(retStr, outfileDescriptor);
}

// return from subroutine allow interrupt
void sub_return_allow_int(void)
{
	char retStr[4];
	sprintf(retStr, "RTI");
	dump_instruction(retStr, outfileDescriptor);
}

// return from subroutine set XM (eXternal Module)
void sub_return_set_XM(void)
{
	char retStr[7];
	sprintf(retStr, "RTNSXM");
	dump_instruction(retStr, outfileDescriptor);
}

// return from subroutine if carry 
void sub_return_if_carry(void)
{
	char retStr[5];
	sprintf(retStr, "RTNC");
	dump_instruction(retStr, outfileDescriptor);
}

// return from subroutine if carry not set
void sub_return_if_no_carry(void)
{
	char retStr[6];
	sprintf(retStr, "RTNNC");
	dump_instruction(retStr, outfileDescriptor);
}


// -------------------------------------------



// ------------------- Tests -----------------

// === ALWAYS FOLLOWED BY 'GOYES label' or 'RTNYES' ===
// equal to zero
void equal_to_zero(short reg_name, short field)
{
	char retStr[8];
	sprintf(retStr, "?%s=0 %s",working_register_str[reg_name],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// different from zero
void different_from_zero(short reg_name, short field)
{
	char retStr[8];
	sprintf(retStr, "?%s#0 %s",working_register_str[reg_name],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// register equality
void register_equal(short reg_1,short reg_2, short field)
{
	char retStr[8];
	sprintf(retStr, "?%s=%s %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// register inequality
void register_not_equal(short reg_1,short reg_2, short field)
{
	char retStr[8];
	sprintf(retStr, "?%s#%s %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// register less than
void register_LT(short reg_1,short reg_2, short field)
{
	char retStr[8];
	sprintf(retStr, "?%s<%s %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// register greater than
void register_GT(short reg_1,short reg_2, short field)
{
	char retStr[8];
	sprintf(retStr, "?%s>%s %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// register less than or equal
void register_LTE(short reg_1,short reg_2, short field)
{
	char retStr[9];
	sprintf(retStr, "?%s<=%s %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// register greater than or equal
void register_GTE(short reg_1,short reg_2, short field)
{
	char retStr[9];
	sprintf(retStr, "?%s>=%s %s",working_register_str[reg_1],working_register_str[reg_2],field_str[field]);
	dump_instruction(retStr, outfileDescriptor);
}

// testing a bit = 0 in a register
void testing_bit_0(short reg_name, short bit_nbr)
{
	char retStr[14];
	sprintf(retStr, "?%sBIT=0 %d",working_register_str[reg_name],bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// testing a bit = 1 in a register
void testing_bit_1(short reg_name, short bit_nbr)
{
	char retStr[14];
	sprintf(retStr, "?%sBIT=1 %d",working_register_str[reg_name],bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// -------------------------------------------



// ------------------- Misc ------------------

// field A of C = RSTK
void C_to_RSTK(void)
{
	char retStr[7];
	sprintf(retStr, "C=RSTK");
	dump_instruction(retStr, outfileDescriptor);
}

// RSTK = field A of C
void RSTK_to_C(void)
{
	char retStr[7];
	sprintf(retStr, "RSTK=C");
	dump_instruction(retStr, outfileDescriptor);
}

// save nibble 0 of C in OUT 
void save_n0_OUT(void)
{
	char retStr[7];
	sprintf(retStr, "OUT=CS");
	dump_instruction(retStr, outfileDescriptor);
}

// save field X of C in OUT 
void save_X_OUT(void)
{
	char retStr[6];
	sprintf(retStr, "OUT=C");
	dump_instruction(retStr, outfileDescriptor);
}

// IN in four nibble of field A of A
void save_IN_A(void)
{
	// === BUG USING 'A=IN' ===
	// === USE A SUBROUTINE ===
	char retStr[13];
	if (target == 48)
	{
		sprintf(retStr, "GOSBVL 0115A"); // =AINRTN in 48
	}
	else if (target == 49)
	{
		sprintf(retStr, "GOSBVL 0020A"); // =AINRTN in 49
	}
	dump_instruction(retStr, outfileDescriptor);
}

// IN in four nibble of field A of C
void save_IN_C(void)
{
	// === BUG USING 'C=IN' ===
	// === USE A SUBROUTINE ===
	char retStr[13];
	if (target == 48)
	{
		sprintf(retStr, "GOSBVL 01160"); // =CINRTN in 48
	}
	else if (target == 49)
	{
		sprintf(retStr, "GOSBVL 00212"); // =CINRTN in 49
	}
	dump_instruction(retStr, outfileDescriptor);
}

//clear STatus Register (first 3 nibbles of ST, last nibble contains special values for processor)
void clear_ST(void)
{
	char retStr[6];
	sprintf(retStr, "CLRST");
	dump_instruction(retStr, outfileDescriptor);
}

//store ST in X field of C
void store_ST_C(void)
{
	char retStr[5];
	sprintf(retStr, "C=ST");
	dump_instruction(retStr, outfileDescriptor);
}

//store X field of C in ST
void store_C_ST(void)
{
	char retStr[5];
	sprintf(retStr, "ST=C");
	dump_instruction(retStr, outfileDescriptor);
}

//exchange X field of C and ST
void exchange_ST_C(void)
{
	char retStr[6];
	sprintf(retStr, "CSTEX");
	dump_instruction(retStr, outfileDescriptor);
}

//set bit n to 1 in ST reg 
void set_bit_ST(short bit_nbr)
{
	char retStr[12];
	sprintf(retStr, "ST=1 %d", bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

//clear bit n to 1 in ST reg 
void clear_bit_ST(short bit_nbr)
{
	char retStr[12];
	sprintf(retStr, "ST=0 %d", bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// === ALWAYS FOLLOWED BY 'GOYES label' or 'RTNYES' ===
//check if bit n to 0 in ST reg 
void check_ST_bit_zero(short bit_nbr)
{
	char retStr[13];
	sprintf(retStr, "?ST=0 %d", bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

//check if bit n to 1 in ST reg 
void check_ST_bit_one(short bit_nbr)
{
	char retStr[13];
	sprintf(retStr, "?ST=1 %d", bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// set HST bit to 0
void clear_HST_bit(short bit_nbr)
{
	char retStr[13];
	sprintf(retStr, "HST=0 %d", bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// set a HST field to 0
void clear_HST_field(short hst_field)
{
	char retStr[5];
	sprintf(retStr, "%s=0", hst_str[hst_field]);
	dump_instruction(retStr, outfileDescriptor);
}

// set all HST to 0
void clear_HST(void)
{
	char retStr[7];
	sprintf(retStr, "CLRHST");
	dump_instruction(retStr, outfileDescriptor);
}

// === ALWAYS FOLLOWED BY 'GOYES label' or 'RTNYES' ===
// check HST bit  0
void check_HST_bit(short bit_nbr)
{
	char retStr[14];
	sprintf(retStr, "?HST=0 %d", bit_nbr);
	dump_instruction(retStr, outfileDescriptor);
}

// check HST field  0
void check_HST_field(short hst_field)
{
	char retStr[6];
	sprintf(retStr, "?%s=0", hst_str[hst_field]);
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------


// --------- Interruptions management --------

// disable keyboards interrupt
void disable_kb_interrupt(void)
{
	char retStr[7];
	sprintf(retStr, "INTOFF");
	dump_instruction(retStr, outfileDescriptor);
}

// enable keyboards interrupt
void enable_kb_interrupt(void)
{
	char retStr[6];
	sprintf(retStr, "INTON");
	dump_instruction(retStr, outfileDescriptor);
}

// reset interrupt
void reset_interrupt(void)
{
	char retStr[4];
	sprintf(retStr, "RSI");
	dump_instruction(retStr, outfileDescriptor);
}

// disable all interrupt
void disable_all_interrupt(void)
{
	char retStr[13];
	if (target == 48)
	{
		sprintf(retStr, "GOSBVL 01115"); // =DisableIntr on 48
	}
	else if (target == 49)
	{
		sprintf(retStr, "GOSBVL 26791"); // =DisableIntr on 49
	}
	dump_instruction(retStr, outfileDescriptor);
}

// enable all interrupt
void enable_all_interrupt(void)
{
	char retStr[13];
	if (target == 48)
	{
		sprintf(retStr, "GOSBVL 010E5"); // =AllowIntr on 48
	}
	else if (target == 49)
	{
		sprintf(retStr, "GOSBVL 26767"); // =AllowIntr on 49
	}
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------


// --------- Bus-related instructions --------
// maybe not necessary

// bus reset : all modules go to unconfigured state
void bus_reset(void)
{
	char retStr[6];
	sprintf(retStr, "RESET");
	dump_instruction(retStr, outfileDescriptor);
}

// configure a memory module
void bus_config(void)
{
	char retStr[7];
	sprintf(retStr, "CONFIG");
	dump_instruction(retStr, outfileDescriptor);
}

// un-configure a memory module
void bus_unconfig(void)
{
	char retStr[7];
	sprintf(retStr, "UNCNFG");
	dump_instruction(retStr, outfileDescriptor);
}

// copy module ID in A field of C
void bus_ID(void)
{
	char retStr[5];
	sprintf(retStr, "C=ID");
	dump_instruction(retStr, outfileDescriptor);
}

// low power usage mode
void bus_shutdown(void)
{
	char retStr[7];
	sprintf(retStr, "SHUTDN");
	dump_instruction(retStr, outfileDescriptor);
}
// -------------------------------------------


// ------------ Unused instructions ----------
// Unused on 48 and 49 
// BUSCx => only for Saturn + => not implemented
// SREQ? => old legacy instruction
// All ARM Instructions
// Custom fields F1-F7
// -------------------------------------------
// ================================================================================================= //
// ================================================================================================= //
// ================================================================================================= //

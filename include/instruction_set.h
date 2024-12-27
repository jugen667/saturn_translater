// ========================================
// > Author :   jugen 667 
// > Title  :   instruction_set.h 
// > Desc.  :   Header for assembly 
//				generation
// ========================================


// ======================= REGISTER STRUCTURES IN HP48 ======================== //
//																				//
// 		| F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |		//
//		|																|		//
//		 <------------------------------W------------------------------>		//
//												 <----------A---------->		//
//															 <----X---->		//
//															 <XS>				//
//															  <----B--->		//
//		     <-----------------------M--------------------->					//
//		 <S>																	//
//																				//
// ============================================================================ //


// ================================================================================================= //
// ======================================== ENUM & STRUCTS ========================================= //
// ================================================================================================= //
enum WORKING_REGISTER
{
	A,
	B,
	C,
	D,
	MAX_WORKING_REGISTER,
};

enum SAVE_REGISTER
{
	R0,
	R1,
	R2,
	R3,
	R4,
	MAX_SAVE_REGISTER,
};

enum POINTER_REGISTER
{
	D0,
	D1,
	MAX_POINTER_REGISTER
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	MAX_DIRECTION,
};

enum REGISTER_FIELDS
{
	W_FIELD,		// WORD (64 bits = 16 nibbles)
	A_FIELD,		// ADRESS (5 lowest nibbes)
	B_FIELD,		// BYTE (1 BYTE nibble 1 & nibble 0)
	X_FIELD,		// X go along OUT coponent of the CPU (3 nibbles)
	XS_FIELD,		// XS MSB of X_FIELD (1 nibble) [XS = eXponent Sign]
	M_FIELD,		// MANTISSA, nibble 3 to 14
	S_FIELD,		// SIGN, last nibble of the register; nibble 15
	WP_FIELD,  		// user defined, start at the value of P
	MAX_FIELD,
};

// ================================================================================================= //
// =========================================== GLOBALS ============================================= //
// ================================================================================================= //

// ================================================================================================= //
// =========================================== PROTOTYPES ========================================== //
// ================================================================================================= //
short work_reg_available(void);
void increment_P(void);
void decrement_P(void);
void set_PField_value(unsigned char value);
void reset_P(void);
void clear_bit(short reg_name, char bit_nbr);
void set_bit(short reg_name, char bit_nbr);

void load_register(short value, bool speedflag);
void register_zero(short reg_name, short field);
void ex_register(short reg_1, short reg_2, short field);
void copy_register(short src_reg_name, short dest_reg_name, short field);
void inc_register(short reg_name, short field);
void dec_register(short reg_name, short field);
void add_register(short dest_reg, short reg_1, short field);
void add_const_register(short dest_reg, short field, short constant);
void sub_register(short dest_reg, short reg_1, short field);
void sub_const_register(short dest_reg, short field, short constant);
void mul_register(short dest_reg, short reg_1, short field);
void div_register(short dest_reg, short reg_1, short field);
void one_complement(short dest_reg, short field);
void two_complement(short dest_reg, short field);
void logical_OR(short dest_reg, short reg_1, short field);
void logical_AND(short dest_reg, short reg_1, short field);
void logical_XOR(short dest_reg, short reg_1, short field);
void shift_nibble(short dest_reg, short field, short direction);
void rotate_nibble(short dest_reg, short direction);
void shift_bit_right(short dest_reg, short field);
void shift_reg_right(short dest_reg, short value_reg, short field);
void shift_reg_left(short dest_reg, short value_reg, short field);

void copy_reg_save_work(short reg_1, short reg_2, short field);
void copy_reg_work_save(short reg_1, short reg_2, short field);
void ex_reg_work_save(short reg_1, short reg_2, short field);

void load_pointer(short reg_1, int adress);
void adding_pointer(short reg_1, short n);
void subing_pointer(short reg_1, short n);
void copying_pointer(short reg_1, short reg_2, short LSBFlag);
void exchanging_pointer(short reg_1, short reg_2, short LSBFlag);

void reading_memory(short pointer, short working, short field);
void writing_memory(short pointer, short working, short field);

void create_label(char * label);
void go_if_carry(char * label);
void go_if_no_carry(char * label);
void go_to(char * label);
void go_long(char * label);
void go_very_long(char * label);
void go_reg_adress(short reg_1);
void goex_reg_adress(short reg_1);
void ind_jump(short reg_1);
void save_PC(short reg_1);

void go_subroutine(char * label);
void go_subroutine_long(char * label);
void go_subroutine_very_long(char * label);

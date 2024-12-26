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
enum REGISTER
{
	A,
	B,
	C,
	D,
	MAX_REGISTER,
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
short reg_available(void);
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
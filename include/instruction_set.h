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
//															     <--B-->		//
//		     <-----------------------M--------------------->					//
//		 <S>																	//
//																				//
// ============================================================================ //


// ================================================================================================= //
// ======================================== ENUM & STRUCTS ========================================= //
// ================================================================================================= //
enum REGISTER_TYPE 	// each of 64 bits (16 nibbles)
{
	T_WORKING,
	T_SAVE,
	T_POINTER,
	MAX_REGISTER_TYPE,
};
enum WORKING_REGISTER 	// each of 64 bits (16 nibbles)
{
	A,
	B,
	C,
	D,
	MAX_WORKING_REGISTER,
};

enum SAVE_REGISTER  	// each of 64 bits (16 nibbles)
{
	R0,
	R1,
	R2,
	R3,
	R4,
	MAX_SAVE_REGISTER,
};

enum HARDWARE_STATUS  
{
	SR,					// Service Request
	SB,					// Sticky Bit
	MP,					// Module Pulled
	XM,					// eXternal Module missing
	MAX_HST,
};

enum POINTER_REGISTER  	// 5 nibbles each (an adress is 5 nibbles)
{
	D0,
	D1,
	MAX_POINTER_REGISTER
};

enum REGISTER_FIELDS
{
	W_FIELD,			// WORD (64 bits = 16 nibbles)
	A_FIELD,			// ADRESS (5 lowest nibbes)
	B_FIELD,			// BYTE (1 BYTE nibble 1 & nibble 0)
	X_FIELD,			// X go along OUT coponent of the CPU (3 nibbles)
	XS_FIELD,			// XS MSB of X_FIELD (1 nibble) [XS = eXponent Sign]
	M_FIELD,			// MANTISSA, nibble 3 to 14
	S_FIELD,			// SIGN, last nibble of the register; nibble 15
	WP_FIELD,  			// user defined, start at the value of P
	P_FIELD,			// definition for WP field (can be used as a field can store one nibble but is a register)
	MAX_FIELD,
};

enum DIRECTION 			// for bit/nibble shift
{
	RIGHT,
	LEFT,
	MAX_DIRECTION,
};

// ================================================================================================= //
// =========================================== GLOBALS ============================================= //
// ================================================================================================= //

// ================================================================================================= //
// =========================================== PROTOTYPES ========================================== //
// ================================================================================================= //
short work_reg_available(void);
short save_reg_available(void);
short point_reg_available(void);
void add_node_register(short reg_type, node_t node_val, node_t node_ident, short index);
node_t get_node_val(short reg_type, short index);
short get_node_ident(short reg_type, char * ident);

// ==== Useless - to delete but idc atm ==== 
node_t get_current_node(void);
void set_current_node(node_t node);
// =========================================  

void increment_P(void);
void decrement_P(void);
void set_PField_value(short value);
void reset_P(void);
void set_PField_C_value(short nibble_nbr);
void set_C_value_PField(short nibble_nbr);
void exchange_C_P(short nibble_nbr);
void strange_instruction(void);
void check_P_value(short n);
void check_P_diff_value(short n);

void save_pointers(void);
void restore_pointers(void);
void set_hexmode(void);
void set_hexmode(void);
void filler(short nibble_amount); 	// not recognised by MASD and HP ASM
void filler_3n(void);				// using raw opcode
void filler_4n(void);				// using raw opcode
void filler_5n(void);				// using raw opcode
void create_comment(const char* comment);

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
void GOYES(char * label);
void RTNYES(char * label);
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
void sub_return(void);
void sub_return_set_carry(void);
void sub_return_clear_carry(void);
void sub_return_allow_int(void);
void sub_return_set_XM(void);
void sub_return_if_carry(void);
void sub_return_if_no_carry(void);

void equal_to_zero(short reg_name, short field);
void different_from_zero(short reg_name, short field);
void register_equal(short reg_1,short reg_2, short field);
void register_not_equal(short reg_1,short reg_2, short field);
void register_LT(short reg_1,short reg_2, short field);
void register_GT(short reg_1,short reg_2, short field);
void register_LTE(short reg_1,short reg_2, short field);
void register_GTE(short reg_1,short reg_2, short field);
void testing_bit_0(short reg_name, short bit_nbr);
void testing_bit_1(short reg_name, short bit_nbr);

void C_to_RSTK(void);
void RSTK_to_C(void);
void save_n0_OUT(void);
void save_X_OUT(void);
void save_IN_A(void);
void save_IN_C(void);
void clear_ST(void);
void store_ST_C(void);
void store_C_ST(void);
void exchange_ST_C(void);
void set_bit_ST(short bit_nbr);
void clear_bit_ST(short bit_nbr);
void check_ST_bit_zero(short bit_nbr);
void check_ST_bit_one(short bit_nbr);
void clear_HST_bit(short bit_nbr);
void clear_HST_field(short hst_field);
void clear_HST(void);
void check_HST_bit(short bit_nbr);
void check_HST_field(short hst_field);

void disable_kb_interrupt(void);
void enable_kb_interrupt(void);
void reset_interrupt(void);
void disable_all_interrupt(void);
void enable_all_interrupt(void);

void bus_reset(void);
void bus_config(void);
void bus_unconfig(void);
void bus_ID(void);
void bus_shutdown(void);
// ================================================================================================= //
// ================================================================================================= //
// ================================================================================================= //

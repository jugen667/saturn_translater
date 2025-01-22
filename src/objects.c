// ========================================
// > Author :   jugen 667 
// > Title  :   objects.c 
// > Desc.  :   Objects creation for the assembly
// ========================================

//==============
// - INCLUDES -
//==============
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/defs.h"
#include "../include/common.h"
#include "../include/objects.h"

//===============
// - FUNCTIONS -
//===============
typedef union{
    struct {
        uint64_t fullNumber;
    };
    struct {
        uint64_t sign:4;        // 1 nibbles = 4 bits
        uint64_t mantissa:48;   // 12 nibbles = 48 bits
        uint64_t exponent:12;   // 3 nibbles = 12 bits
    };
} realNumber;


uint64_t create_real_number(int32_t value)
{
    int32_t tempValue = value;
    printf("entrey value  : %d\n", value);
    unsigned short exponent;
    realNumber returnValue;
    returnValue.fullNumber = 0;
    //sign
    if(tempValue < 0)
    {
        returnValue.sign = 0x9;
        tempValue *= -1;
    }
    // exponent
    while(tempValue/10)
    {
        exponent++;
        tempValue/=10;
    }
    returnValue.exponent = decimal2BCD(exponent);
    //mantissa
    returnValue.mantissa = decimal2BCD(value);
    return returnValue.fullNumber;
}
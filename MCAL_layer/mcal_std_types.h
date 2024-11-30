/* 
 * File:   mcal_std_types.h
 * Author: KimoStore
 *
 * Created on September 7, 2024, 9:45 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

// section : includes
#include "std_libraries.h"
#include "compiler.h"


// macros declarations

#define STD_HIGH  0x01
#define STD_LOW   0x00


#define STD_ON   0x01
#define STD_OFF  0x00


#define STD_ACTIVE  0x01
#define STD_IDEAL   0x00


 #define E_OK        (Std_ReturnType)0x01
#define E_NOT_OK    (Std_ReturnType)0x00



// macros functions declarations


// data type declarations
typedef unsigned char unit8;
typedef unsigned short unit16;
typedef unsigned int unit32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

typedef unit8 Std_ReturnType;


// function declarations



#endif	/* MCAL_STD_TYPES_H */


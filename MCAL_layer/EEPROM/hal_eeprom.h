/* 
 * File:   hal_eeprom.h
 * Author: Yassin_Khadrawy
 *
 * Created on October 15, 2024, 10:21 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

// section : includes

#include "../../MCAL_layer/mcal_std_types.h"
#include <pic18f4620.h>
#include "../../MCAL_layer/interrupts/mcal_internal_interrupt.h"

// macros declarations


// macros functions declarations


// data type declarations


// function declarations
Std_ReturnType Data_EEPROM_WriteByte(unit16 bAdd , unit8 bData);
Std_ReturnType Data_EEPROM_ReadByte(unit16 bAdd , unit8 *bData);
#endif	/* HAL_EEPROM_H */


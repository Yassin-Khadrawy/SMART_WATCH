/* 
 * File:   mcal_layer_init.h
 * Author: KimoStore
 *
 * Created on November 28, 2024, 11:07 AM
 */

#ifndef MCAL_LAYER_INIT_H
#define	MCAL_LAYER_INIT_H

// section : includes

#include "ADC/hal_adc.h"
#include "EEPROM/hal_eeprom.h"
#include "Timer1/hal_timer1.h"
#include "Timer_0/hal_timer0.h"
#include "Timer_2/hal_timer2.h"
#include "Timer_3/hal_timer3.h"
#include "USART/hal_usart.h"
#include "GPIO/hal_gpio.h"
#include "mcal_std_types.h"
// macros declarations


// macros functions declarations


// data type declarations


// function declarations
void Timer0_DefaultInterruptHandler_1000ms(void);
void ADC_DefaultInterruptHandler(void);
void EUSART_TxDefaultInterruptHandler(void);
void EUSART_RxDefaultInterruptHandler(void);
void EUSART_FramingDefaultInterruptHandler(void);
void EUSART_OverrunDefaultInterruptHandler(void);
#endif	/* MCAL_LAYER_INIT_H */


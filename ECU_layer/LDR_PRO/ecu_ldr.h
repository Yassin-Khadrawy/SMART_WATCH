/* 
 * File:   ecu_ldr.h
 * Author: KimoStore
 *
 * Created on November 3, 2024, 7:58 PM
 */

#ifndef ECU_LDR_H
#define	ECU_LDR_H

// section : includes

#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include <pic18f4620.h>
#include "../../MCAL_layer/mcal_std_types.h"

// macros declarations
#define ADC_CHANNEL_AN2_PWM               2

// macros functions declarations
#define PWM_SET_PIN_CCP1_OUTPUT()            (TRISC2 = 0);
#define PWM_CCP1_TO_PWM_MODE(_CONFIG)        (CCP1CON = _CONFIG);
#define PWM_SET_PWM_PERIOD_FREQ(_CONFIG)     (PR2 = _CONFIG);
#define TIMER2_PRESCALER_ON(_CONFIG)     (T2CON = _CONFIG);
#define PWM_SET_MSBs(_CONFIG)     (CCPR1L = _CONFIG);
#define PWM_SET_LSBs(_CONFIG)      (CCP1CONbits.DC1B = _CONFIG);

// data type declarations


// function declarations
void ADC_Init_chat();
void PWM_Init();
void PWM_SetDuty(unsigned int duty);
unsigned int ADC_Read(unsigned char channel , unit8 Analog_channel);
#endif	/* ECU_LDR_H */


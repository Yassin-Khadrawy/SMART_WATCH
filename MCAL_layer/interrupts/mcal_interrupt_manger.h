/* 
 * File:   mcal_interrupt_manger.h
 * Author: KimoStore
 *
 * Created on October 10, 2024, 9:40 PM
 */

#ifndef MCAL_INTERRUPT_MANGER_H
#define	MCAL_INTERRUPT_MANGER_H

// section : includes

#include "mcal_interruot_config.h"

// macros declarations


// macros functions declarations


// data type declarations


// function declarations
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(unit8 RBx_source);
void RB5_ISR(unit8 RBx_source);
void RB6_ISR(unit8 RBx_source);
void RB7_ISR(unit8 RBx_source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
#endif	/* MCAL_INTERRUPT_MANGER_H */


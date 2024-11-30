/* 
 * File:   mcal_internal_interrupt.h
 * Author: KimoStore
 *
 * Created on October 10, 2024, 9:40 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

// section : includes

#include "mcal_interruot_config.h"
// macros declarations


// macros functions declarations
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the ADC module*/
#define ADC_InterruptEnable()             (PIE1bits.ADIE = 1)
/* this routine sets the interrupt enable for the ADC module*/
#define ADC_InterruptDisable()            (PIE1bits.ADIE = 0)
/* this routine clear the interrupt flag for the ADC module*/
#define ADC_InterruptFlagClear()          (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the ADC module to HIGH priority*/
#define ADC_HighPrioritySet()             (IPR1bits.ADIP = 1)
/* this routine sets the edge detect of the ADC module to LOW priority*/
#define ADC_LowPrioritySet()              (IPR1bits.ADIP = 0)
#endif
#endif


#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the TIMER0 module*/
#define TIMER0_InterruptEnable()             (INTCONbits.TMR0IE = 1)
/* this routine sets the interrupt enable for the TIMER0 module*/
#define TIMER0_InterruptDisable()            (INTCONbits.TMR0IE = 0)
/* this routine clear the interrupt flag for the TIMER0 module*/
#define TIMER0_InterruptFlagClear()          (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the TIMER0 module to HIGH priority*/
#define TIMER0_HighPrioritySet()             (INTCON2bits.TMR0IP = 1)
/* this routine sets the edge detect of the TIMER0 module to LOW priority*/
#define TIMER0_LowPrioritySet()              (INTCON2bits.TMR0IP = 0)

#endif
#endif


#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the TIMER1 module*/
#define TIMER1_InterruptEnable()             (PIE1bits.TMR1IE = 1)
/* this routine sets the interrupt enable for the TIMER1 module*/
#define TIMER1_InterruptDisable()            (PIE1bits.TMR1IE = 0)
/* this routine clear the interrupt flag for the TIMER1 module*/
#define TIMER1_InterruptFlagClear()          (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the TIMER1 module to HIGH priority*/
#define TIMER1_HighPrioritySet()             (IPR1bits.TMR1IP = 1)
/* this routine sets the edge detect of the TIMER1 module to LOW priority*/
#define TIMER1_LowPrioritySet()              (IPR1bits.TMR1IP = 0)

#endif
#endif



#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the TIMER2 module*/
#define TIMER2_InterruptEnable()             (PIE1bits.TMR2IE = 1)
/* this routine sets the interrupt enable for the TIMER2 module*/
#define TIMER2_InterruptDisable()            (PIE1bits.TMR2IE = 0)
/* this routine clear the interrupt flag for the TIMER2 module*/
#define TIMER2_InterruptFlagClear()          (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the TIMER2 module to HIGH priority*/
#define TIMER2_HighPrioritySet()             (IPR1bits.TMR2IP = 1)
/* this routine sets the edge detect of the TIMER2 module to LOW priority*/
#define TIMER2_LowPrioritySet()              (IPR1bits.TMR2IP = 0)

#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the TIMER3 module*/
#define TIMER3_InterruptEnable()             (PIE2bits.TMR3IE = 1)
/* this routine sets the interrupt enable for the TIMER3 module*/
#define TIMER3_InterruptDisable()            (PIE2bits.TMR3IE = 0)
/* this routine clear the interrupt flag for the TIMER3 module*/
#define TIMER3_InterruptFlagClear()          (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the TIMER3 module to HIGH priority*/
#define TIMER3_HighPrioritySet()             (IPR2bits.TMR3IP = 1)
/* this routine sets the edge detect of the TIMER3 module to LOW priority*/
#define TIMER3_LowPrioritySet()              (IPR2bits.TMR3IP = 0)

#endif
#endif



#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the ADC module*/
#define EUSART_TX_InterruptEnable()             (PIE1bits.TXIE = 1)
/* this routine sets the interrupt enable for the ADC module*/
#define EUSART_TX_InterruptDisable()            (PIE1bits.TXIE = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the ADC module to HIGH priority*/
#define EUSART_TX_HighPrioritySet()             (IPR1bits.TXIP = 1)
/* this routine sets the edge detect of the ADC module to LOW priority*/
#define EUSART_TX_LowPrioritySet()              (IPR1bits.TXIP = 0)
#endif
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine clears the interrupt enable for the ADC module*/
#define EUSART_RX_InterruptEnable()             (PIE1bits.RCIE = 1)
/* this routine sets the interrupt enable for the ADC module*/
#define EUSART_RX_InterruptDisable()            (PIE1bits.RCIE = 0)
  
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the ADC module to HIGH priority*/
#define EUSART_RX_HighPrioritySet()             (IPR1bits.RCIP = 1)
/* this routine sets the edge detect of the ADC module to LOW priority*/
#define EUSART_RX_LowPrioritySet()              (IPR1bits.ADIP = 0)
#endif
#endif

// data type declarations

typedef void(*InterruptHandler)(void);
// function declarations

#endif	/* MCAL_INTERNAL_INTERRUPT_H */


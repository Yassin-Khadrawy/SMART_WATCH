/* 
 * File:   hal_timer1.h
 * Author: KimoStore
 *
 * Created on October 26, 2024, 8:03 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

// section : includes

#include "../interrupts/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include <pic18f4620.h>
#include "../../MCAL_layer/mcal_std_types.h"

// macros declarations

#define TIMER1_COUNTER_MODE                 1
#define TIMER1_TIMER_MODE                   0

#define TIMER1_SYNCHRONIZE                  0
#define TIMER1_NON_SYNCHRONIZE              1

#define TIMER1_OSC_ENABLE                   1
#define TIMER1_OSC_DISABLE                  0

#define TIMER1_CLOCK_OSC                    1
#define TIMER1_CLOCK_ANOTHER                0

#define TIMER1_RW_16                        1
#define TIMER1_RW_8                         0

// macros functions declarations
#define TIMER1_COUNTER_MODE_ENABLE()              (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE_ENABLE()                (T1CONbits.TMR1CS = 0)

#define TIMER1_SYNCHRONIZE_EXTERNAL()             (T1CONbits.T1SYNC = 0)
#define TIMER1_NON_SYNCHRONIZE_EXTERNAL()         (T1CONbits.T1SYNC = 1)

#define TIMER1_OSCILLATOR_ENABLE()                (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_DISABLE()               (T1CONbits.T1OSCEN = 0)

#define TIMER1_MODULE_ENABLE()                    (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                   (T1CONbits.TMR1ON = 0)

#define TIMER1_CLOCK_status()                     (T1CONbits.T1RUN)

#define TIMER1_RW_IN_ONE_16_BIT()                 (T1CONbits.RD16 = 1)
#define TIMER1_RW_IN_TWO_8_BIT()                  (T1CONbits.RD16 = 0)

#define TIMER1_PRESCALAR_SELECT(_PRESCALAR_)      (T1CONbits.T1CKPS = _PRESCALAR_)
// data type declarations
typedef enum
{
    TIMER1_PRESCALER_DIV_BY_1 = 0,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8,
    
}timer1_prescaler_select_t;

typedef struct
{
    unit8 clock_status : 1;
    unit8 timer1_oscillator_mode : 1;
    unit8 timer1_No_bits_RW : 1;
    unit8 timer1_timer_counter : 1;
    unit8 timer1_syncro_non_syncro : 1;
    unit16 timer1_preload_value ;
    timer1_prescaler_select_t prescalaer_value;
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*timer1_interrupt_handler)(void);
    interrupt_priority_cfg priority;
#endif 
}timer1_t;
// function declarations

Std_ReturnType Timer1_Init(const timer1_t *timer);
Std_ReturnType Timer1_DeInit(const timer1_t *timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *timer , unit16 value);
Std_ReturnType Timer1_Read_Value(const timer1_t *timer , unit16 *value);


#endif	/* HAL_TIMER1_H */


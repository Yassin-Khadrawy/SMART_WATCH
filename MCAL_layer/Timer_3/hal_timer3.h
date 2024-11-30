/* 
 * File:   hal_timer3.h
 * Author: KimoStore
 *
 * Created on October 29, 2024, 4:58 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

// section : includes
#include "../interrupts/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include <pic18f4620.h>

// macros declarations

#define TIMER3_COUNTER_MODE_ENABLE                     1
#define TIMER3_TIMER_MODE_ENABLE                       0

#define TIMER3_SYNCHRONIZE                             0
#define TIMER3_NON_SYNCHRONIZE                         1

#define TIMER3_RW_16                                   1
#define TIMER3_RW_8                                    0
 

// macros functions declarations

#define TIMER3_MODULE_ENABLE()                (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE()                    (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE()                  (T3CONbits.TMR3CS = 1)

#define TIMER3_SYNCHRONIZE_EXTERNAL()             (T3CONbits.nT3SYNC = 0)
#define TIMER3_NON_SYNCHRONIZE_EXTERNAL()         (T3CONbits.nT3SYNC = 1)

#define TIMER3_PRESCALAR_SELECT(_PRESCALAR_)        (T3CONbits.T3CKPS = _PRESCALAR_)

#define TIMER3_RW_IN_ONE_16_BIT()                 (T3CONbits.RD16 = 1)
#define TIMER3_RW_IN_TWO_8_BIT()                  (T3CONbits.RD16 = 0)


// data type declarations
typedef enum
{
    TIMER3_PRESCALER_DIV_BY_1 = 0,
    TIMER3_PRESCALER_DIV_BY_2,
    TIMER3_PRESCALER_DIV_BY_4,
    TIMER3_PRESCALER_DIV_BY_8,      
}timer3_prescaler_select_t;
typedef struct
{
#if  TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(*timer3_inturrpt_handler)(void);
    interrupt_priority_cfg priority;
#endif
    timer3_prescaler_select_t prescaler_enum;
    unit8 timer3_mode : 1;
    unit8 timer3_synco_non_synco : 1;
    unit8 timer3_number_of_bits : 1;
    unit16 timer3_preload_value;
}timer3_t;

// function declarations
Std_ReturnType Timer3_Init(const timer3_t *timer);
Std_ReturnType Timer3_DeInit(const timer3_t *timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *timer , unit16 value);
Std_ReturnType Timer3_Read_Value(const timer3_t *timer , unit16 *value);


#endif	/* HAL_TIMER3_H */


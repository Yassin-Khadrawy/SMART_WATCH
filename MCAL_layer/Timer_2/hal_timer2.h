/* 
 * File:   hal_timer2.h
 * Author: KimoStore
 *
 * Created on October 28, 2024, 9:24 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

// section : includes
#include "../interrupts/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include <pic18f4620.h>

// macros declarations


// macros functions declarations

#define TIEMR2_MODULE_ENABLE()                      (T2CONbits.TMR2ON = 1)
#define TIEMR2_MODULE_DISABLE()                     (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALAR_SELECT(_PRESCALAR_)        (T2CONbits.T2CKPS = _PRESCALAR_)

#define TIMER2_POSTSCALAR_SELECT(_POSTSCALAR_)      (T2CONbits.TOUTPS = _POSTSCALAR_)


// data type declarations
typedef enum
{
    TIMER2_PRESCALER_DIV_BY_1 = 0,
    TIMER2_PRESCALER_DIV_BY_4,
    TIMER2_PRESCALER_DIV_BY_16,
}timer2_prescaler_select_t;

typedef enum
{
    TIMER2_POSTSCALER_DIV_BY_1 = 0,
    TIMER2_POSTSCALER_DIV_BY_2,
    TIMER2_POSTSCALER_DIV_BY_3,
    TIMER2_POSTSCALER_DIV_BY_4,
    TIMER2_POSTSCALER_DIV_BY_5,
    TIMER2_POSTSCALER_DIV_BY_6,
    TIMER2_POSTSCALER_DIV_BY_7,
    TIMER2_POSTSCALER_DIV_BY_8,
    TIMER2_POSTSCALER_DIV_BY_9,
    TIMER2_POSTSCALER_DIV_BY_10,
    TIMER2_POSTSCALER_DIV_BY_11,
    TIMER2_POSTSCALER_DIV_BY_12,
    TIMER2_POSTSCALER_DIV_BY_13,
    TIMER2_POSTSCALER_DIV_BY_14,
    TIMER2_POSTSCALER_DIV_BY_15,
    TIMER2_POSTSCALER_DIV_BY_16,
}timer2_postscaler_select_t;

typedef struct
{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*timer2_interrupt_handler)(void);
    interrupt_priority_cfg priority;
#endif
    timer2_postscaler_select_t postscaler_enum;
    timer2_prescaler_select_t prescaler_enum;
    unit8 timer1_preload_value;
}timer2_t;

// function declarations

Std_ReturnType Timer2_Init(const timer2_t *timer);
Std_ReturnType Timer2_DeInit(const timer2_t *timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *timer , unit16 value);
Std_ReturnType Timer2_Read_Value(const timer2_t *timer , unit16 *value);


#endif	/* HAL_TIMER2_H */


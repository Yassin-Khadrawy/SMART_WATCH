/* 
 * File:   hal_timer.h
 * Author: KimoStore
 *
 * Created on October 23, 2024, 11:04 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

// section : includes

#include <pic18f4620.h>
#include "../../MCAL_layer/mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupts/mcal_internal_interrupt.h"
// macros declarations
#define TIMER0_PRESCALER_ENABLE_CFG           1
#define TIMER0_PRESCALER_DISABLE_CFG          0
#define TIMER0_RISING_EDGE_CFG                1
#define TIMER0_FALLING_EDGE_CFG               0
#define TIMER0_TIMER_MODE                     1
#define TIMER0_COUNTER_MODE                   0
#define TIMER0_8_BIT_MODE                     1
#define TIMER0_16_BIT_MODE                    0

// macros functions declarations


#define TIMER0_PRESCALER_ENABLE()           (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()          (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE_ENABLE()         (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()        (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT = 0)

#define TIMER0_MODULE_ENABLE()              (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()             (T0CONbits.TMR0ON = 0)


// data type declarations
typedef enum
{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
}timer0_prescaler_select_t;

typedef struct
{
    unit8 prescaler           : 1 ;
    unit8 edge                : 1 ;
    unit8 timer0_mode         : 1 ;
    unit8 timer_register_size : 1;
    unit16 timer0_pteload_value;
    unit8 timer0_reserved : 4;
    timer0_prescaler_select_t prescaler_value;
    #if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        void (* TIMER0_InterruptHandler)(void);
        interrupt_priority_cfg priority;
    #endif
}timer0_t;

// function define
Std_ReturnType Timer0_Init(const timer0_t *timer);
Std_ReturnType Timer0_DeInit(const timer0_t *timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *timer , unit16 value);
Std_ReturnType Timer0_Read_Value(const timer0_t *timer , unit16 *value);

#endif	/* HAL_TIMER0_H */


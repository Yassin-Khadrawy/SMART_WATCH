/* 
 * File:   mcal_external_interrupt.h
 * Author: KimoStore
 *
 * Created on October 10, 2024, 9:40 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

// section : includes
#include "mcal_interruot_config.h"

// macros declarations


// macros functions declarations
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this routine sets the interrupt enable for the external interrupt*/
#define EXT_INT0_InterruptsEnable()          (INTCONbits.INT0IE = 1)
/* this routine clears the interrupt enable for the external interrupt*/
#define EXT_INT0_InterruptsDisable()         (INTCONbits.INT0IE = 0)

/* this routine clear the interrupt flag for the external interrupt*/
#define EXT_INT0_InterruptsFlagClear()       (INTCONbits.INT0IF= 0)

/* this routine sets the edge detect of the external interrupt to negative edge*/
#define EXT_INT0_RisingEdgeSet()             (INTCON2bits.INTEDG0 = 1)
/* this routine sets the edge detect of the external interrupt to positive edge*/
#define EXT_INT0_FallingEdgeSet()            (INTCON2bits.INTEDG0 = 0)


/* this routine sets the interrupt enable for the external interrupt*/
#define EXT_INT1_InterruptsEnable()          (INTCON3bits.INT1IE= 1)
/* this routine clears the interrupt enable for the external interrupt*/
#define EXT_INT1_InterruptsDisable()         (INTCON3bits.INT1IE = 0)

/* this routine clear the interrupt flag for the external interrupt*/
#define EXT_INT1_InterruptsFlagClear()       (INTCON3bits.INT1IF = 0)

/* this routine sets the edge detect of the external interrupt to negative edge*/
#define EXT_INT1_RisingEdgeSet()             (INTCON2bits.INTEDG1 = 1)
/* this routine sets the edge detect of the external interrupt to positive edge*/
#define EXT_INT1_FallingEdgeSet()            (INTCON2bits.INTEDG1 = 0)



/* this routine sets the interrupt enable for the external interrupt*/
#define EXT_INT2_InterruptsEnable()          (INTCON3bits.INT2IE= 1)
/* this routine clears the interrupt enable for the external interrupt*/
#define EXT_INT2_InterruptsDisable()         (INTCON3bits.INT2IE = 0)

/* this routine clear the interrupt flag for the external interrupt*/
#define EXT_INT2_InterruptsFlagClear()       (INTCON3bits.INT2IF = 0)

/* this routine sets the edge detect of the external interrupt to negative edge*/
#define EXT_INT2_RisingEdgeSet()             (INTCON2bits.INTEDG2 = 1)
/* this routine sets the edge detect of the external interrupt to positive edge*/
#define EXT_INT2_FallingEdgeSet()            (INTCON2bits.INTEDG2 = 0)
/*********************************/
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the edge detect of the external interrupt to negative edge*/
#define EXT_INT1_HighPrioritySet()             (INTCON3bits.INT1IP = 1)
/* this routine sets the edge detect of the external interrupt to positive edge*/
#define EXT_INT1_LowPrioritySet()              (INTCON3bits.INT1IP = 0)
/* this routine sets the edge detect of the external interrupt to negative edge*/
#define EXT_INT2_HighPrioritySet()             (INTCON3bits.INT2IP = 1)
/* this routine sets the edge detect of the external interrupt to positive edge*/
#define EXT_INT2_LowPrioritySet()              (INTCON3bits.INT2IP = 0)


#endif
/*********************************/

#endif



#if EXTERNAL_INTERRUPT_Onchange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this routine sets the interrupt enable to external interrupt , RBx*/
#define EXT_RBx_InterruptEnable()              (INTCONbits.RBIE = 1)
/* this routine clears the interrupt enable to external interrupt , RBx*/
#define EXT_RBx_InterruptDisable()             (INTCONbits.RBIE = 0)
/* this routine clears the interrupt flag to external interrupt , RBx*/
#define EXT_RBx_InterruptFlagClear()           (INTCONbits.RBIF = 0)


#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine sets the external interrupt priority to high priority , RBx*/
#define EXT_RBx_HighPrioritySet()             (INTCON2bits.RBIP = 1)
/* this routine sets the external interrupt priority to low priority , RBx*/
#define EXT_RBx_LowPrioritySet()              (INTCON2bits.RBIP = 0)

#endif

#endif

// data type declarations

typedef void(*InterruptHandler)(void);

typedef enum
{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE,
}interrupt_INTx_edge;

typedef enum
{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,
}interrupt_INTx_sorc;


typedef struct 
{
    void (* EXT_InterruptHandler)(void);
    pin_config_t  mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_sorc sorc;
    interrupt_priority_cfg prio;
}interrupt_INTx_t;

typedef struct 
{
    void (* EXT_InterruptHandler_HIGH)(void);
    void (* EXT_InterruptHandler_LOW)(void);
    pin_config_t  mcu_pin;
    interrupt_priority_cfg prio;
}interrupt_RBx_t;

// function declarations

Std_ReturnType interrupt_INTx_init(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t *int_obj);
Std_ReturnType interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */


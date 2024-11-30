/* 
 * File:   mcal_interruot_config.h
 * Author: KimoStore
 *
 * Created on October 10, 2024, 9:43 PM
 */

#ifndef MCAL_INTERRUOT_CONFIG_H
#define	MCAL_INTERRUOT_CONFIG_H

// section : includes

#include <pic18f4620.h>
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_config.h"
// macros declarations
#define  INTERRUPT_ENABLE                  1
#define  INTERRUPT_DISENABLE               0
#define  INTERRUPT_OCCUR                   1
#define  INTERRUPT_NOT_OCCUR               0
#define  INTERRUPT_PRIORITY_ENALBE         1
#define  INTERRUPT_PRIORITY_DISENALBE      0


// macros functions declarations
/************************************/
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this micro will enable priority levels on interrupts */
#define INTERRUPT_PriorityLevelEnable() (RCONbits.IPEN = 1)

/* this micro will disable priority levels on interrupts */
#define INTERRUPT_PriorityLevelDisable() (RCONbits.IPEN = 0)

/* this micro will enable high priority global interrupts */
#define INTERRUPT_GLOBALPriorityInterruptHighEnable() (INTCONbits.GIEH = 1)

/* this micro will enable low priority global interrupts */
#define INTERRUPT_GLOBALPriorityInterruptHighDisable() (INTCONbits.GIEH = 0)


/* this micro will enable high priority global interrupts */
#define INTERRUPT_GLOBALPriorityInterruptlowEnable() (INTCONbits.GIEL = 1)

/* this micro will enable low priority global interrupts */
#define INTERRUPT_GLOBALPriorityInterruptlowDisable() (INTCONbits.GIEL = 0)
#else
/* this micro will enable global interrupts */
#define INTERRUPT_GLOBALInterruptEnable() (INTCONbits.GIE = 1)

/* this micro will disable global interrupts */
#define INTERRUPT_GLOBALInterruptDisable() (INTCONbits.GIE = 0)

/* this micro will enable high priority Peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

/* this micro will enable low priority Peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif
/************************************/

/************************************/
// data type declarations
typedef enum
{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY,
}interrupt_priority_cfg;

// function declarations
//

#endif	/* MCAL_INTERRUOT_CONFIG_H */


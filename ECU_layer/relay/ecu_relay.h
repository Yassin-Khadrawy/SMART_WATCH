/* 
 * File:   ecu_relay.h
 * Author: KimoStore
 *
 * Created on September 19, 2024, 1:43 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H



// section : includes

#include "ecu_relay_config.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

// macros declarations
#define RELAY_ON_STATUS   0x01
#define RELAY_OFF_STATUS  0x00

// macros functions declarations


// data type declarations
typedef struct 
{
    unit8 relay_port   : 4;
    unit8 relay_pin    : 3 ;
    unit8 relay_status : 1;
}relay_t;

// function declarations
Std_ReturnType relay_initialized(relay_t *relay);
Std_ReturnType relay_turn_on(relay_t *relay);
Std_ReturnType relay_turn_off(relay_t *relay);
#endif	/* ECU_RELAY_H */


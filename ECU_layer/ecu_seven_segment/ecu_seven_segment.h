/* 
 * File:   ecu_seven_segment.h
 * Author: KimoStore
 *
 * Created on September 22, 2024, 9:59 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H



// section : includes
#include "ecu_seven_segment.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

// macros declarations

#define SEGMENT_PIN_0     0
#define SEGMENT_PIN_1     1
#define SEGMENT_PIN_2     2
#define SEGMENT_PIN_3     3
#define SEGMENT_PIN_4     4
#define SEGMENT_PIN_5     5
#define SEGMENT_PIN_6     6
#define SEGMENT_PIN_7     7
// macros functions declarations


// data type declarations

typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,        
}segment_type_t;

typedef struct
{
    pin_config_t   segment_pins[8];
    segment_type_t segment_type;
}segment_t;


// function declarations
Std_ReturnType seven_segment_initialized(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg , unit8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */


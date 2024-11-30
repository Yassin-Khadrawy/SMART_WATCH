#include "ecu_layer_init.h"

/**
 * @brief Used to start a process or operation.
 */
button_t BUTTON_START =
{
    .button_pin.dirction=INPUT,
    .button_pin.logic = LOW,
    .button_pin.pin = pin4,
    .button_pin.port = PORTD_INDEX,
    .button_state =  BUTTON_RELEASED,
    .button_connect = ACTIVE_HIGH,
};

/**
 * @brief  Adjusts or increments minutes in a time-related application.
 */
button_t BUTTON_MINUTES =
{
    .button_pin.dirction=INPUT,
    .button_pin.logic = LOW,
    .button_pin.pin = pin5,
    .button_pin.port = PORTD_INDEX,
    .button_state =  BUTTON_RELEASED,
    .button_connect = ACTIVE_HIGH,
};

/**
 * @brief Adjusts or increments hours in a time-related application.
 */
button_t BUTTON_HOURS =
{
    .button_pin.dirction=INPUT,
    .button_pin.logic = LOW,
    .button_pin.pin = pin6,
    .button_pin.port = PORTD_INDEX,
    .button_state =  BUTTON_RELEASED,
    .button_connect = ACTIVE_HIGH,
};

/**
 * @brief  Indicates or controls a charging-related process.
 */
button_t BUTTON_CHARGING =
{
    .button_pin.dirction=INPUT,
    .button_pin.logic = LOW,
    .button_pin.pin = pin1,
    .button_pin.port = PORTC_INDEX,
    .button_state =  BUTTON_RELEASED,
    .button_connect = ACTIVE_HIGH,
};

/**
 * @brief Triggers or interacts with GPS functionality.
 */


/**
 * @brief This configuration enables an 8-bit character LCD to display information.
          The control pins (lcd_rs, lcd_enable) 
 *        and data lines (lcd_data) are mapped to 
 *        the microcontroller's ports for communication.
 */

chr_lcd_8bit_t lcd_1 = {
    .lcd_rs.port = PORTD_INDEX,
    .lcd_rs.pin = pin2,
    .lcd_rs.dirction = OUTPUT,
    .lcd_rs.logic = LOW,
    .lcd_enable.port = PORTD_INDEX,
    .lcd_enable.pin = pin3,
    .lcd_enable.dirction = OUTPUT,
    .lcd_enable.logic = LOW,
    
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = pin0,
    .lcd_data[0].dirction = OUTPUT,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].port = PORTE_INDEX,
    .lcd_data[1].pin = pin0,
    .lcd_data[1].dirction = OUTPUT,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].port = PORTE_INDEX,
    .lcd_data[2].pin = pin1,
    .lcd_data[2].dirction = OUTPUT,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = pin3,
    .lcd_data[3].dirction = OUTPUT,
    .lcd_data[3].logic = LOW,
    
    .lcd_data[4].port = PORTC_INDEX,
    .lcd_data[4].pin = pin4,
    .lcd_data[4].dirction = OUTPUT,
    .lcd_data[4].logic = LOW,
    
    .lcd_data[5].port = PORTC_INDEX,
    .lcd_data[5].pin = pin5,
    .lcd_data[5].dirction = OUTPUT,
    .lcd_data[5].logic = LOW,
    
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = pin0,
    .lcd_data[6].dirction = OUTPUT,
    .lcd_data[6].logic = LOW,
    
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = pin1,
    .lcd_data[7].dirction = OUTPUT,
    .lcd_data[7].logic = LOW
};

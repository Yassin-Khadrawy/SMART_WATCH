/* 
 * File:   ecu_led.c
 * Author: KimoStore
 *
 * Created on September 7, 2024, 9:48 PM
 */
#include "ecu_led.h"

/**
 * 
 * @param led : pointer to led module configuration 
 * @return 
 */
Std_ReturnType led_initialize(const led_t  *led )
{    
   Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name ,
                                   .pin = led->pin ,
                                   .dirction = OUTPUT ,
                                   .logic = led->led_status};
        gpio_pin_intialize(&pin_obj);
    }
   return ret;
}


/**
 * 
 * @param led : pointer to led module configuration 
 * @return 
 */

Std_ReturnType led_turn_on_initialize(const led_t  *led )
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t pin_obj = {.port = led->port_name ,
                                   .pin = led->pin ,
                                   .dirction = OUTPUT ,
                                   .logic = led->led_status};
         gpio_pin_write_logic(&pin_obj , HIGH);
    }
    return ret;
} 

/**
 * 
 * @param led : pointer to led module configuration 
 * @return 
 */
Std_ReturnType led_turn_off_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if (NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,
                                   .pin = led->pin,
                                   .dirction = OUTPUT,
                                   .logic = led->led_status};  // Force the logic to LOW for turning off
        gpio_pin_write_logic(&pin_obj, LOW);
    }
    return ret;
}
  

/**
 * 
 * @param led : pointer to led module configuration 
 * @return 
 */
Std_ReturnType led_turn_toggle_initialize(const led_t  *led )
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name ,
                                   .pin = led->pin ,
                                   .dirction = OUTPUT ,
                                   .logic = led->led_status};
         gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}


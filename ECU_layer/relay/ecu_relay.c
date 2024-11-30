/* 
 * File:   ecu_relay.h
 * Author: KimoStore
 *
 * Created on September 19, 2024, 1:43 PM
 */


#include "ecu_relay.h"
// function declarations
Std_ReturnType relay_initialized(relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = relay->relay_port ,
                                .pin = relay->relay_pin ,
                                .dirction = OUTPUT ,
                                .logic = relay->relay_status };
        
        gpio_pin_intialize(&pin_obj);
    }
    return ret;
}
/**
 * @brief
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_on(relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = relay->relay_port ,
                                .pin = relay->relay_pin ,
                                .dirction = OUTPUT ,
                                .logic = relay->relay_status };
        
        gpio_pin_write_logic(&pin_obj , HIGH);
    }
    return ret;
}
/**
 * @brief
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_off(relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = relay->relay_port ,
                                .pin = relay->relay_pin ,
                                .dirction = OUTPUT ,
                                .logic = relay->relay_status };
        
        gpio_pin_write_logic(&pin_obj , LOW);
    }
    return ret;
    
}
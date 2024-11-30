/* 
 * File:   ecu_dc_motor.c
 * Author: KimoStore
 *
 * Created on September 20, 2024, 10:10 AM
 */

#include "ecu_dc_motor.h"

Std_ReturnType dc_motor_initialized(const dc_motor_t  *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t motor_1 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_status };
         
         
         pin_config_t motor_2 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_status };
        gpio_pin_intialize(&motor_1);
        gpio_pin_intialize(&motor_2);
    }
}
Std_ReturnType dc_motor_move_right(const dc_motor_t  *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_1 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_status };
         
         
         pin_config_t motor_2 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_status };
        gpio_pin_write_logic(&motor_1 , LOW );
        gpio_pin_write_logic(&motor_2 , HIGH);
    }
}
Std_ReturnType dc_motor_move_left(const dc_motor_t  *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_1 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_status };
         
         
         pin_config_t motor_2 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_status };
        gpio_pin_write_logic(&motor_1 , HIGH);
        gpio_pin_write_logic(&motor_2 , LOW );
    }
}
Std_ReturnType dc_motor_stop(const dc_motor_t  *dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t motor_1 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ZERO].dc_motor_status };
         
         
         pin_config_t motor_2 = {.port = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_port ,
                                .pin = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_pin ,
                                .dirction = OUTPUT ,
                                .logic = dc_motor->dc_motor[DC_MOTOR_PIN_ONE].dc_motor_status };
        gpio_pin_write_logic(&motor_1 , HIGH);
        gpio_pin_write_logic(&motor_2 , HIGH);
    }
}
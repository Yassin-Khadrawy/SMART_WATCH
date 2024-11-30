/* 
 * File:   ecu_seven_segment.c
 * Author: KimoStore
 *
 * Created on September 22, 2024, 9:59 AM
 */
#include "ecu_seven_segment.h"


Std_ReturnType seven_segment_initialized(const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(seg == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN_0]));
        gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN_1]));
        gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN_2]));
        gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN_3]));
        gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN_4]));
        gpio_pin_intialize(&(seg->segment_pins[SEGMENT_PIN_5]));  
    }
    return ret ;
}
Std_ReturnType seven_segment_write_number(const segment_t *seg , unit8 number)
{
    Std_ReturnType ret = E_OK;
    if((seg == NULL) && (number > 9))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_0]) , number&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_1]) , (number>>1)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_2]) , (number>>2)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_3]) , (number>>3)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_4]) , (number>>4)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_5]) , (number>>5)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_6]) , (number>>6)&0x01);
        gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN_7]) , (number>>7)&0x01);
        
    }
    return ret ;
}

#include "ecu_keypad.h"
#define _XTAL_FREQ 8000000





static const unit8 btn_values[ECU_KEYPAD_ROW][ECU_KEYPAD_COL] = 
{
    {'7' , '8' , '9' , '/'},
    {'4' , '5' , '6' , '*'},
    {'1' , '2' , '3' , '-'},
    {'#' , '0' , '=' , '+'}
};
/**
 * 
 * @param keypad_obj
 * @return 
 */

Std_ReturnType keypad_initialize(const keypad_t *keypad_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL == keypad_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
        unit8 count_row = 0;
        unit8 count_col = 0;
        for(count_row = 0 ; count_row < ECU_KEYPAD_ROW ; ++count_row)
        {
            ret = gpio_pin_intialize(&(keypad_obj->keypad_row_pins[count_row]));

        }
        for(count_col = 0 ; count_col < ECU_KEYPAD_COL ; ++count_col)
        {
            ret = gpio_pin_direction_intialize(&(keypad_obj->keypad_col_pins[count_col]));
        }
    }
    return ret ;
}

/**
 * 
 * @param keypad_obj
 * @param value
 * @return 
 */

Std_ReturnType keypad_get_value(const keypad_t *keypad_obj , unit8 *value)
{
    Std_ReturnType ret = E_OK;
    unit8 count_row = 0;
    unit8 count_row_cpy = 0;
    unit8 count_col = 0;
    unit8 col_logic = 0;
    
    if(NULL == keypad_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
        
         for(count_row = 0 ; count_row < ECU_KEYPAD_ROW ; ++count_row)
        {
             
              for(count_row_cpy = 0 ; count_row_cpy < ECU_KEYPAD_ROW ; ++count_row_cpy)
              {
                  ret = gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[count_row_cpy]) , LOW);

              }
               gpio_pin_write_logic(&(keypad_obj->keypad_row_pins[count_row]) , HIGH);
               for(count_col = 0 ; count_col < ECU_KEYPAD_COL ; ++count_col)
              {
                  ret = gpio_pin_read_logic(&(keypad_obj->keypad_col_pins[count_col]) , &col_logic);
                  if(HIGH == col_logic)
                  {
                      *value = btn_values[count_row][count_col];
                  }
              }
        }
         
   
        
    }
    return ret ;
}

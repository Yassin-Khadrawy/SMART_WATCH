#include "ecu_button.h"


Std_ReturnType button_intialized(button_t *BUTTON)
{
    Std_ReturnType ret = E_OK;
    if(NULL == BUTTON )
    {
        ret = E_NOT_OK;
    }
    else
    {
         gpio_pin_direction_intialize(&(BUTTON->button_pin));
    }

}
Std_ReturnType button_read_intialized(button_t *BUTTON , button_state_t *button_read)
{
    Std_ReturnType ret = E_OK;
    logic_t PIN_LOGIC_STATUS = LOW;
    if((NULL == BUTTON)  || NULL == button_read)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_read_logic(&(BUTTON->button_pin) , &PIN_LOGIC_STATUS);
        if(ACTIVE_HIGH == BUTTON->button_connect)
        {
            if(PIN_LOGIC_STATUS == HIGH)
            {
                *button_read = BUTTON_PRESSED;
            }
            else
            {
                *button_read = BUTTON_RELEASED;
            }
        }
        else if(ACTIVE_LOW == BUTTON->button_connect)
        {
            if(PIN_LOGIC_STATUS == HIGH)
            {
                *button_read = BUTTON_RELEASED;
            }
            else
            {
                *button_read = BUTTON_PRESSED;
            }
        }
        else
        {
            /*nothing*/
        }
        ret = E_OK;
        
    }
    return ret;
}

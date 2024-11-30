/* 
 * File:   hal_gpio.h
 * Author: KimoStore
 *
 * Created on September 7, 2024, 9:14 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

// section : includes

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_confg.h" 
#include "hal_gpio_cfg.h"

// macros declarations
#define BIT_MASK                       (unit8) 1
#define PORT_PIN_MAX                   8
#define PORT_MAX_NUM                   5



// macros functions declarations
#define HWREG(_X)                      (*((volatile unit8 *)(-X)))

#define SET_BIT(REG ,BIT_POSTION)      (REG |= (BIT_MASK << BIT_POSTION))
#define CLEAR_BIT(REG ,BIT_POSTION)    (REG &= ~(BIT_MASK << BIT_POSTION))
#define TOGGLE_BIT(REG ,BIT_POSTION)   (REG ^= (BIT_MASK << BIT_POSTION))
#define READ_BIT(REG , BIT_POSN)       ((REG >> BIT_POSN) & BIT_MASK)
// data type declarations
typedef enum 
{
    LOW = 0,
    HIGH,
}logic_t;

typedef enum 
{
    OUTPUT,
    INPUT,
}direction_t;

typedef enum 
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
}pin_index_t;

typedef enum 
{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;

typedef struct
{
    unit8 port     : 3; /* @ref port_index_t  */
    unit8 pin      : 3; /* @ref port_index_t  */
    unit8 dirction : 1; /* @ref direction_t   */
    unit8 logic    : 1; /* @ref logic_t       */
}pin_config_t;



// function declarations]

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config , direction_t *direction);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config , logic_t  logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config , logic_t  *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);


Std_ReturnType gpio_port_direction_intialize(port_index_t port , unit8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port , unit8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port , unit8  logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, unit8  *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);


#endif	/* HAL_GPIO_H */


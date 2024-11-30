/* 
 * File:   ecu_chr_lcd.h
 * Author: KimoStore
 *
 * Created on September 28, 2024, 11:32 AM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

// section : includes

#include "ecu_chr_lcd_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include <xc.h>
// macros declarations
#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0X02
#define _LCD_ENTRY_M0DE                 0X06
#define _LCD_CURSOR_OFF_DISPLAY_ON      0X0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF     0X08
#define _LCD_CURSOR_ON_BLINK_ON         0X0F
#define _LCD_CURSOR_ON_BLINK_OFF        0X0E
#define _LCD_DISPLAY_SHIFT_LEFT         0X18
#define _LCD_DISPLAY_SHIFT_RIGHT        0X1C
#define _LCD_8BIT_MODE_2_LINE           0X38  
#define _LCD_4BIT_MODE_2_LINE           0X28 
#define _LCD_CGRAM_START                0X40
#define _LCD_DDRAM_START                0X80

#define ROW1                             1
#define ROW2                             2
#define ROW3                             3
#define ROW4                             4


// macros functions declarations


// data type declarations
typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_enable;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_enable;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

// function declarations

Std_ReturnType lcd_4bit_initialized(const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , unit8 command);
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd , unit8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd , unit8 row , unit8 column, unit8 data);
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd , unit8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd ,unit8 row , unit8 column, unit8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd , unit8 row , unit8 column,const unit8 _chr[] , unit8 mem_pos);


Std_ReturnType lcd_8bit_initialized(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , unit8 command);
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd , unit8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd , unit8 row , unit8 column, unit8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd , unit8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd ,unit8 row , unit8 column, unit8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd , unit8 row , unit8 column,const unit8 _chr[] , unit8 mem_pos);

Std_ReturnType convert_byte_to_string(unit8 value , unit8 *str);
Std_ReturnType convert_short_to_string(unit8 value , unit8 *str);
Std_ReturnType convert_int_to_string(unit8 value , unit8 *str);
Std_ReturnType convert_float_two_dec_to_string(float value, unit8 *str);
Std_ReturnType convert_float_six_dec_to_string(float value, unit8 *str);

#endif	/* ECU_CHR_LCD_H */


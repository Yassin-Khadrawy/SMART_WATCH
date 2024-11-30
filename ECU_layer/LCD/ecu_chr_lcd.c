#include "ecu_chr_lcd.h"
#include "pic18f4620.h"

#define _XTAL_FREQ 8000000
static Std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t *lcd  , unit8 _data_command);
static Std_ReturnType lcd_4bits_send_enable(const chr_lcd_8bit_t *lcd );
static Std_ReturnType lcd_8bits_send_enable(const chr_lcd_8bit_t *lcd );
static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd  , unit8 row , unit8 col);
static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd  , unit8 row , unit8 col);
Std_ReturnType lcd_4bit_initialized(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    int counter = 0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_enable));
        for(counter = 0 ; counter < 4 ; ++counter)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command( lcd , _LCD_CLEAR);
        ret = lcd_4bit_send_command( lcd , _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command( lcd , _LCD_ENTRY_M0DE);
        ret = lcd_4bit_send_command( lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command( lcd , _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command( lcd , 0X80);
    }
}
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , unit8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , LOW);
        ret = lcd_send_4bits(lcd , command >> 4);
        ret = lcd_4bits_send_enable(lcd);
        ret = lcd_send_4bits(lcd , command);
        ret = lcd_4bits_send_enable(lcd);
        
        
    }
}
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd , unit8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , HIGH);
        ret = lcd_send_4bits(lcd , data >> 4);
        ret = lcd_4bits_send_enable(lcd);
        ret = lcd_send_4bits(lcd , data);
        ret = lcd_4bits_send_enable(lcd);
    }
}
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd , unit8 row , unit8 column, unit8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bits_set_cursor(lcd , row , column);
        ret = lcd_4bit_send_char_data(lcd  , data);
    }
}
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd , unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd  , *str);
            str++;
        }
    }
}
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd ,unit8 row , unit8 column, unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bits_set_cursor( lcd  , row , column);
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd  , *str++);
            
        }
        
    }
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd , unit8 row , unit8 column,const unit8 _chr[] , unit8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
}

/////////////////////////////////////////////////
//********************************************//
///////////////////////////////////////////////


Std_ReturnType lcd_8bit_initialized(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    int counter = 0;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_enable));
        for(counter = 0 ; counter < 8 ; ++counter)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command( lcd , _LCD_CLEAR);
        ret = lcd_8bit_send_command( lcd , _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command( lcd , _LCD_ENTRY_M0DE);
        ret = lcd_8bit_send_command( lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command( lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command( lcd , 0X80);
    }
}
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , unit8 command)
{
    unit8 counter = 0 ;
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , LOW);
        for(counter = 0 ; counter < 8 ; ++counter)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]) , (command >> counter) & 0x01 );
        }
        ret = lcd_8bits_send_enable(lcd);
    }
}
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd , unit8 data)
{
    Std_ReturnType ret = E_OK;
    unit8 counter = 0 ;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , HIGH);
        for(counter = 0 ; counter < 8 ; ++counter)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[counter]) , (data >> counter) & 0x01 );
        }
        ret = lcd_8bits_send_enable(lcd);
    }
}
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd , unit8 row , unit8 column, unit8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bits_set_cursor(   lcd  , row , column);
        ret = lcd_8bit_send_char_data(lcd , data);
    }
}
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd , unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd  , *str);
            str++;
        }
    }
}
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd ,unit8 row , unit8 column, unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if(lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bits_set_cursor( lcd  , row , column);
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd  , *str);
            str++;
        }
        
    }
}

Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, unit8 row, unit8 column, 
                                         const unit8 _chr[], unit8 mem_pos){
    Std_ReturnType ret = E_OK;
    unit8 lcd_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter=0; lcd_counter<=7; ++lcd_counter){
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

Std_ReturnType convert_byte_to_string(unit8 value , unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , 4);
        sprintf((char *)str , "%i" , value);
    }
}
Std_ReturnType convert_short_to_string(unit8 value , unit8 *str)
{
    Std_ReturnType ret = E_OK;
    unit8 tempstring[6] = {0};
    unit8 datacounter = 0;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str , ' ' , 6);
        str[5] = '\0';
        sprintf((char *)tempstring , "%i" , value);
        while(tempstring[datacounter] != '\0')
        {
            str[datacounter] = tempstring[datacounter];
            datacounter++;
        }
    }
}
Std_ReturnType convert_int_to_string(unit8 value , unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str , '\0' , 11);
        sprintf((char *)str , "%i" , value);
    }
}

Std_ReturnType convert_float_two_dec_to_string(float value, unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if (str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 11);
        sprintf((char *)str, "%.1f", value);  // Format the float to 2 decimal places
    }
    return ret;
}

Std_ReturnType convert_float_six_dec_to_string(float value, unit8 *str)
{
    Std_ReturnType ret = E_OK;
    if (str == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, '\0', 11);
        sprintf((char *)str, "%.6f", value);  // Format the float to 2 decimal places
    }
    return ret;
}

static Std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t *lcd  , unit8 _data_command)
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , (_data_command >> 0) & 0x01 );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , (_data_command >> 1) & 0x01 );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , (_data_command >> 2) & 0x01 );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , (_data_command >> 3) & 0x01 );
    return ret ;
}

static Std_ReturnType lcd_4bits_send_enable(const chr_lcd_8bit_t *lcd )
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_enable) , HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_enable) , LOW);
    return ret ;
}

static Std_ReturnType lcd_8bits_send_enable(const chr_lcd_8bit_t *lcd )
{
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_enable) , HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_enable) , LOW);
    return ret ;
}

static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *lcd  , unit8 row , unit8 col)
{
    col--;
    Std_ReturnType ret = E_OK;
    switch(row)
    {
        case ROW1 : 
            ret = lcd_8bit_send_command( lcd , (0X80 + col));
            break;
        case ROW2 : 
            ret = lcd_8bit_send_command( lcd , (0XC0 + col));
            break;
        case ROW3 : 
            ret = lcd_8bit_send_command( lcd , (0X94 + col));
            break;
        case ROW4 : 
            ret = lcd_8bit_send_command( lcd , (0XD4 + col));
            break;
        default: ;    
        
    }
    return ret;
}

static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *lcd  , unit8 row , unit8 col)
{
    col--;
    Std_ReturnType ret = E_OK;
    switch(row)
    {
        case ROW1 : 
            ret = lcd_4bit_send_command( lcd , (0X80 + col));
            break;
        case ROW2 : 
            ret = lcd_4bit_send_command( lcd , (0XC0 + col));
            break;
        case ROW3 : 
            ret = lcd_4bit_send_command( lcd , (0X94 + col));
            break;
        case ROW4 : 
            ret = lcd_4bit_send_command( lcd , (0XD4 + col));
            break;
        default: ;    
        
    }
    return ret;
}
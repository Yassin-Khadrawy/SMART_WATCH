/*
 * File:   MAIN_MICRO.c
 * Author: Yassin_Khadrawy
 *
 * Created on September 7, 2024, 7:29 PM
 */
#include "application.h"

/**
 * @brief The entry point of the application. Initializes and runs the main functionality of the system in a continuous loop.
 * @param NONE
 * @return 
 * @functionality  Initializes the application and clears the LCD screen.
                   Continuously reads button states and adjusts the system state based on user input.
                   Monitors sensors and updates the system based on their readings.
                   Handles normal clock operations, GPS initialization, and ADC conversions.
 */
int main() 
{
    Std_ReturnType ret = E_NOT_OK;
    application();
    
    if(clear_watch == 0)
    {
        ret = lcd_8bit_send_command(&lcd_1 , _LCD_CLEAR);
        clear_watch = 1;
        clear_normal_watch = 0 ;
    }
    while(1) 
    {
        buttton_reads();
        if(button_start == BUTTON_RELEASED && button_gps == BUTTON_RELEASED)
        {
            adjust_normal_clock();
        }
        else if(button_start == BUTTON_PRESSED)
        {
            if(clear_adjust_the_watch == 1)
            {
                ret = lcd_8bit_send_command(&lcd_1 , _LCD_CLEAR);
                clear_adjust_the_watch = 0;
                clear_normal_watch = 1;
                clear_watch = 0 ;
                clear_GPS = 0 ;
            }
            if(timer0_1000ms == 1)
            {
                timer0_1000ms = 0;
                normal_clock_watch();
            }  
            else{/*nothing*/}
            ADC_interrupt_start();
            data_at_watch();
            rain_sensor();
            pressure_sensor();
            temperature_sensor();
            LDR_sensor();
            charge_read();
        }

        ret = EUSART_ASYNC_Init(&usart_obj);
        
    }
    return (EXIT_SUCCESS);
}

                      /*********initialization functions of main code**********/

/**
 * @brief Initializes all required hardware components, including LCD, buttons, ADC, GPIO, Timer0, and PWM.
 * @param NONE
 * @return  
 */
void application(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_8bit_initialized(&lcd_1);
    ret = button_intialized(&BUTTON_START);
    ret = button_intialized(&BUTTON_MINUTES);
    ret = button_intialized(&BUTTON_HOURS);
    ret = button_intialized(&BUTTON_CHARGING);
    ret = ADC_Init(&adc_sensor);
    ret = gpio_pin_direction_intialize(&RAIN_D);
    ret = Timer0_Init(&timer0_timer_obj);
    PWM_Init();
    
}
/**
 * @brief Reads the state of buttons and rain detection input pin and stores the state in global variables.
 * @param NONE
 * @return  
 */
void buttton_reads(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = gpio_pin_read_logic(&RAIN_D , &rain_state);
    ret = button_read_intialized(&BUTTON_START , &button_start);
    ret = button_read_intialized(&BUTTON_MINUTES , &button_min);
    ret = button_read_intialized(&BUTTON_HOURS , &button_hour);
    ret = button_read_intialized(&BUTTON_CHARGING , &button_charging);
}
/**
 * @brief Sets a flag (timer0_1000ms) every 1 second using Timer0 interrupts.
 * @param NONE
 * @return  
 */
void Timer0_DefaultInterruptHandler_1000ms(void)
{
    timer0_1000ms = 1;
}
/**
 * @brief Handles ADC interrupt and reads ADC values for different channels in a round-robin fashion.
 * @param NONE
 * @return  
 */
void ADC_DefaultInterruptHandler(void)
{
    Std_ReturnType ret = E_NOT_OK;
    if(0 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_sensor, &adc_res_1);
        ADC_Req = 1;
    }
    else if(1 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_sensor, &adc_res_2);
        ADC_Req = 2;
    }
    else if(2 == ADC_Req){
        ret = ADC_GetConversionResult(&adc_sensor, &adc_res_3);
        ADC_Req = 0;
    }
    else { /* Nothing */ }
}
/**
 * @brief Handles framing errors for the EUSART module and increments the framing error counter.
 * @param NONE
 * @return  
 */
void EUSART_FramingDefaultInterruptHandler(void)
{
    Std_ReturnType ret = E_NOT_OK;
    unit8 data;
    EUSART_ASYNC_ReadByteNonBlocking(&usart_obj , &data);
    valid_framing++;
}
/**
 * @brief Handles overrun errors in the EUSART module and resets the receiver.
 * @param NONE
 * @return  
 */
void EUSART_OverrunDefaultInterruptHandler(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = EUSART_ASYNC_RESTART_RX();
    valid_overrun++;
}
/**
 * @brief Handles received data from EUSART by storing it into a global variable and increments the RX counter.
 * @param NONE
 * @return  
 */
void EUSART_RxDefaultInterruptHandler(void)
{
    Std_ReturnType ret = E_NOT_OK;
    //unit8 data_temp = 0;
    valid_rx++;
    ret = EUSART_ASYNC_ReadByteBlocking( &usart_obj , (unit8 *)&rec_uart_data );
    //data_temp = RCREG;
}
/**
 * @brief Handles transmission of data over EUSART.
 * @param NONE
 * @return  
 */
void EUSART_TxDefaultInterruptHandler(void)
{
    Std_ReturnType ret = E_NOT_OK;
    valid_tx++;
    ret = EUSART_ASYNC_WriteByteBlocking( &usart_obj , rec_uart_data);
}
/**
 * @brief Starts an ADC conversion on specific channels based on the current request.
 * @param NONE
 * @return  
 */
void ADC_interrupt_start(void)
{
    Std_ReturnType ret = E_NOT_OK;
    if(0 == ADC_Req){
        ret = ADC_StartConversion_Interrupt(&adc_sensor, ADC_CHANNEL_AN0);
    }
    else if(1 == ADC_Req){
        ret = ADC_StartConversion_Interrupt(&adc_sensor, ADC_CHANNEL_AN1);
    }
    else if(2 == ADC_Req){
        ret = ADC_StartConversion_Interrupt(&adc_sensor, ADC_CHANNEL_AN2);
    }
}
/**
 * @brief Reads the state of the rain sensor and displays the appropriate status (ON or OFF) on the LCD.
 * @param NONE
 * @return  
 */
void rain_sensor(void)
{
    Std_ReturnType ret = E_NOT_OK;
    if(rain_state == its_rain_now)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 4 , 13 , "RAIN:   " );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 4 , 18 , "ON" );
    }
    else if(rain_state == its_not_rain_now)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 4 , 13 , "RAIN:OFF" );
    }
}
/**
 * @brief Reads the pressure sensor's ADC value, calculates the pressure in KPa, and displays it on the LCD.
 * @param NONE
 * @return  
 */
void pressure_sensor(void)
{
    Std_ReturnType ret = E_NOT_OK;
    final_pressure_read = adc_res_2;
    final_pressure_read = ((final_pressure_read/5.0)+0.095)*0.5999;
    ret = convert_float_two_dec_to_string(final_pressure_read , adc_res_2_txt);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 4 , 1 , "Air:" );
    ret = lcd_8bit_send_string_pos(&lcd_1  , 4 , 5 , adc_res_2_txt );
    ret = lcd_8bit_send_string_pos(&lcd_1  , 4 , 9 , "KPa" );
    
}
/**
 * @brief Reads the temperature sensor's ADC value, calculates the temperature in Celsius, and displays it on the LCD.
 * @param NONE
 * @return  
 */
void temperature_sensor(void)
{
    Std_ReturnType ret = E_NOT_OK;
    final_temp_read = adc_res_1 * 4.88f;
    final_temp_read /= 10;
    ret = convert_short_to_string(final_temp_read , adc_res_1_txt);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 1 , "Temp:" );
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 6 , adc_res_1_txt );
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 9 , "C" );
    ret = lcd_8bit_send_custom_char(&lcd_1  , 3 , 10 ,customChar ,0);
}
/**
 * @brief Reads the LDR sensor's ADC value and adjusts the PWM duty cycle accordingly.
 * @param NONE
 * @return  
 */
void LDR_sensor(void)
{
    adc_value = adc_res_3;;   
    pwm_duty = 1023 - adc_value;     
    PWM_SetDuty(pwm_duty);     
}
/**
 * @brief Displays the current date on the LCD, including the day, month, and year.
 * @param NONE
 * @return  
 */
void data_at_watch(void)
{
    Std_ReturnType ret = E_NOT_OK;
    
    ret = convert_byte_to_string(days_at_watch ,days_txt);
    ret = convert_byte_to_string(months_at_watch ,months_txt);
    ret = convert_byte_to_string(years_at_watch ,years_txt);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 3 , "Data:" );
    ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 15 , "20" );
    
    
    if(days_at_watch < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 9 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 10 , days_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 9 , days_txt );
    }
    ret = lcd_8bit_send_char_data_pos(&lcd_1  , 2 , 11 , '/' );
    if(months_at_watch < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 12 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 13 , months_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 12 , months_txt );
    }
    ret = lcd_8bit_send_char_data_pos(&lcd_1  , 2 , 14 , '/' );
    if(years_at_watch < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 17 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 18 , years_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 17 , years_txt );
    }
    
}
/**
 * @brief Implements a real-time clock that increments the time and date, displaying the current time on the LCD.
 * @param NONE
 * @return  
 */
void normal_clock_watch(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = convert_byte_to_string(seconds ,seconds_txt);
    ret = convert_byte_to_string(minutes ,minutes_txt);
    ret = convert_byte_to_string(hours ,hours_txt);
    if(seconds < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 13 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 14 , seconds_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 13 , seconds_txt );
    }
    ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 12 , ":" );
    if(minutes < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 10 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 11 , minutes_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 10 , minutes_txt );
    }
    ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 9 , ":" );
    if(hours < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 7 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 8 , hours_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 1 , 7 , hours_txt );
    }
    seconds++;
    if(seconds == 60)
    {
        minutes++;
        seconds = 0;
    }
    if(minutes == 60)
    {
        hours++;
        minutes = 0;
    }
    if(hours == 24)
    {
        hours = 0 ;
        minutes = 0;
        seconds = 0;
        days_at_watch++;
    }
    if(days_at_watch == 31)
    {
        days_at_watch = 0;
        months_at_watch++;
    }
    if(months_at_watch == 13)
    {
        months_at_watch = 0;
        years_at_watch++;
    }
    
}
/**
 * @brief Provides functionality to manually adjust the system clock using buttons. Updates the clock display accordingly
 * @param NONE
 * @return  
 */
void adjust_normal_clock(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_8bit_send_string_pos(&lcd_1  , 2 , 3 , "adjust the clock" );
    if(clear_adjust_the_watch == 0)
    {
        ret = lcd_8bit_send_command(&lcd_1 , _LCD_CLEAR);
    }
    else{/*nothing*/}
    if(button_min == BUTTON_PRESSED)
    {
        minutes++;
        if(minutes == 60)
        {
            minutes = 0;
        }
    }
    else
    {/*nothing*/}
    //////////////////////////////////////////////////////////////////////////////////////////////
    if(button_hour == BUTTON_PRESSED)
    {
        hours++;
        if(hours == 24)
        {
            hours = 0;
        }
    }
    else
    {/*nothing*/}
    //////////////////////////////////////////////////////////////////////////////////////////////
    ret = convert_byte_to_string(seconds ,seconds_txt);
    ret = convert_byte_to_string(minutes ,minutes_txt);
    ret = convert_byte_to_string(hours ,hours_txt);
    if(seconds < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 13 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 14 , seconds_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 13 , seconds_txt );
    }
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 12 , ":" );
    if(minutes < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 10 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 11 , minutes_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 10 , minutes_txt );
    }
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 9 , ":" );
    if(hours < 10)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 7 , "0" );
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 8 , hours_txt );
    }
    else
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 7 , hours_txt );
    }
    clear_adjust_the_watch = 1;
    
}
/**
 * @brief Displays the charging icon and "100%" text on the LCD.
 * @param NONE
 * @return  
 */
void charge_it_100(void)
{
    Std_ReturnType ret = E_NOT_OK;
    unit8 clear_lcd = 0 ;
    if(clear_lcd == 0)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "    " );
        clear_lcd = 1;
    }
    ret = lcd_8bit_send_custom_char(&lcd_1  , 3 , 15 ,customChar_charge_100 ,1);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "100%" );
}
/**
 * @brief Displays the charging icon and "80%" text on the LCD.
 * @param NONE
 * @return  
 */
void charge_it_80(void)
{
    Std_ReturnType ret = E_NOT_OK;
    unit8 clear_lcd = 0 ;
    if(clear_lcd == 0)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "    " );
        clear_lcd = 1;
    }
    ret = lcd_8bit_send_custom_char(&lcd_1  , 3 , 15 ,customChar_charge_80 ,2);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "80%" );
}
/**
 * @brief Displays the charging icon and "60%" text on the LCD.
 * @param NONE
 * @return  
 */
void charge_it_60(void)
{
    Std_ReturnType ret = E_NOT_OK;
    unit8 clear_lcd = 0 ;
    if(clear_lcd == 0)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "    " );
        clear_lcd = 1;
    }
    ret = lcd_8bit_send_custom_char(&lcd_1  , 3 , 15 ,customChar_charge_60 ,3);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "60%" );
}
/**
 * @brief Displays the charging icon and "40%" text on the LCD.
 * @param NONE
 * @return  
 */
void charge_it_40(void)
{
    Std_ReturnType ret = E_NOT_OK;
    unit8 clear_lcd = 0 ;
    if(clear_lcd == 0)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "    " );
        clear_lcd = 1;
    }
    ret = lcd_8bit_send_custom_char(&lcd_1  , 3 , 15 ,customChar_charge_40 ,4);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "40%" );
}
/**
 * @brief Displays the charging icon and "20%" text on the LCD.
 * @param NONE
 * @return  
 */
void charge_it_20(void)
{
    Std_ReturnType ret = E_NOT_OK;
    unit8 clear_lcd = 0 ;
    if(clear_lcd == 0)
    {
        ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "    " );
        clear_lcd = 1;
    }
    ret = lcd_8bit_send_custom_char(&lcd_1  , 3 , 15 ,customChar_charge_20 ,5);
    ret = lcd_8bit_send_string_pos(&lcd_1  , 3 , 16 , "20%" );
}
/**
 * @brief Determines the charging percentage based on a counter and displays the appropriate charging icon and percentage on the LCD.
 * @param NONE
 * @return  
 */
void charge_read(void)
{
    charging_mode_precent++;
    if((0 <= charging_mode_precent) && (charging_mode_precent < 10000))
    {
        charge_it_100();
    }
    else if((10000 <= charging_mode_precent) && (charging_mode_precent < 20000))
    {
        charge_it_80();
    }
    else if((20000 <= charging_mode_precent) && (charging_mode_precent < 30000))
    {
        charge_it_60();
    }
    else if((30000 <= charging_mode_precent) && (charging_mode_precent < 40000))
    {
        charge_it_40();
    }
    else if((40000 <= charging_mode_precent) && (charging_mode_precent < 50000))
    {
        charge_it_20();
    }
    else if (charging_mode_precent >= 50000)
    {
        Std_ReturnType ret = E_NOT_OK;
        while(button_charging == BUTTON_RELEASED)
        {
            ret = lcd_8bit_send_command(&lcd_1 , _LCD_CLEAR);
        }
        charging_mode_precent = 0;  
    }
}


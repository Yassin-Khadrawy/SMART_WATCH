/*
 * File:   MAIN_MICRO.c
 * Author: Yassin_Khadrawy
 *
 * Created on September 7, 2024, 7:29 PM
 */

/*****************************************************************************/
// section : includes
/*****************************************************************************/

#include "MCAL_layer/mcal_layer_init.h" // Includes the initialization for the Microcontroller Abstraction Layer (MCAL).
#include "ECU_layer/ecu_layer_init.h"   // Includes the initialization for the Electronic Control Unit (ECU) layer.

/*****************************************************************************/
// section : macros declarations
/*****************************************************************************/

#define its_rain_now  1        // Indicates that it is raining.
#define its_not_rain_now 0     // Indicates that it is not raining.

/*****************************************************************************/
// section : variables
/*****************************************************************************/

// Timers for timing control
volatile unit8 timer0_1000ms = 0, timer1_100ms = 0;

// ADC result storage
unit16 adc_res_1 = 0, adc_res_2 = 0, adc_res_3 = 0;

// Processed sensor readings
unit16 final_temp_read = 0;          // Final temperature reading
float final_pressure_read = 0;       // Final pressure reading

// Strings to store ADC results and other data
unit16 adc_res_1_txt[6], adc_res_2_txt[11], GPS_txt[11];
unit16 seconds_txt[4], minutes_txt[4], hours_txt[4];
unit16 mill_seconds_stop_watch_txt[4], seconds_stop_watch_txt[4], minutes_stop_watch_txt[4];

// ADC request flag
unit8 ADC_Req = 0;

// Variables for time tracking
unit8 seconds = 0;
unit8 minutes = 0;
unit8 hours = 0;

// Stopwatch variables
unit8 mill_seconds_stop_watch = 0;
unit8 seconds_stop_watch = 0;
unit8 minutes_stop_watch = 0;

// Flags for resetting functionalities
unit8 clear_watch = 0;
unit8 clear_adjust_the_watch = 0;
unit8 clear_normal_watch = 0;
unit8 clear_GPS = 0;

// Date variables
unit8 days_at_watch = 30;
unit8 months_at_watch = 11;
unit16 years_at_watch = 24;
unit16 days_txt[4], months_txt[4], years_txt[4];

// ADC values, PWM values and charging values
unsigned int adc_value;
unsigned int pwm_duty;
unit16 charging_mode_precent = 0;

// USART variables
unit8 rec_uart_data;               // Received UART data
unit8 counter_gps = 0;             // GPS counter for received data
volatile unit32 valid_tx, valid_rx, valid_overrun, valid_framing; // UART status tracking

// Custom LCD characters for display
const unit8 customChar[] = {
  0x07,
  0x05,
  0x07,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

const unit8 customChar_charge_100[] = {
  0x0E,
  0x0E,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};

const unit8 customChar_charge_80[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};

const unit8 customChar_charge_60[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x1F
};

const unit8 customChar_charge_40[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x1F
};

const unit8 customChar_charge_20[] = {
  0x0E,
  0x0A,
  0x1B,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F
};

/*****************************************************************************/
// section : extern
/*****************************************************************************/

// Externally defined variables used in the application
extern pin_config_t RAIN_D;              // Configuration for the rain sensor pin
extern chr_lcd_8bit_t lcd_1;             // LCD object for displaying data
extern button_t BUTTON_CHARGING;         // Button for charging mode
extern button_t BUTTON_HOURS;            // Button for setting hours
extern button_t BUTTON_MINUTES;          // Button for setting minutes
extern button_t BUTTON_START;            // Button for starting the system
extern timer0_t timer0_timer_obj;        // Timer0 object for time tracking
extern adc_conf_t adc_sensor;            // ADC sensor configuration
extern usart_t usart_obj;                // USART object for communication

/*****************************************************************************/
// section : boolean
/*****************************************************************************/

// Button states for different functionalities
button_state_t button_start = BUTTON_RELEASED;
button_state_t button_min = BUTTON_RELEASED;
button_state_t button_hour = BUTTON_RELEASED;
button_state_t button_charging = BUTTON_RELEASED;
button_state_t button_gps = BUTTON_RELEASED;

// Rain sensor state
logic_t rain_state;

/*****************************************************************************/
// function declarations
/*****************************************************************************/

// Main application and utility functions
void application(void);                   // Main application logic
void buttton_reads(void);                 // Reads the state of all buttons
void ADC_DefaultInterruptHandler(void);   // Default interrupt handler for ADC
void ADC_interrupt_start(void);           // Starts ADC interrupt
void rain_sensor(void);                   // Handles rain sensor readings
void pressure_sensor(void);               // Handles pressure sensor readings
void temperature_sensor(void);            // Handles temperature sensor readings
void LDR_sensor(void);                    // Handles light-dependent resistor sensor readings
void data_at_watch(void);                 // Handles date and time updates
void normal_clock_watch(void);            // Displays normal clock functionality
void adjust_normal_clock(void);           // Allows adjustments to the clock
void charge_it_100(void);                 // Displays 100% charging status
void charge_it_80(void);                  // Displays 80% charging status
void charge_it_60(void);                  // Displays 60% charging status
void charge_it_40(void);                  // Displays 40% charging status
void charge_it_20(void);                  // Displays 20% charging status
void charge_read(void);                   // Reads and processes the charging status

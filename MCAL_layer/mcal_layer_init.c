#include "mcal_layer_init.h"

/**
 * @brief object is used to configure a specific pin for input functionality.
 */
pin_config_t RAIN_D = 
{
    .dirction = INPUT,
    .logic = LOW,
    .pin = pin7,
    .port = PORTD_INDEX
};

/**
 * @brief configures Timer0 for periodic interrupts.
 */
timer0_t timer0_timer_obj = {
    .TIMER0_InterruptHandler = Timer0_DefaultInterruptHandler_1000ms,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer_register_size = TIMER0_8_BIT_MODE,
    .prescaler = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_pteload_value = 3036
};

/**
 * @brief object configures the ADC module for analog-to-digital conversion.
 */
adc_conf_t adc_sensor = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};

/**
 * @brief The usart_obj configures the Enhanced Universal Synchronous Asynchronous Receiver Transmitter (EUSART) module for serial communication.
 */
usart_t usart_obj=
{
    .baudrate = 9600,
    .baudrate_gen_cfg = BAUDRATE_AYSN_8BIT_LOW_SPEED,
    
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable =  EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE,
    
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
    .usart_rx_cfg.usart_rx_9bit_enable =  EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE,
    
    .EUSART_Tx_Default_Interrupt_Handler = NULL,
    .EUSART_Rx_Default_Interrupt_Handler = EUSART_RxDefaultInterruptHandler,
    .EUSART_Overrun_Error_Handler = NULL,
    .EUSART_Framing_Error_Handler = NULL,
};


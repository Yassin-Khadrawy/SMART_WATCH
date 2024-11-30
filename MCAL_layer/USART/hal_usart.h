/* 
 * File:   hal_usart.h
 * Author: Yassin_khadrawy
 *
 * Created on October 29, 2024, 4:58 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

// section : includes

#include "../../MCAL_layer/mcal_std_types.h"
#include <pic18f4620.h>
#include "../../MCAL_layer/interrupts/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"

// macros declarations

/* Enable / Disable EUSART module*/
#define EUSART_MODULE_ENABLE     1
#define EUSART_MODULE_DISABLE    0

/* selecting EUSART working mode*/
#define EUSART_SYNCHRONOUS_MODE             1
#define EUSART_ASYNCHRONOUS_MODE            0
/* baud rate generator asynchronous speed mode*/
#define EUSART_ASYNCHRONOUS_HIGH_SPEED      1
#define EUSART_ASYNCHRONOUS_LOW_SPEED       0
/* baud rate generator register size*/
#define EUSART_16BIT_BAUDRATE_GEN           1   
#define EUSART_08BIT_BAUDRATE_GEN           0 

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE             1
#define EUSART_ASYNCHRONOUS_TX_DISABLE            0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1     
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE        1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE       0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE             1
#define EUSART_ASYNCHRONOUS_RX_DISABLE            0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1     
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE        1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE       0

/* EUSART Framing ERROR */
#define EUSART_FRAMING_ERROR_DETECTED             1
#define EUSART_FRAMING_ERROR_CLEARED              0
/* EUSART OVERRUN ERROR */
#define EUSART_OVERRUN_ERROR_DETECTED             1
#define EUSART_OVERRUN_ERROR_CLEARED              0


// macros functions declarations

/* initialize of the baud rate registers*/
#define EUSART_MODE_SELECT_BIT(USART)  (TXSTAbits.SYNC = USART)
#define EUSART_16_8_BIT_REGISTER_SELECT_BIT(USART)  (BAUDCONbits.BRG16 = USART)
#define EUSART_BAUD_RATE_SPEED_SELECT_BIT(USART)  (TXSTAbits.BRGH = USART)

/* initialize of EUSART registers */
#define EUSART_SERIAL_PORT_EN_DISABLE(USART) (RCSTAbits.SPEN = USART)

/* initialize of transmitter registers */
#define EUSART_TRANMIT_ENABLE_BIT(USART)    (TXSTAbits.TXEN = USART)
#define EUSART_TRANMIT_INTERRUPT_ENABLE_BIT(USART)    (PIE1bits.TXIE = USART)
#define EUSART_TRANMIT_9BIT_ENABLE_BIT(USART)    (TXSTAbits.TX9 = USART)

/* initialize of receiver registers */
#define EUSART_RECEIVER_ENABLE_BIT(USART)    (RCSTAbits.CREN = USART)
#define EUSART_RECEIVER_INTERRUPT_ENABLE_BIT(USART)    (PIE1bits.RCIE = USART)
#define EUSART_RECEIVER_9BIT_ENABLE_BIT(USART)    (RCSTAbits.RX9 = USART)


// data type declarations
typedef enum
{
    BAUDRATE_AYSN_8BIT_LOW_SPEED,
    BAUDRATE_AYSN_8BIT_HIGH_SPEED,
    BAUDRATE_AYSN_16BIT_LOW_SPEED,
    BAUDRATE_AYSN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT,
}baudrate_gen_t;

typedef struct
{
    unit8 usart_tx_reserved : 5;
    unit8 usart_tx_enable : 1;
    unit8 usart_tx_interrupt_enable : 1;
    unit8 usart_tx_9bit_enable : 1;
    interrupt_priority_cfg TX_priority;
}usart_tx_cfg_t;

typedef struct
{
    unit8 usart_rx_reserved : 5;
    unit8 usart_rx_enable : 1;
    unit8 usart_rx_interrupt_enable : 1;
    unit8 usart_rx_9bit_enable : 1;
    interrupt_priority_cfg RX_priority;
}usart_rx_cfg_t;

typedef union
{
    struct
    {
        unit8 usart_tx_reserved : 6;
        unit8 usart_ferr : 1;
        unit8 usart_oerr : 1;
    };
    unit8 status;
}usart_error_status_t;

typedef struct
{
    unit32 baudrate;
    baudrate_gen_t baudrate_gen_cfg;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t usart_error;
    void(*EUSART_Tx_Default_Interrupt_Handler)(void);
    void(*EUSART_Rx_Default_Interrupt_Handler)(void);
    void(*EUSART_Framing_Error_Handler)(void);
    void(*EUSART_Overrun_Error_Handler)(void);  
}usart_t;


// function declarations

Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(const usart_t *_eusart , unit8 *_data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(const usart_t *_eusart , unit8 *_data);
Std_ReturnType EUSART_ASYNC_WriteByteBlocking(const usart_t *_eusart , unit8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(const usart_t *_eusart , unit8 *_data , unit16 strlen);
Std_ReturnType EUSART_ASYNC_WriteByte_NON_Blocking(const usart_t *_eusart , unit8 _data);
Std_ReturnType EUSART_ASYNC_WriteString_NON_Blocking(const usart_t *_eusart , unit8 *_data , unit16 strlen);
Std_ReturnType EUSART_ASYNC_RESTART_RX(void);
Std_ReturnType EUSART_ASYNC_READ_RCREG(void);

#endif /*HAL_USART_H*/
/* 
 * File:   hal_usart.h
 * Author: Yassin_khadrawy
 *
 * Created on October 29, 2024, 4:58 PM
 */
#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        static void (*EUSART_TxInterruptHandler)(void) = NULL;       
#endif
        
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        static void (*EUSART_RxInterruptHandler)(void) = NULL;       
        static void (*EUSART_FramingErrorHandler)(void) = NULL;       
        static void (*EUSART_OverrunErrorHandler)(void) = NULL;       
        
#endif
        

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart)
{
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EUSART_SERIAL_PORT_EN_DISABLE(EUSART_MODULE_DISABLE);
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        EUSART_Baud_Rate_Calculation(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);
        EUSART_SERIAL_PORT_EN_DISABLE(EUSART_MODULE_ENABLE);
    }   
    return ret;
}
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart)
{
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EUSART_SERIAL_PORT_EN_DISABLE(EUSART_MODULE_ENABLE);
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_ReadByteBlocking(const usart_t *_eusart , unit8 *_data)
{
    Std_ReturnType ret = E_NOT_OK;
    while(!PIR1bits.RCIF);
    *_data = RCREG;
    return ret;
}
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(const usart_t *_eusart ,unit8 *_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(1 == PIR1bits.RCIF){
        *_data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_NOT_OK;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteByteBlocking(const usart_t *_eusart , unit8 _data)
{
    Std_ReturnType ret = E_OK;
    if(_eusart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(!TXSTAbits.TRMT);
#if  EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_TX_InterruptEnable();
#endif        
        TXREG = _data;
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteStringBlocking(const usart_t *_eusart, unit8 *_data, unit16 str_len)
{
    Std_ReturnType ret = E_OK;
    if (_eusart == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (unit16 chr_poin = 0; chr_poin < str_len; chr_poin++)
        {
            ret = EUSART_ASYNC_WriteByteBlocking(_eusart, _data[chr_poin]);
        }
    }
    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteByte_NON_Blocking(const usart_t *_eusart, unit8 _data) 
{
    Std_ReturnType ret = E_OK;

    if (_eusart == NULL) {
        ret = E_NOT_OK;
    } else {
        if (TXSTAbits.TRMT == 1) {
            TXREG = _data; 
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();
#endif
        } else {
            ret = E_NOT_OK; 
        }
    }

    return ret;
}
Std_ReturnType EUSART_ASYNC_WriteString_NON_Blocking(const usart_t *_eusart, unit8 *_data, unit16 strlen) 
{
    static uint16_t chr_index = 0; 
    Std_ReturnType ret = E_OK;

    if (_eusart == NULL || _data == NULL) {
        ret = E_NOT_OK;
    } else {
        while (chr_index < strlen) {
            ret = EUSART_ASYNC_WriteByte_NON_Blocking(_eusart, _data[chr_index]);
            if (ret == E_NOT_OK) {
                return E_NOT_OK;
            }
            chr_index++; 
        }
        if (chr_index >= strlen) {
            chr_index = 0; 
        }
    }

    return ret;
}
Std_ReturnType EUSART_ASYNC_RESTART_RX(void)
{
    Std_ReturnType ret = E_OK;
    EUSART_RECEIVER_ENABLE_BIT(EUSART_ASYNCHRONOUS_RX_DISABLE);
    EUSART_RECEIVER_ENABLE_BIT(EUSART_ASYNCHRONOUS_RX_ENABLE);
    return ret;
}
static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart)
{
    float Baud_rate_temp = 0;
    switch(_eusart->baudrate_gen_cfg)
    {
        case BAUDRATE_AYSN_8BIT_LOW_SPEED:
            EUSART_MODE_SELECT_BIT(EUSART_ASYNCHRONOUS_MODE);
            EUSART_BAUD_RATE_SPEED_SELECT_BIT(EUSART_ASYNCHRONOUS_LOW_SPEED);
            EUSART_16_8_BIT_REGISTER_SELECT_BIT(EUSART_08BIT_BAUDRATE_GEN);
            Baud_rate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/64)-1;
            break;
        case BAUDRATE_AYSN_8BIT_HIGH_SPEED:
            EUSART_MODE_SELECT_BIT(EUSART_ASYNCHRONOUS_MODE);
            EUSART_BAUD_RATE_SPEED_SELECT_BIT(EUSART_ASYNCHRONOUS_HIGH_SPEED);
            EUSART_16_8_BIT_REGISTER_SELECT_BIT(EUSART_08BIT_BAUDRATE_GEN);
            Baud_rate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/16)-1;
            break;
        case BAUDRATE_AYSN_16BIT_LOW_SPEED:
            EUSART_MODE_SELECT_BIT(EUSART_ASYNCHRONOUS_MODE);
            EUSART_BAUD_RATE_SPEED_SELECT_BIT(EUSART_ASYNCHRONOUS_LOW_SPEED);
            EUSART_16_8_BIT_REGISTER_SELECT_BIT(EUSART_16BIT_BAUDRATE_GEN);
            Baud_rate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/16)-1;
            break;
        case BAUDRATE_AYSN_16BIT_HIGH_SPEED:
            EUSART_MODE_SELECT_BIT(EUSART_ASYNCHRONOUS_MODE);
            EUSART_BAUD_RATE_SPEED_SELECT_BIT(EUSART_ASYNCHRONOUS_HIGH_SPEED);
            EUSART_16_8_BIT_REGISTER_SELECT_BIT(EUSART_16BIT_BAUDRATE_GEN);
            Baud_rate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/4)-1;
            break;
        case BAUDRATE_SYN_8BIT:
            EUSART_MODE_SELECT_BIT(EUSART_SYNCHRONOUS_MODE);
            EUSART_16_8_BIT_REGISTER_SELECT_BIT(EUSART_08BIT_BAUDRATE_GEN);
            Baud_rate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/4)-1;
            break;
        case BAUDRATE_SYN_16BIT:
            EUSART_MODE_SELECT_BIT(EUSART_SYNCHRONOUS_MODE);
            EUSART_16_8_BIT_REGISTER_SELECT_BIT(EUSART_16BIT_BAUDRATE_GEN);
            Baud_rate_temp = ((_XTAL_FREQ / (float)_eusart->baudrate)/4)-1;
            break;
        default : ;    
    }
    SPBRG  = (unit8)((unit32)Baud_rate_temp);
    SPBRGH = (unit8)(((unit32)Baud_rate_temp) >> 8);
}
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart)
{
    ////////// transmitter enable //////////
    if(_eusart->usart_tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLE)
    {
        EUSART_TRANMIT_ENABLE_BIT(EUSART_ASYNCHRONOUS_TX_ENABLE);
        EUSART_TxInterruptHandler = _eusart->EUSART_Tx_Default_Interrupt_Handler;
        ////////// transmitter interrupt //////////
        if(_eusart->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE)
        {
            EUSART_TRANMIT_INTERRUPT_ENABLE_BIT(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE);
#if  EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_TX_InterruptEnable();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(_eusart->usart_tx_cfg.TX_priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptHighEnable();
            EUSART_TX_HighPrioritySet();
        }
        else if(_eusart->usart_tx_cfg.TX_priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptlowEnable();
            EUSART_TX_LowPrioritySet();
        }
#else
        INTERRUPT_GLOBALInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif    

#endif
        }
        else if(_eusart->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE)
        {
            EUSART_TRANMIT_INTERRUPT_ENABLE_BIT(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE);
        }
        else{/*nothing*/}

        ////////// transmitter 9 bits //////////
        if(_eusart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE)
        {
            EUSART_TRANMIT_9BIT_ENABLE_BIT(EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE);
        }
        else if(_eusart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE)
        {
            EUSART_TRANMIT_9BIT_ENABLE_BIT(EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE);
        }
        else{/*nothing*/}
    }
    else{/*nothing*/} 
}
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart)
{
    if(_eusart->usart_rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLE)
    {
        EUSART_RECEIVER_ENABLE_BIT(EUSART_ASYNCHRONOUS_RX_ENABLE);
        EUSART_RxInterruptHandler = _eusart->EUSART_Rx_Default_Interrupt_Handler;
        EUSART_FramingErrorHandler = _eusart->EUSART_Framing_Error_Handler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_Overrun_Error_Handler;
        ////////// receiver interrupt //////////
        if(_eusart->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE)
        {
            EUSART_RECEIVER_INTERRUPT_ENABLE_BIT(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE);
#if  EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_RX_InterruptEnable();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(_eusart->usart_rx_cfg.RX_priority == INTERRUPT_HIGH_PRIORITY)
            {
                INTERRUPT_GLOBALPriorityInterruptHighEnable();
                EUSART_RX_HighPrioritySet();
            }
            else if(_eusart->usart_rx_cfg.RX_priority == INTERRUPT_LOW_PRIORITY)
            {
                INTERRUPT_GLOBALPriorityInterruptlowEnable();
                EUSART_RX_LowPrioritySet();
            }
#else
            INTERRUPT_GLOBALInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif    

#endif
        }
        else if(_eusart->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE)
        {
            EUSART_RECEIVER_INTERRUPT_ENABLE_BIT(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE);
        }
        else{/*nothing*/}

        ////////// receiver 9 bits //////////
        if(_eusart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE)
        {
            EUSART_RECEIVER_9BIT_ENABLE_BIT(EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE);
        }
        else if(_eusart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE)
        {
            EUSART_RECEIVER_9BIT_ENABLE_BIT(EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE);
        }
        else{/*nothing*/}
    }
    else{/*nothing*/}
}
void EUSART_TX_ISR(void)
{
    EUSART_TX_InterruptDisable();
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }else{/*nothing*/}
}
void EUSART_RX_ISR(void)
{
    
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }else{/*nothing*/}
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }else{/*nothing*/}
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }else{/*nothing*/}
}

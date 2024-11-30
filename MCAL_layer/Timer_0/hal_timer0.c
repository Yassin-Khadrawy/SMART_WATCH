#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        static void (*TMR0_InterruptHandler)(void) = NULL;
        
#endif
        
static unit16 timer0_preload = 0;
static inline void Timer0_prescaler_config(const timer0_t *timer);
static inline void Timer0_size_config(const timer0_t *timer);
static inline void Timer0_mode_config(const timer0_t *timer);



Std_ReturnType Timer0_Read_Value(const timer0_t *timer , unit16 *value)
{
    unit8 l_tmr0L = 0;
    unit8 l_tmr0H = 0;
    Std_ReturnType ret = E_OK;
    if(timer == NULL )
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr0L = TMR0L;
        l_tmr0H = TMR0H;
        *value = ((l_tmr0H << 8) + l_tmr0L);
    }
    return ret;
}
Std_ReturnType Timer0_Init(const timer0_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL )
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER0_MODULE_DISABLE();
        Timer0_prescaler_config(timer);
        Timer0_mode_config(timer);
        Timer0_size_config(timer);
        TMR0H = (timer->prescaler_value) >> 8;
        TMR0L = (unit8)(timer->prescaler_value);
        timer0_preload = (timer->timer0_pteload_value);
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = timer->TIMER0_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(timer->priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(timer->priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptlowEnable();
            TIMER0_LowPrioritySet();
        }
#else
        INTERRUPT_GLOBALInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable(); 
#endif
#endif
        TIMER0_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer0_DeInit(const timer0_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL )
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER0_MODULE_DISABLE();
    }
    return ret;
}
Std_ReturnType Timer0_Write_Value(const timer0_t *timer , unit16 value)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL )
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR0H = (value >> 8);
        TMR0L = (unit8)(value);
    }
    return ret;
}
void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload)>> 8;
    TMR0L = (unit8)(timer0_preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}

static inline void Timer0_prescaler_config(const timer0_t *timer)
{
    if(timer->prescaler == TIMER0_PRESCALER_ENABLE_CFG)
    {
        TIMER0_PRESCALER_ENABLE();    
        T0CONbits.T0PS = timer->prescaler_value;
    }
    else if(timer->prescaler == TIMER0_PRESCALER_DISABLE_CFG)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else
    {
        /*nothing*/
    }
}

static inline void Timer0_size_config(const timer0_t *timer)
{
    if(timer->timer_register_size == TIMER0_8_BIT_MODE)
    {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();    
    }
    else if(timer->timer_register_size == TIMER0_16_BIT_MODE)
    {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
    else
    {
        /*nothing*/
    }
}
static inline void Timer0_mode_config(const timer0_t *timer)
{
    if(timer->timer0_mode == TIMER0_TIMER_MODE)
    {
        TIMER0_TIMER_MODE_ENABLE();    
    }
    else if(timer->timer0_mode == TIMER0_COUNTER_MODE)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if(timer->edge == TIMER0_RISING_EDGE_CFG)
        {
            TIMER0_RISING_EDGE_ENABLE();    
        }
        else if(timer->edge == TIMER0_FALLING_EDGE_CFG)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else
        {
            /*nothing*/
        }
    }
    else
    {
        /*nothing*/
    }
}

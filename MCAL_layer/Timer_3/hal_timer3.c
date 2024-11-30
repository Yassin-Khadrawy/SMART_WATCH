#include "hal_timer3.h"
static void(*TIMER3_INTERRUPT_HANDLER)(void) = NULL;
static volatile unit16 preload_value = 0;
static inline void timer3_mode_select(const timer3_t *timer);

Std_ReturnType Timer3_Init(const timer3_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALAR_SELECT(timer->prescaler_enum);
        timer3_mode_select(timer);
        TMR3H = (timer->timer3_preload_value)>>8;
        TMR3L = timer->timer3_preload_value;
        preload_value = timer->timer3_preload_value;
#if  TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TIMER3_INTERRUPT_HANDLER = timer->timer3_inturrpt_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(timer->priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if(timer->priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptlowEnable();
            TIMER3_LowPrioritySet();
        }
#else
        INTERRUPT_GLOBALInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer3_DeInit(const timer3_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER3_MODULE_DISABLE();
#if  TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        
        TIMER3_InterruptDisable();
        
#endif
    }
    return ret;
}
Std_ReturnType Timer3_Write_Value(const timer3_t *timer , unit16 value)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (value >> 8);
        TMR3L = (unit8)(value);
    }
    return ret;
}
Std_ReturnType Timer3_Read_Value(const timer3_t *timer , unit16 *value)
{
    unit8 tmr3H = 0;
    unit8 tmr3L = 0;
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        tmr3H = TMR3H;
        tmr3L = TMR3L;
        *value = (unit16)((tmr3H << 8) + tmr3L);
    }
    return ret;
}

static inline void timer3_mode_select(const timer3_t *timer)
{
    switch(timer->timer3_mode)
    {
        case TIMER3_TIMER_MODE_ENABLE:
            TIMER3_TIMER_MODE();
            break;
        case TIMER3_COUNTER_MODE_ENABLE:
            TIMER3_COUNTER_MODE();
            break;  
        default:
            break;
    }
}

void TMR3_ISR(void)
{
    TIMER3_InterruptFlagClear();
    TMR3H = preload_value >> 8;
    TMR3L = preload_value;
    if(TIMER3_INTERRUPT_HANDLER)
    {
        TIMER3_INTERRUPT_HANDLER();
    }
}

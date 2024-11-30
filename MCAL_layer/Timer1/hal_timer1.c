#include "hal_timer1.h"


static inline void timer1_mode_select(const timer1_t *timer);
static inline void timer1_osc_enable_disable(const timer1_t *timer);
static volatile unit16 timer_preload = 0;
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        static void (*TMR1_InterruptHandler)(void) = NULL;
        
#endif

Std_ReturnType Timer1_Init(const timer1_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
        
        TIMER1_PRESCALAR_SELECT(timer->prescalaer_value);
        timer1_mode_select(timer);
        TMR1H = (timer->timer1_preload_value)>>8;
        TMR1L = (unit8)(timer->timer1_preload_value);
        timer_preload = timer->timer1_preload_value;
        //////////////////////////////////////////////
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptEnable();
        TIMER1_InterruptFlagClear();
        TMR1_InterruptHandler = timer->timer1_interrupt_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(timer->priority== INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptHighEnable();
            TIMER1_HighPrioritySet();
        }
        else if(timer->priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptlowEnable();
            TIMER1_LowPrioritySet();
        }
#else
        INTERRUPT_GLOBALInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable(); 

#endif
#endif
        ////////////////////////////////////////////
        TIMER1_MODULE_ENABLE();

    }
}
Std_ReturnType Timer1_DeInit(const timer1_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptDisable();
#endif
    }
    return ret;
}
Std_ReturnType Timer1_Write_Value(const timer1_t *timer , unit16 value)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (value)>>8;
        TMR1L = (unit8)(value);
    }
    return ret;
}
Std_ReturnType Timer1_Read_Value(const timer1_t *timer , unit16 *value)
{
    Std_ReturnType ret = E_OK;
    unit8 tmr1H = 0;
    unit8 tmr1L = 0;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        tmr1H = TMR1H;
        tmr1L = TMR1L;
        *value = (unit16)(( tmr1H << 8) + tmr1L);
    }
    return ret;
}
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////

static inline void timer1_mode_select(const timer1_t *timer)
{
    switch(timer->timer1_timer_counter)
    {
        case TIMER1_COUNTER_MODE:
            TIMER1_COUNTER_MODE_ENABLE();
            break;
        case TIMER1_TIMER_MODE:
            TIMER1_TIMER_MODE_ENABLE();
            if(timer->timer1_syncro_non_syncro == TIMER1_SYNCHRONIZE)
            {
                TIMER1_SYNCHRONIZE_EXTERNAL();
            }
            else if(timer->timer1_syncro_non_syncro == TIMER1_NON_SYNCHRONIZE)
            {
                TIMER1_NON_SYNCHRONIZE_EXTERNAL();
            }
            break;
        default:break;    
    }
}
static inline void timer1_osc_enable_disable(const timer1_t *timer)
{
    switch(timer->timer1_oscillator_mode)
    {
        case TIMER1_OSC_ENABLE:
            TIMER1_OSCILLATOR_ENABLE();
            break;
        case TIMER1_OSC_DISABLE:
            TIMER1_OSCILLATOR_DISABLE();
            break;
        default:break;    
    }
}

void TMR1_ISR(void)
{
    TIMER1_InterruptFlagClear();
    TMR1H = (timer_preload) >> 8;
    TMR1L = (unit8)(timer_preload);
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
}
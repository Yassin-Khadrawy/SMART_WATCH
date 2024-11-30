#include "hal_timer2.h"
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        static void (*TMR2_InterruptHandler)(void) = NULL;
        
#endif
static volatile unit8 preload_timer2 = 0;
Std_ReturnType Timer2_Init(const timer2_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIEMR2_MODULE_DISABLE();
        TIMER2_PRESCALAR_SELECT(timer->prescaler_enum);
        TIMER2_POSTSCALAR_SELECT(timer->postscaler_enum);
        TMR2 = timer->timer1_preload_value;
        preload_timer2 = TMR2;
        
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TMR2_InterruptHandler = timer->timer2_interrupt_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        
        INTERRUPT_PriorityLevelEnable();
        if(timer->priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if(timer->priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptlowEnable();
            TIMER2_LowPrioritySet();
        }
        else{/*nothing*/}
#else
        
        INTERRUPT_GLOBALInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        
#endif     
#endif
        
        TIEMR2_MODULE_ENABLE();
        
    }
    return ret;
}
        
Std_ReturnType Timer2_DeInit(const timer2_t *timer)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIEMR2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
#endif 
    }
    return ret;
}


Std_ReturnType Timer2_Write_Value(const timer2_t *timer , unit16 value)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR2 = value;
    }
    return ret;
}

Std_ReturnType Timer2_Read_Value(const timer2_t *timer , unit16 *value)
{
    Std_ReturnType ret = E_OK;
    if(timer == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *value = TMR2;
    }
    return ret;
}


void TMR2_ISR(void)
{
    TIMER2_InterruptFlagClear();
    TMR2 = preload_timer2;
    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
    
}


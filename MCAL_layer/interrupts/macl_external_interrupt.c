#include "mcal_external_interrupt.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////

static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW = NULL;
static InterruptHandler RB5_InterruptHandler_LOW = NULL;
static InterruptHandler RB6_InterruptHandler_LOW = NULL;
static InterruptHandler RB7_InterruptHandler_LOW = NULL;

static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);


static Std_ReturnType INT0_SetInterruptHandler (void (*INT0_InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler (void (*INT1_InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler (void (*INT2_InterruptHandler)(void));
static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Std_ReturnType interrupt_INTx_init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Disable the external interrupt       */
        ret = interrupt_INTx_Disable(int_obj);
        /*Clear interrupt flag : external interrupt did not occur*/
        ret |= interrupt_INTx_Clear_Flag(int_obj);
        /*configure external interrupt edge    */
        ret |= interrupt_INTx_Edge_Init(int_obj);
        /*configure external interrupt I/O pin */
        ret |= interrupt_INTx_Pin_Init(int_obj);
        /*configure external interrupt CallBack*/
        ret |= interrupt_INTx_SetInterruptHandler(int_obj);
        /*Enable the external interrupt        */
        ret |= interrupt_INTx_Enable(int_obj);
    }
    return ret;
}
///////////////////////////////////////////////////////////////////////
void INT0_ISR(void)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_INT0_InterruptsFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
    else{/*nothing*/}
}

void INT1_ISR(void)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_INT1_InterruptsFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
    else{/*nothing*/}
}

void INT2_ISR(void)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_INT2_InterruptsFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
    else{/*nothing*/}
}
///////////////////////////////////////////////////////////////////////

void RB4_ISR(unit8 RBx_source)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_RBx_InterruptFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(RBx_source == 1)
    {
        if(RB4_InterruptHandler_HIGH)
        {
            RB4_InterruptHandler_HIGH();
        }
        else{/*nothing*/}
    }
    else if(RBx_source == 0)
    {
        if(RB4_InterruptHandler_LOW)
        {
            RB4_InterruptHandler_LOW();
        }
        else{/*nothing*/}
    }
    else{/*nothing*/}
}

void RB5_ISR(unit8 RBx_source)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_RBx_InterruptFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(RBx_source == 1)
    {
        if(RB5_InterruptHandler_HIGH)
        {
            RB5_InterruptHandler_HIGH();
        }
        else{/*nothing*/}
    }
    else if(RBx_source == 0)
    {
        if(RB5_InterruptHandler_LOW)
        {
            RB5_InterruptHandler_LOW();
        }
        else{/*nothing*/}
    }
    else{/*nothing*/}
}

void RB6_ISR(unit8 RBx_source)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_RBx_InterruptFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(RBx_source == 1)
    {
        if(RB6_InterruptHandler_HIGH )
        {
            RB6_InterruptHandler_HIGH();
        }
        else{/*nothing*/}
    }
    else if(RBx_source == 0)
    {
        if(RB6_InterruptHandler_LOW)
        {
            RB6_InterruptHandler_LOW();
        }
        else{/*nothing*/}
    }
    else{/*nothing*/}
}

void RB7_ISR(unit8 RBx_source)
{
    /*Clear interrupt flag : external interrupt did not occur*/
    EXT_RBx_InterruptFlagClear();
    /*code*/

    /*callback function gets called every time this ISR executes*/
    if(RBx_source == 1)
    {
        if(RB7_InterruptHandler_HIGH)
        {
            RB7_InterruptHandler_HIGH();
        }
        else{/*nothing*/}
    }
    else if(RBx_source == 0)
    {
        if(RB7_InterruptHandler_LOW)
        {
            RB7_InterruptHandler_LOW();
        }
        else{/*nothing*/}
    }
    else{/*nothing*/}
}
///////////////////////////////////////////////////////////////////////
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Disable the external interrupt       */
        EXT_RBx_InterruptDisable();
        /*Clear interrupt flag : external interrupt did not occur*/
        EXT_RBx_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(int_obj->prio == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptlowEnable();
            EXT_RBx_LowPrioritySet();
        }
        else if(int_obj->prio == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GLOBALPriorityInterruptHighEnable();
            EXT_RBx_HighPrioritySet();
        }
        else{/*nothing*/}
    
#else       
        INTERRUPT_GLOBALInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif  
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
        switch(int_obj->mcu_pin.pin)
        {
            case pin4:
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case pin5:
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case pin6:
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case pin7:
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;  
            default:
                ret = E_NOT_OK;
        }
        EXT_RBx_InterruptEnable();
        ret = E_OK;
        
    }
    return ret;
}
Std_ReturnType interrupt_INTx_Deinit(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /*Disable the external interrupt       */
        EXT_RBx_InterruptDisable();
        /*Clear interrupt flag : external interrupt did not occur*/
        EXT_RBx_InterruptFlagClear();
    }
    return ret;
}
static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->sorc)
        {
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GLOBALPriorityInterruptHighEnable();
#else       
                INTERRUPT_GLOBALInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif          
                EXT_INT0_InterruptsEnable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(int_obj->prio == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GLOBALPriorityInterruptlowEnable();
                }
                else if(int_obj->prio == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOBALPriorityInterruptHighEnable();
                }
                else{/*nothing*/}
    
#else       
                INTERRUPT_GLOBALInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif          
                EXT_INT1_InterruptsEnable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(int_obj->prio == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GLOBALPriorityInterruptlowEnable();
                }
                else if(int_obj->prio == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GLOBALPriorityInterruptHighEnable();
                }
                else{/*nothing*/}
    
#else       
                INTERRUPT_GLOBALInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif          
                EXT_INT2_InterruptsEnable();
                break;
            default: 
                ret = E_NOT_OK; 
                break;    
        }
    }
    return ret;
}
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->sorc)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptsDisable();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptsDisable();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptsDisable();
                break;  
            default: ret = E_NOT_OK;    
        }
    }
    return ret;
}
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->sorc)
        {
            case INTERRUPT_EXTERNAL_INT1:
                if(int_obj->prio == INTERRUPT_LOW_PRIORITY)
                {
                    EXT_INT1_LowPrioritySet();
                }
                else if(int_obj->prio == INTERRUPT_HIGH_PRIORITY)
                {
                    EXT_INT1_HighPrioritySet();
                }
                else{/*nothing*/}
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(int_obj->prio == INTERRUPT_LOW_PRIORITY)
                {
                    EXT_INT2_LowPrioritySet();
                }
                else if(int_obj->prio == INTERRUPT_HIGH_PRIORITY)
                {
                    EXT_INT2_HighPrioritySet();
                }
                else{/*nothing*/}
            
                break;  
            default: ret = E_NOT_OK;  
        }    
    }
    return ret;
}
#endif
static Std_ReturnType interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->sorc)
        {
            case INTERRUPT_EXTERNAL_INT0:
                if(int_obj->edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT0_FallingEdgeSet();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT0_RisingEdgeSet();  
                }
                else{/*nothing*/};
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if(int_obj->edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT1_FallingEdgeSet();
                }
                else if(int_obj->edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT1_RisingEdgeSet();  
                }
                else{/*nothing*/};
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if(int_obj->edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT2_FallingEdgeSet();
                }
                else if(int_obj->edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT2_RisingEdgeSet();  
                }
                else{/*nothing*/};
                break;  
            default: ret = E_NOT_OK;    
        }
    }
    return ret;
}
static Std_ReturnType interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}


static Std_ReturnType interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->sorc)
        {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptsFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptsFlagClear();
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptsFlagClear();
                break;  
            default: ret = E_NOT_OK;    
        }
    }
    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler (void (*InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(InterruptHandler == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType INT1_SetInterruptHandler (void (*InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(InterruptHandler == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType INT2_SetInterruptHandler (void (*InterruptHandler)(void))
{
    Std_ReturnType ret = E_OK;
    if(InterruptHandler == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
    
}
static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(int_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(int_obj->sorc)
        {
            case INTERRUPT_EXTERNAL_INT0:
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT2:
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;  
            default: ret = E_NOT_OK;    
        }
    }
    return ret;
}

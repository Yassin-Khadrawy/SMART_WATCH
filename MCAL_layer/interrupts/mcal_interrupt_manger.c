#include "mcal_interrupt_manger.h"
static volatile unit8 RB4_Flag = 1;
static volatile unit8 RB5_Flag = 1;
static volatile unit8 RB6_Flag = 1;
static volatile unit8 RB7_Flag = 1;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptMangerHigh(void)
{
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR))
    {
        INT2_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR))
    {
        INT0_ISR();
    }
    else
    {
        /*NOTHING*/
    }    
}
void __interrupt(low_priority) InterruptMangerLOW(void)
{
    
    if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1F == INTERRUPT_OCCUR))
    {
        INT1_ISR();
    }
    else
    {
        /*NOTHING*/
    }
}

#else

void __interrupt() InterruptManger(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR))
    {
        INT0_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1F == INTERRUPT_OCCUR))
    {
        INT1_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR))
    {
        INT2_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR))
    {
        ADC_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_OCCUR))
    {
        TMR0_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR))
    {
        TMR1_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == INTERRUPT_OCCUR))
    {
        TMR2_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == INTERRUPT_OCCUR))
    {
        TMR3_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == INTERRUPT_OCCUR))
    {
        EUSART_TX_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == INTERRUPT_OCCUR))
    {
        EUSART_RX_ISR();
    }
    else
    {
        /*NOTHING*/
    }
    
    ////////////////////////////////////////////////////////
    /******************************************************/
    ////////////////////////////////////////////////////////
    
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB4 == HIGH) && (RB4_Flag == 1))
    {
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB4 == LOW) && (RB4_Flag == 0))
    {
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else
    {
        /*NOTHING*/
    }
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB5 == HIGH) && (RB5_Flag == 1))
    {
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB5 == LOW) && (RB5_Flag == 0))
    {
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else
    {
        /*NOTHING*/
    }
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB6 == HIGH) && (RB6_Flag == 1))
    {
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB6 == LOW) && (RB6_Flag == 0))
    {
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else
    {
        /*NOTHING*/
    }
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB7 == HIGH) && (RB7_Flag == 1))
    {
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else
    {
        /*NOTHING*/
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR)
            &&(PORTBbits.RB7 == LOW) && (RB7_Flag == 0))
    {
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else
    {
        /*NOTHING*/
    }
}


#endif
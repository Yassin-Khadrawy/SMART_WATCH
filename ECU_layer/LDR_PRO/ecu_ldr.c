#include "ecu_ldr.h"


void PWM_Init() {
    PWM_SET_PIN_CCP1_OUTPUT();             // Set CCP1 (RC2) as output
    PWM_SET_PWM_PERIOD_FREQ(0xFF) ;             // Set PWM period (frequency)
    PWM_CCP1_TO_PWM_MODE(0x0C) ;         // Set CCP1 to PWM mode
    TIMER2_PRESCALER_ON(0x04) ;           // Timer2 ON, prescaler 1:1
}

void PWM_SetDuty(unsigned int duty) {
    if(duty < 1024) {
        PWM_SET_MSBs(duty >> 2);            // Set the 8 MSBs to CCPR1L
        PWM_SET_LSBs(duty & 0x03); // Set the 2 LSBs to CCP1CON
    }
}



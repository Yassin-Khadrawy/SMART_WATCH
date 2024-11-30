/* 
 * File:   hal_eeprom.c
 * Author: Yassin_Khadrawy
 *
 * Created on October 15, 2024, 10:21 AM
 */
#include "hal_eeprom.h"

/////////////////////////////////////////////////////////
/*******************************************************/
/////////////////////////////////////////////////////////
Std_ReturnType Data_EEPROM_WriteByte(unit16 bAdd , unit8 bData)
{
    Std_ReturnType ret = E_OK;
    /* read the interrupt status "enable or disable" */
    unit8 Global_Interrupt_Status = INTCONbits.GIE;
    /* update the address registers */
    EEADRH = (unit8)((bAdd >> 8) & 0x03);
    EEADR  = (unit8)( bAdd & 0xFF);
    /* update the data register */
    EEDATA = bData;
    /* select access data EEPROM memory */
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    /* allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN  = 1;
    /* disable all interrupts "General interrupt */ 
    #if INTERRUPT_PRIORITY_LEVEL_ENABLE != INTERRUPT_FEATURE_ENABLE
    INTERRUPT_GLOBALInterruptDisable();
    #endif
    /* write at EECON2 the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* initiates a data EEPTROM erase/write cycle */
    EECON1bits.WR = 1;
    /* wait for write to complete */
    while(EECON1bits.WR);
    /* inhibits write cycles to flash program/data EEPROM */
    EECON1bits.WREN  = 0;
    /* Restore the Interrupt Status "enable or disable" */
    INTCONbits.GIE = Global_Interrupt_Status;

    return ret ;
}

/////////////////////////////////////////////////////////
/*******************************************************/
/////////////////////////////////////////////////////////
Std_ReturnType Data_EEPROM_ReadByte(unit16 bAdd , unit8 *bData)
{
    Std_ReturnType ret = E_OK;
    if(bAdd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* update the address register */
        EEADRH = (unit8)((bAdd >> 8) & 0x03);
        EEADR  = (unit8)( bAdd & 0xFF);
        /* select access data EEPROM memory */
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS  = 0;
        /* initiates a data EEPRROM memory*/
        EECON1bits.RD = 1;
        NOP();
        NOP();
        /* return data*/
        *bData = EEDATA;
    }
    return ret ;
}

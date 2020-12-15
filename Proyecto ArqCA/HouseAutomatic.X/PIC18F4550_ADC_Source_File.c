/*!
\file   PIC18F4550_ADC_Source_File.c
\date   2020-11-23
\author Kevin Alarcon <kfalarcon@unicauca.edu.co>
\brief  Example PIC18F4550_ADC_Source_File.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2020. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/
#include "PIC18F4550_ADC_Header_File.h"

void ADC_Init()
{
    TRISA = 0xff;       /*set as input port*/
    ADCON0 = 0x85;
    ADCON1 = 0xC0;      /*ref vtg is VDD and Configure pin as analog pin*/    
    ADCON2 = 0x92;      /*Right Justified, 4Tad and Fosc/32. */
    ADRESH = 0;           /*Flush ADC output Register*/
    ADRESL = 0;   
}

int ADC_Read(int channel)
{
    int digital;
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);      /*channel is selected i.e (CHS3:CHS0) 
                                                                      and ADC is disabled i.e ADON=0*/
    ADCON0 |= ((1<<ADON)|(1<<GO));                   /*Enable ADC and start conversion*/
    while(ADCON0bits.GO_nDONE==1);                  /*wait for End of conversion i.e. Go/done'=0 conversion completed*/        
    digital = (ADRESH*256) | (ADRESL);              /*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}




/*
    Analog Joystick Interfacing with PIC18f4550
    http://www.electronicwings.com
 
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <p18f4550.h>
#include "Configuration_Header_File.h"          /* Header File for Configuration bits */
#include "LCD_16x2_8-bit_Header_File.h"                 /* Header File for LCD Functions */
#include "PIC18F4550_ADC_Header_File.h"

void main()
{    
    char data[10],data1[10];    
    int x,y;  
    OSCCON=0x72;                /* set internal Oscillator frequency to 8 MHz*/
    LCD_Init();                 /* initialize 16x2 LCD*/
    ADC_Init();                 /* initialize 10-bit ADC*/

    while(1)
    {        
        x = 1024 - ADC_Read(0);        
        sprintf(data,"X=%d  ",x);               /* it is used to convert integer value to ASCII string */
        LCD_String_xy(0,0,data);                /* send string data for printing */
        MSdelay(50);
        
        y=ADC_Read(1);
        sprintf(data1,"Y=%d  ",y);              /* It is used to convert integer value to ASCII string */
        LCD_String_xy(0,7,data1);               /* send string data for printing */          

        if(x>494)
            LCD_String_xy(1,2,"X=R");           /* Joystick X-direction is Right */
        else if(x<491)
            LCD_String_xy(1,2,"X=L");           /* Joystick X-direction is Left */
        else
            LCD_String_xy(1,2,"X=C");           /* Joystick X-direction is Centre */
        
        if(y>533)
            LCD_String_xy(1,6,"Y=U");           /* Joystick Y-direction is Right */
        else if(y<530)
            LCD_String_xy(1,6,"Y=D");           /* Joystick Y-direction is Left */
        else
            LCD_String_xy(1,6,"Y=C");           /* Joystick Y-direction is Centre */
        MSdelay(100);
        memset(data,0,10);
        memset(data1,0,10);
    }
    
}

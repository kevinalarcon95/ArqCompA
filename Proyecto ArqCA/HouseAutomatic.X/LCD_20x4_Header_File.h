/* 
   Header File For PIC18F4550 LCD 
   Autor Kevin Alarcón <kfalarcon@unicauca.edu.co>
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>

//DEFINE LA FRECUENCIA DEL CRYSTAL
#define _XTAL_FREQ 8000000

//DECLARACION PUERTOS LCD
#define LCD_Data_Dir TRISD				
#define LCD_Command_Dir TRISE			
#define LCD_Data_Port LATD				
#define LCD_Command_Port LATE			
#define EN LATE2							
#define RS LATE1	
 //DECLARACION SENSOR DE LUZ
#define LED PORTEbits.RE0              
//DECLARACION SENSOR 1 (PIR)
#define MD_Pir1 PORTAbits.RA2            
#define PORT_Dir TRISAbits.RA2            
#define LED2 LATC0                         
#define LED_Dir TRISCbits.RC0             
//DECLARACION SENSOR 2 (PIR)
#define MD_Pir2 PORTAbits.RA3
#define PORT_Dir2 TRISAbits.RA3
#define LED3 LATC1
#define LED_Dir2 TRISCbits.RC1
//DECLARACION SENSOR 3 (PIR)
#define MD_Pir3 PORTAbits.RA4
#define PORT_Dir3 TRISAbits.RA4
#define LED4 LATC2
#define LED_Dir3 TRISCbits.RC2
//DECLARACION LED'S CALEFACCION
#define LED5 LATB2
#define LED_TEMP1 TRISBbits.RB2 
#define LED6 LATB3
#define LED_TEMP2 TRISBbits.RB3

//PROCEDIMIENTOS NECESARIOS PARA LCD
void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void MSdelay(unsigned int );
void LCD_String_xy(char ,char ,const char*);
void LCD_Custom_Char(unsigned char loc,unsigned char *msg);
void LCD_Clear(); 

#endif	/* XC_HEADER_TEMPLATE_H */


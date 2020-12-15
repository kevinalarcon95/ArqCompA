/*!
\file   LCD_20x4.c
\date   2020-11-23
\author Kevin Alarcon <kfalarcon@unicauca.edu.co>
\brief  Example LCD 20x4.

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
#include<xc.h>
#include "LCD_20x4_Header_File.h"

/****************************Functions********************************/

/*
 Inicializa el LCD
 */
void LCD_Init()
{
   	LCD_Command_Dir = 0;                        /* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0x00;							/* Make LCD data port direction as o/p */
	
	MSdelay(20);
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    LCD_Command(0x01);     /*clear display screen*/
    LCD_Command(0x0c);     /*display on cursor off*/
    LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
								/* Clear LCD command */
//	MSdelay(3);
//	LCD_Command (0x80);
}

void LCD_Clear()
{
    LCD_Command(0x01);
    MSdelay(3);
}

void LCD_Command(char cmd )
{
	LCD_Data_Port = cmd;							/* Write command data to LCD data port */
	RS = 0;                                			/* Make RS LOW (command reg.), RW LOW (Write) */
	//RW = 0;
    EN = 1;					/* High to Low transition on EN (Enable) */
	NOP();
	EN = 0;
	MSdelay(3);	
}

void LCD_Char(char char_data)
{
	LCD_Data_Port = char_data;						/* Write data to LCD data port */
	RS = 1;                                			/* Make RS LOW (command reg.), RW LOW (Write) */
	//RW = 0;
    EN = 1;					/* High to Low transition on EN (Enable) */
	NOP();
	EN = 0;
	MSdelay(3);
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
		
}

void LCD_String_xy(char row,char pos,const char *str)
{
    if (row == 1)
		LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
		LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	else if (row == 3)
		LCD_Command((pos & 0x0F)|0x94);				/* Command of Third row and required position<16 */
	else if (row == 4)
		LCD_Command((pos & 0x0F)|0xD4);				/* Command of Fourth row and required position<16 */
	LCD_String(str);
}

void LCD_Custom_Char(unsigned char loc,unsigned char *msg)
{
    unsigned char i;
    if(loc<8)
    {
     LCD_Command(0x40+(loc*8));     /* Command 0x40 and onwards forces the device to point CGRAM address */
       for(i=0;i<8;i++)             /* Write 8 byte for generation of 1 character */
           LCD_Char(msg[i]);
        
    }   
}

/*********************************Delay Function********************************/
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }

/*
 Controlador para los dispositivos:
 *      Sensor de Temperatura
 *      Sensor de Luz
 *      Sensor de Proximidad
 *      RTC
 *      LCD 20X4
 Se utiliza el Microcontrolador PIC 18F4550
 */

/*!
\file   Controler.c
\date   2020-12-11
\author Kevin Alarcón <kfalarcon@unicauca.edu.co>
\brief  Example Controler .

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Configuration_Header_File.h" 
#include "LCD_20x4_Header_File.h" 
#include "PIC18F4550_ADC_Header_File.h"
#include "I2C_Master_File_3.h"

#define device_id_write 0xD0
#define device_id_read 0xD1

//Declaración de Procedimientos 
void SensorTemperatura();
void SensorLuz();
void SensorMovimiento();
void RTC_Read_Clock(char);
void RTC();

//Declaración de variables para el RTC
int sec, min, hour;
char secs[10], mins[10], hours[10];

//Declaracion de caracteres especiales
unsigned char character1[8] = {0x00, 0x00, 0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04}; //Flecha arriba
unsigned char character2[8] = {0x00, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00}; //Flecha abajo

//Main
void main() {

    OSCCON = 0x72;
    I2C_Init();
    LCD_Init();
    ADC_Init();
    ADCON1 = 0x0F;

    //Configura UART a 9600 baudios
    TRISCbits.RC6 = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 0;
    BAUDCONbits.BRG16 = 0;
    RCSTAbits.SPEN = 1;
    SPBRG = (unsigned char) (((_XTAL_FREQ / 9600) / 64) - 1); //baudios  = 9600

    while (1) {
        //Llamado de los procedimientos
        RTC();
        SensorTemperatura();
        SensorMovimiento();
        SensorLuz();
    }
}

/*
 * Procedimiento que permite obtener la temperatura
 * y lo muestra en una pantalla lCD de 20x4.
 * 
 * Segun un rango de temperatura, se activa la calefacción
 */
void SensorTemperatura() {
    char Temperature[10];
    float celsius;
    LED_TEMP1 = 0;
    LED_TEMP2 = 0;

    LCD_String_xy(2, 0, "Temp: ");
    celsius = (ADC_Read(0)*4.88);
    celsius = (celsius / 10.00);
    sprintf(Temperature, "%d%cC ", (int) celsius, 0xdf);
    LCD_String_xy(2, 6, Temperature); 

    
    memset(Temperature, 0, 10);

    if (celsius >= 20 && celsius <= 25) {
        LED5 = 1;
        LED6 = 0;
        
        LCD_String_xy(2,13,"Cal: ");
        LCD_Custom_Char(0,character1);
        LCD_Command(0xc0|(17));
        LCD_Char(0);
        
        char buffer_TX1[] = "Calefaccion encendida\r";
        for (int i = 0; i < 25; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX1[i];
        }
        MSdelay(1000);
    } else {
        LED5 = 0;
        LED6 = 1;
        
        LCD_String_xy(2,13,"Cal: ");
        LCD_Custom_Char(0,character2);
        LCD_Command(0xc0|(17));
        LCD_Char(0);
        
        char buffer_TX2[] = "Calefaccion apagada\r";
        for (int i = 0; i < 21; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX2[i];
        }
        MSdelay(1000);
    }
}

/*
 * Procedimiento que segun un voltaje
 * sube una cortina simulada con un led
 * y muestra el resultado en un LCD.
 */
void SensorLuz() {
    
    float val;
    LCD_Command(0x40);
    val = (ADC_Read(1)*5.0) / 1023.0;

    if (val > 3) {

        LCD_String_xy(4, 0, "Cortina Arriba       ");
        LED = 1;
        char buffer_TX3[] = "Cortina arriba\r";
        for (int i = 0; i < 15; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX3[i];
        }
        MSdelay(1000);

    } else {
        LCD_String_xy(4, 0, "Cortina Abajo        ");
        LED = 0;
        char buffer_TX4[] = "Cortina abajo\r";
        for (int i = 0; i < 15; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX4[i];
        }
        MSdelay(1000);
    }
}

/*
 * Procedimiento que enciende automaticamende
 * los led  si hay presencia, en caso de que no
 * los apaga
 */
void SensorMovimiento() {
    ADCON1    = 0x0F; 
    PORT_Dir  = 1; 
    PORT_Dir2 = 1;
    PORT_Dir3 = 1;
    LED_Dir   = 0; 
    LED_Dir2  = 0;
    LED_Dir3  = 0;
    char buf[20] = "0";
    
    if (MD_Pir1) {
        LED2 = 1;
        strcpy(buf,"1:ON  ");
        //LCD_String_xy(3, 0, "1:ON ");
        char buffer_TX5[] = "Presencia en la H1\r";
        for (int i = 0; i < 20; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX5[i];
        }

    } else {
        LED2 = 0;
        strcpy(buf,"1:OFF ");
        //LCD_String_xy(3, 0, "1:OFF ");
    }

    if (MD_Pir2) {
        LED3 = 1;
        strcat(buf,"2:ON  ");
        //LCD_String_xy(3, 7, "2:ON ");
        char buffer_TX6[] = "Presencia en la H2\r";
        for (int i = 0; i < 20; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX6[i];
        }

    } else {
        LED3 = 0;
        strcat(buf,"2:OFF ");
        //LCD_String_xy(3, 7, "2:OFF");
    }

    if (MD_Pir3) {
        LED4 = 1;
        strcat(buf,"3:ON  ");
        //LCD_String_xy(3,13, "3:ON ");
        char buffer_TX7[] = "Presencia en la H3\r";
        for (int i = 0; i < 20; i++) {
            while (!TXSTAbits.TRMT) {
            }
            TXREG = buffer_TX7[i];
        }
    } else {
        LED4 = 0;
        strcat(buf,"3:OFF ");
        //LCD_String_xy(3,13, "3:OFF");
    }
    LCD_String_xy(3,0,buf);
}

void RTC_Read_Clock(char read_clock_address) {
    I2C_Start(device_id_write);
    I2C_Write(read_clock_address);
    I2C_Repeated_Start(device_id_read);
    sec = I2C_Read(0); 
    min = I2C_Read(0); 
    hour = I2C_Read(1); 
}

/*
 *  Procedimiento que muestra la hora  en la pantalla LCD
 *  en formato 24H
 */
void RTC() {
    RTC_Read_Clock(0); /*gives second,minute and hour*/
    I2C_Stop();
    //MSdelay(1000);
    
    hour = hour & (0x1f);
    sprintf(secs, "%x ", sec); /*%x for reading BCD format from RTC DS1307*/
    sprintf(mins, "%x:", min);
    sprintf(hours, "Tim:%x:", hour);
    LCD_String_xy(0, 0, hours);
    LCD_String(mins);
    LCD_String(secs);
}




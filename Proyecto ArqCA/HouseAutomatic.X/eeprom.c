/*
Estas librerias fueron escritas por mi, dale like.
Instagram âž¥ http://instagram.com/robertelectronica
Facebook  âž¥ https://www.facebook.com/Robertelectronico/
Youtube   âž¥ https://www.youtube.com/channel/UCYze8bs8C1qF6UbV2r4LrAA/videos?view_as=subscriber
*/
#include <xc.h>
#define _XTAL_FREQ        4000000UL
#include "lcd.h"

void eeprom_writex(int address, char data)
{
    EEADR = address;		//  1.Escribir la dirección de la memoria en el registro EEADR
    EEDATA = data;          //  2.	Escribir el dato a guardar en el registro EEDAT
    EECON1bits.EEPGD = 0;	//  3.	Acceder a la memoria de datos de la EEPROM
    EECON1bits.CFGS = 0;	//  4.	Acceder a la EEPROM
    EECON1bits.WREN = 1;	//  5.	Habilitar escritura
    INTCONbits.GIE = 0;     //  6.	Deshabilitar interrupciones
    
    //  7.  Enviar secuencia EECON2 = 0x55 y EECON2 = 0xAA y 
    //      empezar la escritura en la memoria EEPROM
    EECON2 = 0x55;
    EECON2 = 0xaa;
    EECON1bits.WR = 1;          // Bit que empieza la escritura en la memoria
    
    INTCONbits.GIE = 1;         //  8.	Habilitar interrupciones
    while (EECON1bits.WR);      // 9.	Esperar hasta que la escritura se complete 
}

char eeprom_readx(int address)
{
    EEADR = address;        //  1.	Escribir la dirección de la memoria a leer en el registro EEADR  
    EECON1bits.EEPGD = 0;	//  2.	Acceder a la memoria de datos de la EEPROM
    EECON1bits.CFGS = 0;	//  3.	Acceder a la EEPROM
    EECON1bits.RD = 1;      //  4.	Leer datos de la EEPROM
    return(EEDATA);
}
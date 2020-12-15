/*
Estas librerias fueron escritas por mi, dale like.
Instagram ➥ http://instagram.com/robertelectronica
Facebook  ➥ https://www.facebook.com/Robertelectronico/
Youtube   ➥ https://www.youtube.com/channel/UCYze8bs8C1qF6UbV2r4LrAA/videos?view_as=subscriber
*/

#include "lcd_1.h"

void LCD_putc(unsigned char ch){		//Sends Char to LCD

    LCDRS = 1;
    
    if ( ch & 0x10 ) {
        LCD4 = 1;
	} else {
        LCD4 = 0;
	}
	if ( ch & 0x20 ) {
        LCD5 = 1;
	} else {
        LCD5 = 0;
	}
	if ( ch & 0x40 ) {
        LCD6 = 1;
	} else {
        LCD6 = 0;
	}
	if ( ch & 0x80 ) {
        LCD7 = 1;
	} else {
        LCD7 = 0;
	}
    
    LCDE = 1;
    __delay_us(300);
    LCDE = 0;
    __delay_us(300);
    
    if ( ch & 0x01 ) {
        LCD4 = 1;
	} else {
        LCD4 = 0;
	}
	if ( ch & 0x02 ) {
        LCD5 = 1;
	} else {
        LCD5 = 0;
	}
	if ( ch & 0x04 ) {
        LCD6 = 1;
	} else {
        LCD6 = 0;
	}
	if ( ch & 0x08 ) {
        LCD7 = 1;
	} else {
        LCD7 = 0;
	}
    
    LCDE = 1;
    __delay_us(300);
    LCDE = 0;
    __delay_us(300);
}
void LCD_command(unsigned char cmd){	//Sends Command to LCD

    LCDRS = 0;
    
    if ( cmd & 0x10 ) {
        LCD4 = 1;
	} else {
        LCD4 = 0;
	}
	if ( cmd & 0x20 ) {
        LCD5 = 1;
	} else {
        LCD5 = 0;
	}
	if ( cmd & 0x40 ) {
        LCD6 = 1;
	} else {
        LCD6 = 0;
	}
	if ( cmd & 0x80 ) {
        LCD7 = 1;
	} else {
        LCD7 = 0;
	}
    
    LCDE = 1;
    __delay_ms(1);
	LCDE = 0;
    __delay_ms(1);

    if ( cmd & 0x01 ) {
        LCD4 = 1;
	} else {
        LCD4 = 0;
	}
	if ( cmd & 0x02 ) {
        LCD5 = 1;
	} else {
        LCD5 = 0;
	}
	if ( cmd & 0x04 ) {
        LCD6 = 1;
	} else {
        LCD6 = 0;
	}
	if ( cmd & 0x08 ) {
        LCD7 = 1;
	} else {
        LCD7 = 0;
	}
    
    LCDE = 1;
    __delay_ms(1);
    LCDE = 0;
    __delay_ms(1);

}
void LCD_init(void){//Initializes LCD
   
	//4 bit part
    __delay_ms(15);
    TLCDRS  =   0;
    TLCDRW  =   0;
    TLCDE   =   0;
    TLCD4   =   0;
    TLCD5   =   0;
    TLCD6   =   0;
    TLCD7   =   0;
	
    LCD7 = 0; LCD6 = 0; LCD5 = 0; LCD4 = 0;
    LCDE = 0; LCDRW = 0; LCDRS = 0;
    //---------one------
    LCD7 = 0; LCD6 = 0; LCD5 = 1; LCD4 = 1;
    LCDE = 1; LCDRW = 0; LCDRS = 0;
	__delay_ms(1);
    LCDE = 0;
	__delay_ms(1);
	//-----------two-----------
    LCD7 = 0; LCD6 = 0; LCD5 = 1; LCD4 = 1;
    LCDE = 1; LCDRW = 0; LCDRS = 0;
	__delay_ms(1);
    LCDE = 0;
	__delay_ms(1);
	//-------three-------------
    LCD7 = 0; LCD6 = 0; LCD5 = 1; LCD4 = 0;
    LCDE = 1; LCDRW = 0; LCDRS = 0;
	__delay_ms(1);
    LCDE = 0;
	__delay_ms(1);
	//--------4 bit--dual line--5x8 dots---------------
	LCD_command(SETLCD_4BITS_2LINE);
    //-----increment address, invisible cursor shift------
	LCD_command(DISPLAY_ON_D_OFF_CB);
    //-----Clear display
    LCD_clear();
}

void LCD_puts(unsigned char* data, unsigned char nBytes){	//Outputs string to LCD
	register unsigned char i=0;

	for(i=0; i<nBytes; i++){	// print data
		LCD_putc(data[i]);
	}
}

void LCD_gotoxy(unsigned char x, unsigned char y){		//Cursor to X Y position
	register unsigned char DDRAMAddr;

	switch(y){		// remap lines into proper order
	case 1: DDRAMAddr = LCD_LINE0_DDRAMADDR+x-1; break;
	case 2: DDRAMAddr = LCD_LINE1_DDRAMADDR+x-1; break;
	case 3: DDRAMAddr = LCD_LINE2_DDRAMADDR+x-1; break;
	case 4: DDRAMAddr = LCD_LINE3_DDRAMADDR+x-1; break;
	default: DDRAMAddr =LCD_LINE0_DDRAMADDR+x-1;break;
	}
	LCD_command(1<<LCD_DDRAM|DDRAMAddr);	// set data address
}
/*  Funcion para escribir en la CGRAM
 *	DATASHEET HD44780U (LCD-II) (Dot Matrix Liquid Crystal Display Controller/Driver)
 *	page 19.
 * */
void LCD_definechar(unsigned char *car,unsigned char CGRAM_dir){
	unsigned char i=0,a=0;
	a=(CGRAM_dir<<3)|1<<LCD_CGRAM;		//	posiciona en la CGRAM address
	for(i=0;i<8;i++){
        LCD_command(a++);			//	incrementa la direccion para la data
		LCD_putc(car[i]);			//	escribe caracter		
	}
}

void LCD_clear(void){
    LCD_command(CLEAR_DISPLAY);
}


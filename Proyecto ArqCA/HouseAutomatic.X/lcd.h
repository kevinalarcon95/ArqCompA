/*
Estas librerias fueron escritas por mi, dale like.
Instagram ➥ http://instagram.com/robertelectronica
Facebook  ➥ https://www.facebook.com/Robertelectronico/
Youtube   ➥ https://www.youtube.com/channel/UCYze8bs8C1qF6UbV2r4LrAA/videos?view_as=subscriber
*/
#ifndef LCD_H
#define	LCD_H

//----------------   LCD
#define  LCDRS  LATDbits.LATD0
#define  LCDRW  LATDbits.LATD1
#define  LCDE   LATDbits.LATD2
#define  LCD4   LATDbits.LATD4
#define  LCD5   LATDbits.LATD5
#define  LCD6   LATDbits.LATD6
#define  LCD7   LATDbits.LATD7
//----------------   LCD
#define  TLCDRS  TRISDbits.TRISD0
#define  TLCDRW  TRISDbits.TRISD1
#define  TLCDE   TRISDbits.TRISD2
#define  TLCD4   TRISDbits.TRISD4
#define  TLCD5   TRISDbits.TRISD5
#define  TLCD6   TRISDbits.TRISD6
#define  TLCD7   TRISDbits.TRISD7
/*
 *  RS  :   F2
 *  RW  :   F3
 *  E   :   F4
 */

//Uncomment this if LCD 4 bit interface is used
//******************************************
#define LCD_4bit
//***********************************************

#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address

/*
 * Function set
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *	0 	0 	0 	0 	1 	DL 	N 	F 	? 	?
 *	(DL) data length				DL=1: 8 bits, 	DL=0: 4 bits
 *	(N)  number of display lines  	N=1:  2 lines, 	 N=0: 1 line
 *	(F)	 character font  			F=1:  5x10 dots, F=0: 5x8 dots
 */
#define  SETLCD_4BITS_2LINE    	0b00101000
/*
 * Display	on/off
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *  0 	0 	0 	0 	0 	0 	1 	D 	C 	B
 *	Sets entire Display on/off				(D).
 *	Cursor on/off 							(C).
 *	Blinking of cursor position character 	(B).
 */
#define  DISPLAY_ALL_ON				0b00001111
#define  DISPLAY_ON_D_OFF_CB		0b00001100
#define  DISPLAY_ON_D_ON_C_OFF_B	0b00001110
#define  DISPLAY_ON_D_OFF_C_ON_B	0b00001101
/*
 * Entry mode set
 * Sets cursor move direction and specifies display shift.
 * These operations are performed during data write and read.
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *  0 	0 	0 	0 	0 	0 	0 	1  I/D 	S
 *  I/D=1	: Increment
 *  I/D=0	: Decrement
 *  S=1	: Accompanies display shift
 */
#define	 EMS_INC_S			0b00000110
/*
 * Cursor or display shift
 * Moves cursor and shifts display without changing DDRAM contents.
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
   	0 	0 	0 	0 	0 	1  S/C R/L 	? 	?
	S/C=1: Display shift			S/C=0: Cursor move
	R/L=1: Shift to the right		R/L=0: Shift to the left
 */
#define	DISP_MOVE_RIGHT		0b00011100
#define	DISP_MOVE_LEFT		0b00011000
#define	CURSOR_MOVE_RIGHT	0b00010100
#define	CURSOR_MOVE_LEFT	0b00010000
/*
 * Set	DDRAM
 * RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 *  0 	0 	1  ADD ADD ADD ADD ADD ADD ADD
 */
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54
/*******************************************************************/
#define	 RETURN_HOME		0b00000010
#define  CLEAR_DISPLAY   	0b00000001
/********************************************************************/

void LCD_putc(unsigned char);				//forms data ready to send to 74HC164
void LCD_command(unsigned char);				//forms data ready to send to 74HC164
void LCD_init(void);								//Initializes LCD
void LCD_puts(unsigned char*, unsigned char);	//Outputs string to LCD
void LCD_gotoxy(unsigned char, unsigned char);	//Cursor to X Y position
void write_CGRAM(const unsigned char*,unsigned char);
void LCDdefinechar(unsigned char*,unsigned char);
void LCDsend_var(unsigned int);
void LCD_clear(void);

#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */


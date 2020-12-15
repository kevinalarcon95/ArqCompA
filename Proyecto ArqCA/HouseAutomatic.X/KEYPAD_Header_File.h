
#ifndef KEYPAD_H
#define	KEYPAD_H

#define PD7     7 
#define PD6     6
#define PD5     5
#define PD4     4
#define PD3     3
#define PD2     2
#define PD1     1
#define PD0     0

/* FILAS-SALIDAS */
#define ROW1   PD0
#define ROW2   PD1
#define ROW3   PD2
#define ROW4   PD3
/* COLUMNAS-ENTRADAS */
#define COL1   PD4
#define COL2   PD5
#define COL3   PD6
#define COL4   PD7

#define PTECLADO  TRISD
#define FILAS     LATD
#define COLUMNAS  PORTD

void teclado_init (void);
char teclado_getc(void);

#endif	/* KEYPAD_H */


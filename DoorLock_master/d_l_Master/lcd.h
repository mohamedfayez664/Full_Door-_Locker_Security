 /******************************************************************************
 * File Name: lcd.h
 *
 * Created date: 10 10 2019
 *
 * Description: header file for the LCD driver
 *
 * Author: Mohamed Fayez
 *******************************************************************************/

#ifndef LCD_A_
#define LCD_A_

#include "std_types.h"
#include "std_macros.h"
#include "std_micro_comp_conf.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define LCD_DATA_BITS  4

/* Use higher 4 bits in the data port */
#if (LCD_DATA_BITS == 4)
#define UPPER_PORT_PINS      /*4,5,6,7*/
#undef  UPPER_PORT_PINS  /////*0,1,2,3*//////
#endif

/* LCD HW Pins */
/*Note: in case of 4 pins make data port -->> like data port
 *      and make data in lower of port */
#define RS 4
#define RW 5
#define E  6

#define LCD_DATA_PORT_DIR DDRC
#define LCD_DATA_PORT_OUT PORTC
#define LCD_CTRL_PORT_DIR DDRC
#define LCD_CTRL_PORT_OUT PORTC


/* LCD Commands */
#define LCD_CLEAR_SCREEN 0x01
#define FOUR_BITS_DATA_MODE 0x02  //not important//
#define TWO_LINE_LCD_Four_BIT_MODE  0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38

#define LCD_DISPLAY_OFF      0x08          // turn display off
#define LCD_ENTRYMODE       0x06          // shift cursor from left to right on read/write

#define LCD_CURSOR_OFF    0x0C
#define LCD_CURSOR_ON     0x0E
#define LCD_CURSOR_BLINK  0x0Fu
#define SET_CURSOR_LOCATION 0x80 

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_displayNumber(sint32 number);  /* max number is size of uint: 4294967295 */
void LCD_displayFloatNumber(float32 number,uint8 num_pre);  /* max number is size of uint: 4294967295 */

void LCD_clearScreen(void);

#endif /* LCD_A_ */

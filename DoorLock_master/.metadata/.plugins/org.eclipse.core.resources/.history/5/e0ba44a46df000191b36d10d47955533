/******************************************************************************
 * File Name: lcd.c
 *
 * Created date: 10 10 2019
 *
 * Description: source file for the LCD driver
 *
 * Author: Mohamed Fayez
 *******************************************************************************/

#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */

#if (LCD_DATA_BITS == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
#else
	LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);        /* initialize LCD in 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
#elif (LCD_DATA_BITS == 8)
	LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(LCD_CURSOR_OFF);   /* cursor off */
	LCD_sendCommand(LCD_CLEAR_SCREEN); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT_OUT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdsw = 190ns */
#if (LCD_DATA_BITS == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0xF0) | ((command & 0xF0) >> 4);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT_OUT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0xF0) | (command & 0x0F);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif (LCD_DATA_BITS == 8)
	LCD_DATA_PORT_OUT = command ;  /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1);                 /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1);                 /* delay for processing Th = 13ns */
#endif
}


void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT_OUT,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT_OUT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
#if (LCD_DATA_BITS == 4)
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0xF0) | ((data & 0xF0) >> 4);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT_OUT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0xF0) | (data & 0x0F);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif (LCD_DATA_BITS == 8)
	LCD_DATA_PORT_OUT = data; /* out the required data to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayString(const char *Str)
{
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
}

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;

	/* first of all calculate the required address */
	switch(row)
	{
	case 0:
		Address=col;
		break;
	case 1:
		Address=col+0x40;
		break;
	case 2:
		Address=col+0x10;
		break;
	case 3:
		Address=col+0x50;
		break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
	//	while((*Str) != '\0')
	//		{
	//			LCD_displayCharacter(*Str);
	//			Str++;
	//		}
	//	col++;
	//	if (col==15)
	//		row=1;
	//
}

void LCD_displayNumber(sint32 number) /* max number is size of uint: 4294967295 */
{
	static char str[11];       //max number entered to display on lcd
	char *buff = &str[10];     /* String to hold the ascii result */
	uint8 negtive_flag = 0 ;
	if (number<0){
		negtive_flag=1  ;
		number = -number ;
	}
	*buff = '\0';
	if (number == 0){
		*--buff = '0';
	}
	else {
		while(number>0)
		{
			*--buff = "0123456789"[number %10]; /* 10 for decimal */
			number /=10;
		}
	}
	if(negtive_flag){
		negtive_flag=0;
		*--buff = '-' ;
	}
	LCD_displayString(buff);

#if 0
	/*another solution*/
	char buff[11];
	itoa(number,buff,10);
	LCD_displayString(buff);
#endif
}
void LCD_displayFloatNumber(float32 data,uint8 num_pre)
{
	static uint8 str[11];   //max number entered to display on lcd
	uint8 *buff = &str[10], p_counter=num_pre ,negtive_flag=0;
	float32 pre; uint32 p=1;            /* String to hold the ascii result */
	*buff = '\0';
	if (data<0){
		negtive_flag=1;
		data=-data  ;
	}
	for(;p_counter>0;p_counter--)
		p*=10;
	pre=data-(int)data;
	pre*=p;
	if (data == 0){
		while(num_pre>0){
			*--buff = '0';
			num_pre--;
		}
		*--buff = ',';
		*--buff = '0';
	}
	else {
		while((int)pre>0)
		{
			*--buff = "0123456789"[(int)pre %10]; /* 10 for decimal */
			pre =(int)pre/10;
			num_pre--;
		}
		if(num_pre>0){
			*--buff = '0';
			num_pre--;
		}
		*--buff = ',';
		if((int)data==0)
			*--buff = '0';
		while((int)data>0)
		{
			*--buff = "0123456789"[(int)data %10]; /* 10 for decimal */
			data =(int)data/10;
		}
	}
	if(negtive_flag){
		negtive_flag=0;
		*--buff = '-';
	}
	LCD_displayString(buff);
}


void LCD_clearScreen(void)            /*not important */
{
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mohamed Fayez
 *
 *******************************************************************************/
#include "uart.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
ISR(USART_RXC_vect)
{
	PORTB=UDR;
}

/*frame: Async, dis parity, 1.stop bit, 8.bits data*/
void UART_init(UART_ConfigType * Config_Ptr)
{
	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X); /*in first //////////////////////////*/
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/ 
	UCSRB = (1<<RXEN) | (1<<TXEN) ;//|(1<<RXCIE);
	
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/ 	
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | \
			( (Config_Ptr->stopbits)<<USBS) | ( (Config_Ptr->parity)<<UPM0) ;
	
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}
	
void UART_sendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
	/******** Another Method *************/
	/*
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/	
}

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*check parity and frame error
	if( (BIT_IS_CLEAR(UCSRA,FE)) && (BIT_IS_CLEAR(UCSRA,PE))
	   return UDR;	
	else 
	   UART_sendByte(FALID_DATA);
	*/
	/*   Read the received data from the Rx buffer (UDR) and
	 *-> the RXC flag will be cleared after read this data */
    return UDR;		
}

void UART_sendString(const uint8 *Str ,uint8 str_length )
{
	uint8 i = 0;
	while(i < str_length)
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

/*not return address */
/*send length*/

void UART_receiveString(uint8 *Str ,uint8 str_length)
{
	uint8 i = 0;
	Str[i] = UART_recieveByte();   //must recieve first

	while(++i < str_length)  ////with do while
	{
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}

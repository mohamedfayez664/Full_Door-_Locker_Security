 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Fayez
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "std_macros.h"
#include "std_micro_comp_conf.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* UART Driver Baud Rate */

#define USART_BAUDRATE 9600
#define FALID_DATA  0xff

typedef enum
{
	off,even=2 ,odd
}UART_Parity;

/*division factor*/
typedef enum
{
	 oneStopBit ,towStopBit
}UART_StopBit;

typedef struct
{
	UART_Parity parity;
	UART_StopBit stopbits;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void UART_init(UART_ConfigType * Config_Ptr);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str ,uint8);

void UART_receiveString(uint8 *Str ,uint8); // Receive until #

#endif /* UART_H_ */

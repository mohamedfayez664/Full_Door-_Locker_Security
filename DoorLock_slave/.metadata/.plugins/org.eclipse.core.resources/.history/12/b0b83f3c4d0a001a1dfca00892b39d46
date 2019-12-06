/******************************************************************************
 * File Name: micro_compiler_config.h
 *
 * Description: header file for the micro and compiler configuration
 *
 * Author: Mohamed Fayez
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#include "std_types.h"

/*compiler dependant*/
#define INLINE inline

/*Micro dependant*/
#define F_CPU 1000000UL     //Clock frequency

#include <avr/interrupt.h>
#include <avr/delay.h>
/*general definitions ////////////////*/
/* Definition for PORTA Registers */
#define PORTA	(*(volatile uint8 * const)0x003B)
#define DDRA	(*(volatile uint8 * const)0x003A)
#define PINA 	(*(volatile const uint8 * const)0x0039)

/* Definition for PORTB Registers */
#define PORTB	(*(volatile uint8 * const)0x0038)
#define DDRB	(*(volatile uint8 * const)0x0037)
#define PINB 	(*(volatile const uint8 * const)0x0036)

/* Definition for PORTC Registers */
#define PORTC	(*(volatile uint8 * const)0x0035)
#define DDRC	(*(volatile uint8 * const)0x0034)
#define PINC 	(*(volatile const uint8 * const)0x0033)

/* Definition for PORTD Registers */
#define PORTD	(*(volatile uint8 * const)0x0032)
#define DDRD	(*(volatile uint8 * const)0x0031)
#define PIND 	(*(volatile const uint8 * const)0x0030)

/*External interrupts */
#define MCUCR *((volatile uint8 * const)0x55)
#define MCUCSR *((volatile uint8 * const)0x54)
#define GICR *((volatile uint8 * const)0x5B)
#define GIFR *((volatile uint8 * const)0x5A)
#define SREG *((volatile uint8 * const)0x5F)

/* Analoge to digital converter */

#define ADMUX *((volatile uint8 * const)0x27)
#define ADCSRA *((volatile uint8 * const)0x26)
#define ADCH *((volatile uint8 * const)0x25)
#define ADCL *((volatile uint8 * const)0x24)
#define SFIOR *((volatile uint8 * const)0x50)


/*timer 0*/
#define TCCR0 *((volatile uint8 * const)0x53)
#define TCNT0 *((volatile uint8 * const)0x52)
#define TIMSK *((volatile uint8 * const)0x59)
#define TIFR *((volatile uint8 * const)0x58)
#define OCR0 *((volatile uint8 * const)0x5C)

/*Timer 1*/
#define TCCR1A *((volatile uint8 * const)0x4F)
#define TCCR1B *((volatile uint8 * const)0x4E)
#define OCR1A *((volatile uint16 * const)0x4A)
#define ICR1A *((volatile uint16 * const)0x46)
#define TCNT1 *((volatile uint16 * const)0x4C)
#define OCR1B *((volatile uint16 * const)0x48)
#define ICR1 *((volatile uint16 * const)0x46)

/*Timer 2*/
#define TCCR2 *((volatile uint8 * const)0x45)
#define TCNT2 *((volatile uint8 * const)0x44)
#define ASSR *((volatile uint8 * const)0x42)
#define OCR2 *((volatile uint8 * const)0x43)

/*UART*/
#define UDR   *((volatile uint8 * const)0x2C)
#define UCSRA *((volatile uint8 * const)0x2B)
#define UCSRB *((volatile uint8 * const)0x2A)
#define UCSRC *((volatile uint8 * const)0x40)
#define UBRRL *((volatile uint8 * const)0x29)
#define UBRRH *((volatile uint8 * const)0x40)

/*SPI*/
#define SPCR *((volatile uint8 * const)0x2D)
#define SPSR *((volatile uint8 * const)0x2E)
#define SPDR *((volatile uint8 * const)0x2F)

/*I2C*/
#define TWBR *((volatile uint8 * const)0x20)
#define TWCR *((volatile uint8 * const)0x56)
#define TWSR *((volatile uint8 * const)0x21)
#define TWDR *((volatile uint8 * const)0x23)
#define TWAR *((volatile uint8 * const)0x22)

#if 0

typedef union
{
	unsigned char Data;
	struct
	{
		uint8 BIT0:1;
		uint8 BIT1:1;
		uint8 BIT2:1;
		uint8 BIT3:1;
		uint8 BIT4:1;
		uint8 BIT5:1;
		uint8 BIT6:1;
		uint8 BIT7:1;
	}BITS;
}Reg_8bit;

/*bits definitions ///////////////////////////////////////////////// */
/* Definition for PORTA Registers */
#define PINA_REG  (*(volatile Reg_8bit *)0x0039)
#define DDRA_REG  (*(volatile Reg_8bit *)0x003A)
#define PORTA_REG (*(volatile Reg_8bit *)0x003B)

/* Definition for PORTC Registers */
#define PINC_REG  (*(volatile Reg_8bit *)0x0033)
#define DDRC_REG  (*(volatile Reg_8bit *)0x0034)
#define PORTC_REG (*(volatile Reg_8bit *)0x0035)

#endif

#endif /* MICRO_CONFIG_H_ */

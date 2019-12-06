/******************************************************************************
 * File Name: std_macro.h
 *
 * Description: header file for the standard macro
 *
 * Author: Mohamed Fayez
 *******************************************************************************/

#ifndef std_macro_H_
#define std_macro_H_

/* Bits input output macro */
/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)             (REG|=(1<<BIT))
/* Set a certain two bits in any register */
#define SET_2BIT(REG,BIT1,BIT2)      (REG|=(1<<BIT1)|(1<<BIT2))
/* Set a certain three bits in any register */
#define SET_3BIT(REG,BIT1,BIT2,BIT3) (REG|=(1<<BIT1)|(1<<BIT2)|(1<<BIT3))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )
/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

#endif 
 /******************************************************************************
 * File Name: timer.h
 *
 * Description: Header file for the AVR timer driver
 *
 * Author: Mohamed Fayez
 *
 *******************************************************************************/

#ifndef TIMER_Init_H
#define TIMER_Init_H

#include "std_types.h"
#include "std_macros.h"
#include "std_micro_comp_conf.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	TIMER0, TIMER0_OVF ,TIMER0_CTC ,TIMER0_Square_Wave,TIMER0_Fast_PWM, \
	TIMER1,TIMER1_OVF, TIMER1_CTC_A ,TIMER1_ICU ,TIMER1_Square_Wave ,TIMER1_Fast_PWM
}TIMER_Type;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}TIMER_Clock;

typedef struct
{
	TIMER_Type  type;
	TIMER_Clock clock;
	uint16 Reg_value;
}TIMER_ConfigType;

typedef enum
{
	FALLING,RISING
}Icu_EdgeType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 // timer 0 
 *******************************************************************************/
/*
 * Description : Function to initialize the timer0 
 * 	1. Set the timer type.
 * 	2. Set the required clock.
 * 	3. Initialize Timer0 Registers
 */
void TIMER0_init    (TIMER_ConfigType *Config_Ptr);
/*
 * Description: Function to set the Call Back function address.
 */
void TIMER0_CallBack(void(*a_ptr)(void));

/*   timer 1     */
/*
 * Description : Function to initialize the timer1
 * 	1. Set the timer type.
 * 	2. Set the required clock.
 * 	3. Initialize Timer0 Registers
 */
void TIMER1_init  (TIMER_ConfigType *Config_Ptr) ;  //need to modify
/*
 * Description: Function to set the Call Back function address.
 */
void TIMER1_CallBack  (void(*a_ptr)(void));

/*
 * Description: Function to set the required edge detection for icu.
 */
 void Icu_setEdgeDetectionType(const Icu_EdgeType edgeType);

 /*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void);

void Timer1_Fast_PWM_n_invert_speed(uint16 comp_regA);

///////////////////////////
void TIMER_Start (uint8 timer_type, uint8 clk_slect);
/* Disable timer Driver */
void TIMER_Stop  (uint8 timer_type);
/*
 * Description: Function to clear the Timer Value to start count from ZERO
 */
void TIMER_Clear (uint8 timer_type);
/*
 * Description: Function to disable the Timer to stop it
 */
void TIMER_Deinit(uint8 timer_type);

#if 0
/*   timer 2     */
void TIMER2_OVF_init(uint8 init_start, uint8 clk_slect);
void TIMER2_comp_init(uint8 comp_reg , uint8 clk_slect);

void TIMER2_OVF_CallBack(void(*a_ptr)(void));
void TIMER2_CTC_CallBack(void(*a_ptr)(void));

void TIMER2_CTC_Square_Wave_init  (uint8 comp_reg ,uint8 clk_slect);
void TIMER2_Fast_PWM_n_invert_init(uint8 comp_reg ,uint8 clk_slect);

void TIMER2_start(uint8 clk_slect);
void TIMER2_stop  (void);
void TIMER2_clear(void);
void TIMER2_deinit(void);

#endif

////////////////////////////////////////////////////////////////////////
void WDT_ON (uint8 WDClk);
void WDT_OFF(uint8 four_cycles);

#endif  //TIMER_Init_H

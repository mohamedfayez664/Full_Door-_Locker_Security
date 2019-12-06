/******************************************************************************
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR timer driver
 *
 * Author: Mohamed Fayez
 *
 *******************************************************************************/

#include "timer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_TIMER0_callBackPtr)(void) = NULL;

static volatile void (*g_TIMER1_callBackPtr)(void) = NULL;

/*
static volatile void (*g_TIMER2_OVF_callBackPtr)(void) = NULL;
static volatile void (*g_TIMER2_CTC_callBackPtr)(void) = NULL;
 */

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_TIMER0_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_TIMER0_callBackPtr)(); /* another method to call the function using pointer to function g_TIMER0_OVF_callBackPtr(); */
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_TIMER0_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_TIMER0_callBackPtr)(); /* another method to call the function using pointer to function g_TIMER0_OVF_callBackPtr(); */
	}
}
///////////////////////////////////
ISR(TIMER1_COMPA_vect)
{
	if(g_TIMER1_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_TIMER1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_CAPT_vect)
{
	if(g_TIMER1_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_TIMER1_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the timer0 
 * 	1. Set the timer type.
 * 	2. Set the required clock.
 * 	3. Initialize Timer0 Registers
 */
void TIMER0_init( TIMER_ConfigType *Config_Ptr)
{
	if(Config_Ptr->type == TIMER0_OVF){
		TCNT0=Config_Ptr->Reg_value;       // init_start;  //initial

		TCCR0 =(1<<FOC0) | (Config_Ptr->clock);  //clock
		TIMSK |=(1<<TOIE0);   //module enable
	}
	else if(Config_Ptr->type == TIMER0_CTC){
		TCNT0=0;                 //initial
		OCR0=Config_Ptr->Reg_value ;           //compare

		TCCR0 = (1<<FOC0) | (1<<WGM01) | (Config_Ptr->clock);    //clock
		TIMSK |=(1<<OCIE0);   //module enable
	}
	else if(Config_Ptr->type == TIMER0_Square_Wave){
		DDRB |= (1<<PB3);      //make pin output
		TCNT0=0;               //initial
		OCR0=Config_Ptr->Reg_value;         //compare

		TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<COM00) | (Config_Ptr->clock);    //clock
	}
	else if(Config_Ptr->type == TIMER0_Fast_PWM){
		//FOCnPWM= Fclk/ (N * 256)  //N is prescaler
		//so N= Fclk/(FOCnPWM * 256)
		DDRB |= (1<<PB3);      //make pin output
		TCNT0=0;                 //initial
		OCR0=Config_Ptr->Reg_value;                    //compare

		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (Config_Ptr->clock);    //clock
	}
}

void TIMER0_CallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_TIMER0_callBackPtr = a_ptr;
}


/*   timer 1       */
/*
 * Description : Function to initialize the timer0 
 * 	1. Set the timer1 type.
 * 	2. Set the required clock.
 * 	3. Initialize Timer1 Registers
 */
void TIMER1_init(TIMER_ConfigType *Config_Ptr)   //need to modify
{

	if(Config_Ptr->type == TIMER0_OVF){
		TCNT1=Config_Ptr->Reg_value;       // init_start;  //initial

		TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
		TCCR1B = (Config_Ptr->clock);    //clock
		TIMSK |=(1<<TOIE1);   //module enable
	}
	else if(Config_Ptr->type == TIMER1_CTC_A){
		TCNT1=0;                 //initial
		OCR1A=Config_Ptr->Reg_value;           //compare

		TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;           //Configuration
		TCCR1B = (1<<WGM12) | (Config_Ptr->clock);    //clock
		TIMSK |=(1<<OCIE1A);    //module enable
	}
	else if(Config_Ptr->type == TIMER1_ICU){
		/* Configure ICP1/PD6 as i/p pin */
		DDRD &= ~(1<<PD6);

		/* Initial Value for Timer1 */
		TCNT1 = 0;
		/* Initial Value for the input capture register */
		ICR1  = 0;

		/* Timer1 always operates in Normal Mode */
		TCCR1A = (1<<FOC1A) | (1<<FOC1B);
		/*
		 *  insert the required clock value in the first three bits (CS10, CS11 and CS12) of TCCR1B Register
		 *  insert the required edge type in ICES1 bit in TCCR1B Register
		 */
		TCCR1B = (TCCR1B & 0xB8) | ((Config_Ptr->clock)&0x07) | (1<<6);   //with rising

		/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
		TIMSK |= (1<<TICIE1);
	}
	else if(Config_Ptr->type == TIMER1_Square_Wave){
		DDRD |= (1<<PD5);	/* Make OC1A pin as output */
		TCNT1 = 0;		/* Set timer1 initial count to zero */
		OCR1A = Config_Ptr->Reg_value;;      /* Set the compare value at A */

		TCCR1A = (1<<FOC1A) | (1<<FOC1B)| (1<<COM1A0);
		TCCR1B = (1<<WGM12) | (Config_Ptr->clock);    //clock
	}
	else if(Config_Ptr->type == TIMER1_Fast_PWM){
		// fOCnxPWM= fclk/ (N*(1+top) )
		// so (N*(1+top)=fclk/fOCnxPWM
		// so top =((fclk/fOCnxPWM)-N)/N
		DDRD |= (1<<PD5);	/* Make OC1A pin as output */
		TCNT1 = 0;		/* Set timer1 initial count to zero */
		OCR1A = Config_Ptr->Reg_value;      /* Set the compare value at A */

		ICR1 = 2499;//top;         //2499;	/* Set TOP count for timer1 in ICR1 register */
		/* Configure timer control register TCCR1A
		 * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
		 * 2. Disconnect OC1B  COM1B0=0 COM1B1=0
		 * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
		 * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
		 */
		TCCR1A = (1<<WGM11) | (1<<COM1A1);

		/* Configure timer control register TCCR1A
		 * 1. Fast Pwm Mode with the TOP in ICR1 WGM12=1 WGM13=1 (Mode Number 14)
		 * 2. Prescaler = F_CPU/64
		 */
		TCCR1B = (1<<WGM12) | (1<<WGM13) | (Config_Ptr->clock);    //clock //(1<<CS10) | (1<<CS11);
	}
}

/*
 * Description: Function to set the required edge detection for icu.
 */
void Icu_setEdgeDetectionType(const Icu_EdgeType edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (edgeType<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to set the Call Back function address.
 */
void TIMER1_CallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_TIMER1_callBackPtr = a_ptr;
}

///////////////////////////////////
void Timer1_Fast_PWM_n_invert_speed(uint16 comp_regA)
{
	OCR1A = comp_regA;      /* Set the compare value at A */
}
////////////////////
void TIMER_Start(uint8 timer_type,uint8 clk_slect){
	if(timer_type==TIMER0)
		TCCR0= (TCCR0&0xf8)|(clk_slect&0x07);
	else if(timer_type==TIMER1)
		TCCR1B=(TCCR1B&0xf8)| (clk_slect&0x07);

}
/* Disable timers  */
void TIMER_Stop(uint8 timer_type){
	if(timer_type==TIMER0)
		TCCR0&=~0x07;
	else if(timer_type==TIMER1)
		TCCR1B&=~0x07;
}
/*
 * Description: Function to clear the Timers Value to start count from ZERO
 */
void TIMER_Clear(uint8 timer_type)
{
	if(timer_type==TIMER0)
		TCNT0 = 0;
	else if(timer_type==TIMER1)
		TCNT1 = 0;
}
/*
 * Description: Function to disable the Timers to stop it
 */
void TIMER_Deinit(uint8 timer_type)
{
	/* disable the Timer0 to stop it*/
	if(timer_type==TIMER0){
		/* Clear All Timer0 Registers */
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0  = 0;

		/* Disable timer 0 interrupt */
		TIMSK &= ~((1<<TOIE0)|(1<<OCIE0));
	}
	/* disable the Timer1 to stop it*/
	else if(timer_type==TIMER1){
		/* Clear All Timer1 Registers */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0 ;
		OCR1B = 0 ;
		ICR1 = 0;

		/* Disable the timer1 interrupt */
		TIMSK &= ~((1<<TOIE1)|(1<<OCIE1A)|(1<<OCIE1B)|(1<<TICIE1));
	}

}


#if 0
/*   timer 2     */
void TIMER2_OVF_init(uint8 init_start, uint8 clk_slect)
{
	TIMSK |=(1<<TOIE2);   //module enable
	TCNT2=init_start;            //initial

	TCCR2 = (1<<FOC2) | (clk_slect);    //clock
}
void TIMER2_comp_init(uint8 comp_reg ,uint8 clk_slect)
{
	TIMSK |=(1<<OCIE2);   //module enable
	TCNT2=0;            //initial
	OCR2=comp_reg;               //compare

	TCCR2 = (1<<FOC2) | (1<<WGM21) | (clk_slect);    //clock
}
void TIMER2_OVF_CallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_TIMER2_OVF_callBackPtr = a_ptr;
}
void TIMER2_CTC_CallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_TIMER2_CTC_callBackPtr = a_ptr;
}

void TIMER2_CTC_Square_Wave_init(uint8 comp_reg ,uint8 clk_slect)
{
	DDRD |= (1<<PD7);      //make pin output
	TCNT2=0;                 //initial
	OCR2=comp_reg;                    //compare

	TCCR2 = (1<<FOC2) | (1<<WGM21) | (1<<COM20) | (clk_slect);    //clock
}

//FOCnPWM= Fclk/ (N * 256)  //N is prescaler
//so N= Fclk/(FOCnPWM * 256)
void TIMER2_Fast_PWM_n_invert_init(uint8 comp_reg ,uint8 clk_slect)
{
	DDRD |= (1<<PD7);      //make pin output
	TCNT2=0;                 //initial
	OCR2=comp_reg;                    //compare

	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (clk_slect);    //clock
}

void TIMER2_clear()
{
	TCNT2 = 0;
}

void TIMER2_off(){
	TCCR2&=~0x07;
}
void TIMER2_on(uint8 clk_slect){
	TCCR2=(TCCR2&0xf8)| (clk_slect&0x07);
}

void TIMER2_deinit()
{
	/* Clear All Timer0 Registers */
	TCCR2 = 0;
	TCNT2= 0;
	OCR2 = 0;

	/* Disable timer 0 interrupt */
	TIMSK &= ~((1<<TOIE2)|(1<<OCIE2));
}


#endif
/*w d timer */
void WDT_ON(uint8 WDClk){
	WDTCR= (1<<WDE)|(WDClk);
}

void WDT_OFF(uint8 four_cycles){
	WDTCR=(1<<WDE)|(1<<WDTOE);
	_delay_us(four_cycles);
	WDTCR&=~(1<<WDE);
}

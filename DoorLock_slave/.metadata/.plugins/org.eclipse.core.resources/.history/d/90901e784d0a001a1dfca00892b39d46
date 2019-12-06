#include "delay.h"

////////
volatile uint8 g_timer_var = 0;

#define F_CPU_8   2   //prescaler for fcpu 1 M
#define F_CPU_64  3   //prescaller for fcpu 8M

#if     (F_CPU == 1000000)
#define F_CPU_Pre F_CPU_8
#elif   (F_CPU == 8000000)
#define F_CPU_Pre F_CPU_64
#endif


/////////////////////////
void DELAY_init (){
	////timer2 init
	TCNT2=0;              //initial
	OCR2 =125 ;           //initial compare value 
	//>>for f_cpu 1 and 8 M  ,,,pre_scaler 8 and in mili seconds
	//it will over every 1 mili_second>>(1/1M/pre) >>8 usec per every count
	//>>> com = 1000/8 -> 125 >>    8usec * 125 =1000 usec

	TCCR2 = (1<<FOC2) | (1<<WGM21);  //clock is zero to make timer un_active
}

void DELAY_ms   (uint16 number_of_ms){

	if(number_of_ms >0 ){
		TCCR2 =(TCCR2 & 0xf8) | (F_CPU_Pre & 0x07); //to run timer enter clock(2for 1M ,3 to 8M)
		                                            // tcnt2 = 0 ;;;;;;

		while (number_of_ms--){

			while(BIT_IS_CLEAR(TIFR,OCF2) );
			SET_BIT(TIFR,OCF2) ;      //to make it = 0 again
			TCNT2 = 0;         //to clear timer
		}

		TCCR2&=~0x07;      //to turn timer off >> clear clock
		TCNT2 = 0;         //to clear timer
	}
} 


void DELAY_sec  (uint16 number_of_sec){

	if(number_of_sec > 0 ){
		while (number_of_sec--)
			DELAY_ms   (1000);
	}
}

#include "master.h"

//////static functions
static void new_pssowrd();
static void re_enter_new_pssowrd();
static uint8 check_pass();
void amo7ramy();

/////variables
uint8 my_pass_str[N_OF_PASS]= {0}  , counter;

///function definitions
void master_init(){
	DELAY_init();

	sei();

	UART_ConfigType myUartconf = {off , towStopBit};
	UART_init(&myUartconf);

	LCD_init();
}

void enter_new_pass(){
	do{
		new_pssowrd();
		re_enter_new_pssowrd();
	}while(check_pass() != TRUE_PASS);
}

void enter_pass(){
	static uint8 n_of_enters =1;
	do{
		LCD_clearScreen();
		LCD_displayString("enter your Pass:");
		LCD_goToRowColumn(2 , 1);
		for (counter=0 ; counter < N_OF_PASS ; counter ++){
			DELAY_ms(250);
			my_pass_str[counter]= KeyPad_getPressedKey();
			LCD_displayCharacter('*');
		}
		////////
		UART_sendString(my_pass_str,N_OF_PASS);
	}while(check_pass()!=TRUE_PASS && n_of_enters++ <= 2);  //4
	if(n_of_enters > 3){
		amo7ramy();
		n_of_enters=1;
		enter_pass();
	}
	else {
	    n_of_enters=1;
	}
}

void open_door (){
	/////////////////wait slave message
	LCD_clearScreen();
	LCD_goToRowColumn(2 , 1);
	LCD_displayString("WELCOME_DOOR OPEN");
	DELAY_ms(4000);   ////checking
	LCD_clearScreen();
	LCD_goToRowColumn(2 , 1);
	LCD_displayString("BYE_DOOR CLOSE");
	DELAY_ms(1000);  ////checking
	//wait for 15 sec
}

void amo7ramy (){
	/////////////////wait slave message
	LCD_clearScreen();
	LCD_goToRowColumn(2 , 1);
	LCD_displayString(" amo 7ramy ");
	DELAY_ms(10000);   ////checking
}

///////////////////////////////////////////////////
static void new_pssowrd(){
	LCD_clearScreen();
	LCD_displayString("enter new Pass:");
	LCD_goToRowColumn(2 , 1);
	for (counter=0 ; counter < N_OF_PASS ; counter ++){
		DELAY_ms(250);
		my_pass_str[counter]= KeyPad_getPressedKey();
		LCD_displayCharacter('*');
	}
	////////////////////
	//UART_sendByte(MASTER_SEND);
	//PORTB= UART_recieveByte(); ///////checking
	//while (UART_recieveByte() != SLAVE_READY);

	UART_sendString(my_pass_str ,N_OF_PASS);
}

static void re_enter_new_pssowrd(){
	LCD_clearScreen();
	LCD_displayString("re_enter Pass:");
	LCD_goToRowColumn(2 , 1);
	for (counter=0 ; counter < N_OF_PASS ; counter ++){
		DELAY_ms(250);
		my_pass_str[counter]= KeyPad_getPressedKey();
		LCD_displayCharacter('*');
	}
	/////
	UART_sendString(my_pass_str ,N_OF_PASS);
	PORTB=0; ////////////////////////
	////////
}

static uint8 check_pass(){
	return UART_recieveByte();
}

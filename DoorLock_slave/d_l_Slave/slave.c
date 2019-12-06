#include "slave.h"

//////static functions prototype
static void save_new_pass (uint8 *str ,uint8 str_lenghth);

/////variables
uint8 ROM_pass[N_OF_PASS]= {0},
		my_pass [N_OF_PASS]= {0}, counter;
uint8	  status=0xff;

/////Function definitions
void slave_init(){
	sei();

	DDRD |= 0X1C;
	PORTD&=~0X1C; //Initialization for motor and buzzer

	DELAY_init();

	UART_ConfigType myUartconf = {off , towStopBit};
	UART_init(&myUartconf);

	EX_EEPROM_init();   	/* Init EEPROM */

	uint8 bytewrite=Not_firsttime;
	EX_EEPROM_readData(0, &status, 1); ///need to modify
    if (status==Not_firsttime){
    	EX_EEPROM_readData(ROM_ADD, ROM_pass, N_OF_PASS); ///need to modify
    }
    else {
    	EX_EEPROM_writeData(0, &bytewrite, 1); ///need to modify
    }

	// UART_sendByte(out_compare);
}

void recieve_pass(){

	static uint8 n_of_enters =1;
	uint8 out_compare;

	UART_receiveString (my_pass, N_OF_PASS);  //to receive check pass

	out_compare=compare_pass (my_pass, N_OF_PASS);

	UART_sendByte(out_compare);
	// in case true didn't enter this stage.....
	if (out_compare==FALSE_PASS && n_of_enters <= 2 ){
		n_of_enters++;
		recieve_pass();
	}
	else if(out_compare==FALSE_PASS && n_of_enters > 2){
		amo7ramy();
		n_of_enters=1;
		recieve_pass();
	}
	else {
		n_of_enters=1;
	}
}

uint8 compare_pass(uint8 *new_pass ,uint8 str_lenghth){
	uint8 count;
	for(count=0; count<str_lenghth; count++){
		if(new_pass[count]!=ROM_pass[count])
			break;
	}
	if(count==5){
		return TRUE_PASS;
	}
	else if(count!=5){
		return FALSE_PASS;
	}
}

void receive_new_pass(){
	uint8 out_compare;
	//UART_sendByte(SLAVE_READY);
	//while (UART_recieveByte() != MASTER_SEND);
	UART_receiveString(ROM_pass, N_OF_PASS);

	save_new_pass(ROM_pass, N_OF_PASS);  //to save it

	UART_receiveString(my_pass, N_OF_PASS);  //to receive check pass

	out_compare=compare_pass (my_pass, N_OF_PASS);

	UART_sendByte(out_compare);

	if (out_compare==FALSE_PASS )
		receive_new_pass();
}

void open_door(){
	PORTD|= 0x08;
	DELAY_ms(1000);   ////checking
	PORTD&=~0X0C;
	DELAY_ms(3000);   ////checking
	PORTD|= 0x04;
	DELAY_ms(1000);   ////checking
	PORTD&=~0X0C;      ////close motor
}

void amo7ramy (void){
	PORTD|= 0x10;
	DELAY_ms(10000);   ////checking
	PORTD&=~0X10;
}

/////static functions definations
static void save_new_pass (uint8 *str ,uint8 str_lenghth){
	EX_EEPROM_writeData(ROM_ADD ,ROM_pass ,N_OF_PASS);
}

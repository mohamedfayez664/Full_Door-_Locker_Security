#include "slave.h"

uint8 letter , letter_action;

int main(void){

	slave_init();

	if(status!= Not_firsttime){
		UART_sendByte(firsttime);
		receive_new_pass ();
	}
	else{
		UART_sendByte(Not_firsttime);
	}

	////////////////
	while(1){
		letter=UART_recieveByte();

		if (letter == OPEN_DOOR){
			UART_sendByte(OPEN_DOOR);
			recieve_pass();
			open_door ();
		}
		else if(letter == CHANGE_PASS){
			UART_sendByte(CHANGE_PASS);
			recieve_pass();
			receive_new_pass ();
		}
		else {
			UART_sendByte(FAULT_LETTER);
		}
	}
}
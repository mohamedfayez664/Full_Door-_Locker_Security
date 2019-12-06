#include "master.h"

uint8 letter , letter_action ,status;

int main(void){

	master_init();

	status= UART_recieveByte();

	if(status== firsttime){
		enter_new_pass();
	}
	else{

	}

	//////////////////
	while(1){

		LCD_clearScreen();
		LCD_goToRowColumn(1,2);
		LCD_displayString(" *: open door ");
		LCD_goToRowColumn(2,2);
		LCD_displayString(" +: change pass");

		letter=KeyPad_getPressedKey();

		UART_sendByte(letter);
		letter_action=UART_recieveByte();

		if (letter_action == OPEN_DOOR){
			enter_pass();
			open_door ();
		}
		else if(letter_action == CHANGE_PASS){
			enter_pass();
			enter_new_pass();
		}
		else{

		}
	}
}

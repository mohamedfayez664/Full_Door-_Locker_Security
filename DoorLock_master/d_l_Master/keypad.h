 /******************************************************************************
 * File Name: keypad.h
 *
 *Created date: 10 10 2019
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Fayez
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "std_macros.h"
#include "std_micro_comp_conf.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4  /* static configurations need to build every time (negative)*/
#define N_row 4

/* Keypad Port Configurations */
/*Note: Keypad Port must take a full port and the rows in lower pins and
                         * the columns in the upper starting from pin 4 */
#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */

uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */

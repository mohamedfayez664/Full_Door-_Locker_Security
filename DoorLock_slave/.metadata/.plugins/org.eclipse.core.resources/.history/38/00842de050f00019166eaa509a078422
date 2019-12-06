#ifndef motor_Init_H
#define motor_Init_H

#include "std_types.h"
#include "std_macros.h"
#include "std_micro_comp_conf.h"

#include "timer.h"

#define   FULL_WAVE_STEPS  4
#define   HALF_WAVE_STEPS  8

#define data_port_dir   DDRC   // to set port connect with stepper motor
#define data_port       PORTC

extern unsigned char motor_full_steps [FULL_WAVE_STEPS] ;
extern unsigned char motor_half_steps [HALF_WAVE_STEPS] ;

void stepper_motor_init(void);


void servo_init(uint16 duty_cycle);

void servo_move(uint16 duty_cycle);

#endif  //motor_Init_H

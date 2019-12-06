#ifndef DELAY_H_
#define DELAY_H_

#include "std_types.h"
#include "std_macros.h"
#include "std_micro_comp_conf.h"

void DELAY_init ();
void DELAY_ms   (uint16 number_of_ms);
void DELAY_sec  (uint16 number_of_sec);


#endif

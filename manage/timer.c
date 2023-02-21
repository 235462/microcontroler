/*
 * timer.c
 *
 * Created: 19.02.2023 18:10:48
 *  Author: Lenovo
 */ 

#include <avr/io.h>

void f_manage_timer_reset()
{
	GTCCR = GTCCR | 0b00000001;		// Timer/Counter 0, 1, 3, 4 - prescaler reset
	TCNT1 = 0;							// Timer/Counter 1 Counter Value - reset
}

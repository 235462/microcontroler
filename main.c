#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"
#include "initial.h"

#include "manage/adc.h"
#include "manage/communication.h"
#include "manage/timer.h"
#include "manage/update.h"

ISR(USART0_TX_vect){}
ISR(USART0_RX_vect)
{	
	uint8_t command = UDR0; 
	if (command == 0b00000000)
	{
		f_manage_sampling(command);
		
		f_manage_transmit_measurements_time();
		f_manage_transmit_sampling();
	} 
	else if ((command & 0b11000000) == 0b00000000) 
	{
		f_manage_update_samples_number(command);			
	} 
	else if ((command & 0b11000000) == 0b01000000) 
	{
		f_manage_update_timestep_offset(command);			
	} 
	else if ((command & 0b11110000) == 0b10000000) 
	{
		TCCR1B = (TCCR1B & 0b11111000) | (command & 0b00000111);  	// new TIMER/COUNTER1 prescaler
	}
	else if ((command & 0b11000000) == 0b10000000) 
	{
		f_manage_update_pre_irradiating_time(command);
	} 
	else if ((command & 0b11000000) == 0b11000000) 
	{
		f_manage_update_irradiating_offset(command);
	}
	
}


int main(void)
{
	f_init_usart();
	f_init_adc();
	f_init_timer1();
	
	sei();
	while(1){};
}






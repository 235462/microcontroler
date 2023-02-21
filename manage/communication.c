/*
 * communication.c
 *
 * Created: 19.02.2023 18:06:37
 *  Author: Lenovo
 */ 

#include <avr/io.h>

void f_manage_till_usart_is_ready()
{
	while((UCSR0A & 0b00100000) != 0b00100000) {};
}

void f_manage_transmit_sampling()
{
	extern uint16_t g_samples_number;
	extern uint8_t g_measurements_l[];
	extern uint8_t g_measurements_h[];
	
	for(uint16_t i=0; i<g_samples_number; i++)
	{
		f_manage_till_usart_is_ready();
		UDR0=g_measurements_h[i];
		f_manage_till_usart_is_ready();
		UDR0=g_measurements_l[i];
	}
}

void f_manage_transmit_measurements_time()
{
	extern uint16_t g_measurements_time;
	
	f_manage_till_usart_is_ready();
	UDR0 = g_measurements_time >> 8;
	f_manage_till_usart_is_ready();
	UDR0 =g_measurements_time%256;
}

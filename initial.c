/*
 * initial.c
 *
 * Created: 19.02.2023 13:22:20
 *  Author: Lenovo
 */ 


#include <avr/io.h>

// initialize ADC 
void f_init_adc()
{
	ADMUX = (ADMUX & 0b00111111) | 0b01000000;		// reference voltage is taking from the pin AVCC
	ADMUX = (ADMUX & 0b11110000) | 0b00000000;		// pin PC0 as the converter input
	ADCSRB = ADCSRB & 0b10111111;					// enable the Analog Comparator Multiplexer
	
	DDRC  = (DDRC  & 0b11111110) | 0b00000000;		// fix the pin PC0 as a input
	PORTC = 0;										// the pull-up resistor is disconnected
	DIDR0 = (DIDR0 & 0b11111110) | 0b00000001;		// turn off the digital input (currents reduce)
	
	ADCSRA = ADCSRA & 0b11011111;					// disable the ADC Auto Trigger Enable
	ADCSRA = (ADCSRA & 0b11111000) | 0b00000100;	// fix the ADC prescaler
	ADCSRA = ADCSRA | 0b10000000;					// ADC Enable
	
	//ADCSRA = ADCSRA | 0b00001000;					// ADC Interrupt Enable
}

// initialize TIMER1/COUNTER
void f_init_timer1()
{
	//TIMSK1 |= 0b00000001;								// Timer/Counter 1, Overflow Interrupt Enable
	TCCR1B = ((TCCR1B & 0b11111000) | 0b00000101);  	// TIMER/COUNTER1 prescaler 256
}

// initialize USART
void f_init_usart()
{
	UCSR0A = UCSR0A & 0b11111101;					// U2X = 0
	UBRR0H = 0b00000000;
	UBRR0L = 0b00000011;							// in total 3; BR = F_CPU/(16*(3+1)) = 9600 bps;
	UCSR0B = (UCSR0B & 0b00111011) | 0b11000000;	// allows for interrupts, exchange type: indirect, look at the C register
	UCSR0C = (UCSR0C & 0b00000000) | 0b00000110;	// asynchronous, 8 bits of data, 1 stop bit, no parity
	UCSR0B = (UCSR0B & 0b11100111) | 0b00011000; 	// fix the RXEN TXEN  i.e. turn on the transmitter and reciever
}

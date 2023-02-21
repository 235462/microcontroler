/*
 * adc.c
 *
 * Created: 19.02.2023 18:08:51
 *  Author: Lenovo
 */ 
#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"

void f_manage_till_adc_is_ready()
{
	while((ADCSRA & 0b01000000) == 0b01000000) {};
}

void _f_no_preirradiation_no_offset()
{
	extern uint16_t g_samples_number;
	extern uint16_t g_timestep_offset;
	extern uint16_t g_measurements_time;
	extern uint8_t g_measurements_l[];
	extern uint8_t g_measurements_h[];
	
	uint16_t adc_converter = 0;
	uint16_t iterator = 0;
	
	f_manage_timer_reset();
	
	//start sampling
	for (iterator=0; iterator<g_samples_number; iterator++)
	{
		ADCSRA = ADCSRA | 0b01000000;								// ADC - start a conversion
		f_manage_till_adc_is_ready();
		
		adc_converter = ADC;										// read the measurement
		g_measurements_l[iterator] = adc_converter%256;				// write the result
		g_measurements_h[iterator] = adc_converter >> 8;			// write the result
		_delay_us(g_timestep_offset);								// timestep offset
	}	

	g_measurements_time = TCNT1;
}

void _f_no_preirradiation_nonzero_offset()
{
	extern uint16_t g_irradiating_offset;
	extern uint16_t g_samples_number;
	extern uint16_t g_timestep_offset;
	extern uint16_t g_measurements_time;
	extern uint8_t g_measurements_l[];
	extern uint8_t g_measurements_h[];
	
	uint16_t adc_converter = 0;
	uint16_t iterator = 0;
	
	f_manage_timer_reset();
	PORTB = 0b00000001;												// turn on the light
	
	// start sampling
	for (iterator=0; iterator<g_irradiating_offset; iterator++)
	{
		ADCSRA = ADCSRA | 0b01000000;								// ADC - start a conversion
		f_manage_till_adc_is_ready();
		
		adc_converter = ADC;										// read the measurement
		g_measurements_l[iterator] = adc_converter%256;				// write the result
		g_measurements_h[iterator] = adc_converter >> 8;			// write the result
		_delay_us(g_timestep_offset);								// timestep offset
	}
	
	PORTB = 0b00000000;												// turn off the irradiating
	
	//continue the sampling
	for (iterator=g_irradiating_offset; iterator<g_samples_number; iterator++)
	{
		ADCSRA = ADCSRA | 0b01000000;								// ADC - start a conversion
		f_manage_till_adc_is_ready();
		
		adc_converter = ADC;										// read the measurement
		g_measurements_l[iterator] = adc_converter%256;				// write the result
		g_measurements_h[iterator] = adc_converter >> 8;			// write the result
		_delay_us(g_timestep_offset);								// timestep offset
	}	
	
	g_measurements_time = TCNT1;
}
void _f_nonzero_preirradiation_no_offset()
{
	extern uint16_t g_pre_irradiating_time;
	extern uint16_t g_samples_number;
	extern uint16_t g_measurements_time;
	extern uint16_t g_timestep_offset;
	extern uint8_t g_measurements_l[];
	extern uint8_t g_measurements_h[];
	
	uint16_t adc_converter = 0;
	uint16_t iterator = 0;
	
	// preirradiating
	PORTB = 0b00000001;												// turn on the light
	_delay_ms(g_pre_irradiating_time);								// irradiation time
	
	f_manage_timer_reset();
	PORTB = 0b00000000;												// turn off the light
	
	//start sampling
	for (iterator=0; iterator<g_samples_number; iterator++)
	{
		ADCSRA = ADCSRA | 0b01000000;								// ADC - start a conversion
		f_manage_till_adc_is_ready();
		
		adc_converter = ADC;										// read the measurement
		g_measurements_l[iterator] = adc_converter%256;				// write the result
		g_measurements_h[iterator] = adc_converter >> 8;			// write the result
		_delay_us(g_timestep_offset);								// timestep offset
	}
	
	g_measurements_time = TCNT1;
}

void _f_nonzero_preirradiation_nonzero_offset()
{
	extern uint16_t g_pre_irradiating_time;
	extern uint16_t g_irradiating_offset;
	extern uint16_t g_samples_number;
	extern uint16_t g_timestep_offset;
	extern uint16_t g_measurements_time;
	extern uint8_t g_measurements_l[];
	extern uint8_t g_measurements_h[];
	
	uint16_t adc_converter = 0;
	uint16_t iterator = 0;
	
	// preirradiating
	PORTB = 0b00000001;												// turn on the light
	_delay_ms(g_pre_irradiating_time);								// irradiation time
	
	f_manage_timer_reset();
	
	// start sampling
	for (iterator=0; iterator<g_irradiating_offset; iterator++)
	{
		ADCSRA = ADCSRA | 0b01000000;								// ADC - start a conversion
		f_manage_till_adc_is_ready();
		
		adc_converter = ADC;										// read the measurement
		g_measurements_l[iterator] = adc_converter%256;				// write the result
		g_measurements_h[iterator] = adc_converter >> 8;			// write the result
		_delay_us(g_timestep_offset);								// timestep offset
	}
	
	PORTB = 0b00000000;												// turn off the irradiating
	
	//continue the sampling
	for (iterator=g_irradiating_offset; iterator<g_samples_number; iterator++)
	{
		ADCSRA = ADCSRA | 0b01000000;								// ADC - start a conversion
		f_manage_till_adc_is_ready();
		
		adc_converter = ADC;										// read the measurement
		g_measurements_l[iterator] = adc_converter%256;				// write the result
		g_measurements_h[iterator] = adc_converter >> 8;			// write the result
		_delay_us(g_timestep_offset);								// timestep offset
	}
	
	g_measurements_time = TCNT1;
}

void f_manage_sampling(uint8_t command)
{
	extern uint16_t g_pre_irradiating_time;
	extern uint16_t g_irradiating_offset;
	
	// no preirradiation
	if (g_pre_irradiating_time == 0)
	{
		// no irradiation offset
		if (g_irradiating_offset == 0)
		{
			_f_no_preirradiation_no_offset();
		}
		else
		{
			_f_no_preirradiation_nonzero_offset();
		}	
	}
	else
	{
		// no irradiation offset
		if (g_irradiating_offset == 0)
		{
			_f_nonzero_preirradiation_no_offset();
		}
		else
		{
			_f_nonzero_preirradiation_nonzero_offset();
		}			
	}
}

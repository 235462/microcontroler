/*
 * main.h
 *
 * Created: 19.02.2023 16:54:56
 *  Author: Lenovo
 */ 

#include <avr/io.h>

#ifndef MAIN_H_
#define MAIN_H_

volatile uint16_t g_samples_number = 100;

volatile uint16_t g_timestep_offset = 4000;				// us
volatile uint16_t g_pre_irradiating_time = 1000;		// ms
volatile uint16_t g_irradiating_offset = 5;				// number of measurements

volatile uint16_t g_measurements_time;

volatile uint8_t g_measurements_l[950];
volatile uint8_t g_measurements_h[950];

	
#endif /* MAIN_H_ */
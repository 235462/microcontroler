/*
 * update.c
 *
 * Created: 19.02.2023 18:11:26
 *  Author: Lenovo
 */ 

#include <avr/io.h>
#include <math.h>

void f_manage_update_irradiating_offset(uint8_t command)
{
	extern uint16_t g_irradiating_offset;
	uint16_t replacement = (uint16_t)(command & 0b00001111);

	if ((command & 0b00110000) == 0b00110000)
	{
		g_irradiating_offset = (g_irradiating_offset & 0b1111111111110000) | replacement;
	} else if ((command & 0b00110000) == 0b00100000)
	{
		g_irradiating_offset = (g_irradiating_offset & 0b1111111100001111) | (replacement << 4);
	} else if ((command & 0b00110000) == 0b00010000)
	{
		g_irradiating_offset = (g_irradiating_offset & 0b1111000011111111) | (replacement << 8);
	}else if ((command & 0b00110000) == 0b00000000)
	{
		g_irradiating_offset = (g_irradiating_offset & 0b0000111111111111) | (replacement << 12);
	}
	
	return;
}

void f_manage_update_pre_irradiating_time(uint8_t command)
{
	extern uint16_t g_pre_irradiating_time;
	uint16_t replacement = (uint16_t)(command & 0b00001111);

	if ((command & 0b00110000) == 0b00110000)
	{
		g_pre_irradiating_time = (g_pre_irradiating_time & 0b1111111111110000) | replacement;
	} else if ((command & 0b00110000) == 0b00100000)
	{
		g_pre_irradiating_time = (g_pre_irradiating_time & 0b1111111100001111) | (replacement << 4);
	} else if ((command & 0b00110000) == 0b00010000)
	{
		g_pre_irradiating_time = (g_pre_irradiating_time & 0b1111000011111111) | (replacement << 8);
	}else if ((command & 0b00110000) == 0b00000000)
	{
		//g_pre_irradiating_time = (g_pre_irradiating_time & 0b0000111111111111) | (replacement << 12);
	}
	
	return;
}

void f_manage_update_samples_number(uint8_t command)
{
	extern uint16_t g_samples_number;
	uint16_t replacement = (uint16_t)(command & 0b00001111);

	if ((command & 0b00110000) == 0b00110000)
	{
		g_samples_number = (g_samples_number & 0b1111111111110000) | replacement;
	} else if ((command & 0b00110000) == 0b00100000)
	{
		g_samples_number = (g_samples_number & 0b1111111100001111) | (replacement << 4);
	} else if ((command & 0b00110000) == 0b00010000)
	{
		g_samples_number = (g_samples_number & 0b1111000011111111) | (replacement << 8);
	}
	
	return;
}

void f_manage_update_timestep_offset(uint8_t command)
{
	extern uint16_t g_timestep_offset;
	uint16_t replacement = (uint16_t)(command & 0b00001111);

	if ((command & 0b00110000) == 0b00110000)
	{
		g_timestep_offset = (g_timestep_offset & 0b1111111111110000) | replacement;
	} else if ((command & 0b00110000) == 0b00100000)
	{
		g_timestep_offset = (g_timestep_offset & 0b1111111100001111) | (replacement << 4);
	} else if ((command & 0b00110000) == 0b00010000)
	{
		g_timestep_offset = (g_timestep_offset & 0b1111000011111111) | (replacement << 8);
	}else if ((command & 0b00110000) == 0b00000000)
	{
		g_timestep_offset = (g_timestep_offset & 0b0000111111111111) | (replacement << 12);
	}
	
	return;
}

/*
 * update.h
 *
 * Created: 19.02.2023 18:11:37
 *  Author: Lenovo
 */ 


#ifndef UPDATE_H_
#define UPDATE_H_

void f_manage_update_irradiating_offset(uint8_t command);
void f_manage_update_pre_irradiating_time(uint8_t command);
void f_manage_update_samples_number(uint8_t command);
void f_manage_update_timestep_offset(uint8_t command);

#endif /* UPDATE_H_ */
/*
 * adc.h
 *
 * Created: 19.02.2023 18:09:01
 *  Author: Lenovo
 */ 


#ifndef ADC_H_
#define ADC_H_

void _f_no_preirradiation_no_offset();
void _f_no_preirradiation_nonzero_offset();
void _f_nonzero_preirradiation_no_offset();
void _f_nonzero_preirradiation_nonzero_offset();

void f_manage_sampling(uint8_t command);
void f_manage_till_adc_is_ready();

#endif /* ADC_H_ */
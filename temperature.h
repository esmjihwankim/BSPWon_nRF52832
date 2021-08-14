
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "nrfx_temp.h"
#include "helper.h"
#include "nrf_nvic.h"

void cpu_temp_init();
void cpu_temp_start_task(); 
int get_temperature(); 

#endif
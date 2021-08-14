#include "temperature.h"

int32_t volatile temp; 

/*@brief Sets register to enable temperature measurement
*/
void cpu_temp_init()
{
    nrf_temp_init(); 
    
    NRF_TEMP->INTENSET |= TEMP_INTENSET_DATARDY_Enabled; 
    NVIC_SetPriority(TEMP_IRQn, APP_IRQ_PRIORITY_LOW);
    NVIC_EnableIRQ(TEMP_IRQn); 
    
}


/*@brief Returns temperature value 
*/
void cpu_temp_start_task()
{
    NRF_TEMP->TASKS_START = 1;
}


void TEMP_IRQHandler()
{
    NRF_TEMP->EVENTS_DATARDY = 0;
    temp = (nrf_temp_read() / 4); 
    NRF_TEMP->TASKS_STOP = 1;
    //printf("TEMP:::%d", temp);
}

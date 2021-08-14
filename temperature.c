#include "temperature.h"

int32_t volatile temp; 

/*@brief Sets register to enable temperature measurement
*/
void temp_init()
{
    nrf_temp_init(); 
}

/*@brief Returns temperature value 
*/
int get_temperature()
{
    // Start Temperature Measurement 
    NRF_TEMP->TASKS_START = 1;
    temp = (nrf_temp_read() / 4);
    printf("Current Temperature: %d", (int)temp); 
    NRF_TEMP->TASKS_STOP = 1;

    return (int) temp; 
}


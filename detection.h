
#ifndef DETECTION_H
#define DETECTION_H

#include <stdbool.h>
#include <stdio.h>
#include "gpio_control.h"

int get_automatic_pulsing_state(void);
void set_automatic_pulsing_state(int value);

int sensor_detection(int u_val, int v_val, int w_val, int x_val, int y_val, int z_val); 

typedef enum Pulsing_Status 
{
    OFF_STATE = 0, 
    ADDUP_STATE = 1,
    AVERAGING_STATE = 2,
    SIGN_STATE = 2,
    END_STATE = 3 
}Pulsing_Status_t;


#endif
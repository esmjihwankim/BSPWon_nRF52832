
#ifndef DETECTION_H
#define DETECTION_H

#include <stdbool.h>
#include <stdio.h>
#include "gpio_control.h"

int get_automatic_pulsing(void);
void set_automatic_pulsing(int value);

int32_t sensor_detection(int u_val, int v_val, int w_val, int x_val, int y_val, int z_val); 

#endif
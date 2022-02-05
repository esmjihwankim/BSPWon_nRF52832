
#ifndef DETECTION_H
#define DETECTION_H

#include <stdbool.h>

int get_automatic_pulsing(void);
void set_automatic_pulsing(int value);

void detection_to_pulsing(int u_val, int v_val, int w_val, int x_val, int y_val, int z_val); 

#endif
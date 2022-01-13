#include "settings.h"

int automatic_pulsing_setting(int input)
{
    static int automatic_pulsing = 0; 
    if(input == 0 || input == 1) automatic_pulsing = input;
    return  automatic_pulsing;
}

int get_automatic_pulsing(void)
{     
    return automatic_pulsing_setting(2); 
}

void set_automatic_pulsing(int value)
{
    automatic_pulsing_setting(value); 
}
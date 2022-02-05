#include "detection.h"

/* @brief Interface to change the setting
*/ 
// 0
// 1
// 2
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



/*@brief provides detection and outputs pulses
@param
       u_val : strain index finger
       v_val : strain middle finger
       w_val : strain ring finger
       x_val : accelerometer x axis 
       y_val : accelerometer y axis 
       z_val : accelerometer z axis 
*/ 
void detection_to_pulsing(int u_val, int v_val, int w_val, int x_val, int y_val, int z_val)
{
    const int resting_time = 100; 
    const int sign_time = 200; 
    const int avg_deviation_range_strain = 100; 
    const int avg_deviation_range_acc = 50; 

    static bool state_straight_u = true;
    static bool state_straight_v = true;
    static bool state_straight_w = true;

    static bool state_avg_range_x = true;
    static bool state_avg_range_y = true;
    static bool state_avg_range_z = true;
    
    static int timestamp = 0;
    timestamp++;
    static int u_avg = 0, v_avg = 0, w_avg = 0, 
               x_avg = 0, y_avg = 0, z_avg = 0; 

    // Average Calculation 
    if(timestamp < 100)
    {
        u_avg += u_val; 
        v_avg += v_val; 
        w_avg += w_val; 
        x_avg += x_val; 
        y_avg += y_val; 
        z_avg += z_val;
    }
    else if(timestamp == 100) 
    {
        u_avg /= 100; 
        v_avg /= 100; 
        w_avg /= 100; 
        x_avg /= 100; 
        y_avg /= 100; 
        z_avg /= 100; 
    }
    else if(timestamp >= 100 && timestamp <= 300)
    {
        // u strain 
        if(u_val <= u_avg + avg_deviation_range_strain)
        {
            if(state_straight_u == false)
            {
                state_straight_u = true; 
                // u_pulse_straight();
            }
        }
        else 
        {
            if(state_straight_u == true) 
            {
                state_straight_u = false; 
                // u_pulse_bent();  
            }
        }

        // v strain 
        if(v_val <= v_avg + avg_deviation_range_strain)
        {
            if(state_straight_v == false)
            {
                state_straight_v = true; 
                // v_pulse_straight(); 
            }
        }
        else
        {
            if(state_straight_v == true) 
            {
                state_straight_v = false; 
                // v_pulse_bent();
            }
        }

        // w strain 
        if(w_val <= w_avg + avg_deviation_range_strain)
        {
            if(state_straight_w == false)
            {
                state_straight_w = true; 
                // w_pulse_straight(); 
            }
        }
        else 
        {
            if(state_straight_w == true)
            {
                state_straight_w = false; 
                // w_pulse_bent(); 
            }
        }

        // x acc axis - hits acceptable average range
        if(x_val <= (x_avg + avg_deviation_range_acc) && 
           x_val >= (x_avg - avg_deviation_range_acc)) 
        {
            if(state_avg_range_x == false)
            {
                state_avg_range_x = true; 
            }
        }
        else 
        {
            if(state_avg_range_x == true)
            {
                state_avg_range_x = false; 
                int derivative_x = x_val - x_avg; 
                if(derivative_x < 0);   // negative pulse 
                else if(derivative_x > 0);   // positive pulse
            }
        }

        // y acc axis 
        if(y_val <= (y_avg + avg_deviation_range_acc) && 
           y_val >= (y_avg - avg_deviation_range_acc))
        {
            if(state_avg_range_y == false) 
            {
                state_avg_range_y = true; 
            }
        }
        else
        {
            if(state_avg_range_y == true)
            {
                state_avg_range_y = false; 
                int derivative_y = y_val - y_avg; 
                if(derivative_y < 0);  // negative pulse 
                else if(derivative_y > 0);  // positive pulse 
            }
        }

        // z acc axis
        if(z_val <= (z_avg + avg_deviation_range_acc) && 
           z_val >= (z_avg - avg_deviation_range_acc))
        {
            if(state_avg_range_z == false) 
            {
                state_avg_range_z = true; 
            }
        }
        else 
        {
            if(state_avg_range_z == true) 
            {
                state_avg_range_z = false; 
                int derivative_z = z_val - z_avg; 
                if(derivative_z < 0); // negative pulse 
                else if(derivative_z > 0);  // positive pulse
            }
        }
        

    }
    else // initialize 
    {
        u_avg = 0;
        v_avg = 0; 
        w_avg = 0; 
        x_avg = 0; 
        y_avg = 0;
        z_avg = 0;

        state_straight_u = true;
        state_straight_v = true;
        state_straight_w = true;

        state_avg_range_x = true;
        state_avg_range_y = true;
        state_avg_range_z = true;
        automatic_pulsing_setting(0);
    }
}




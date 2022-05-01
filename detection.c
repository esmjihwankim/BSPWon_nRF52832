#include "detection.h"

/* @brief Interface to change the setting
*/ 


/**@brief Interface for modifying & checking pulsing state 
  *pulsing states should be accessed only by get/set functions
  */

int automatic_pulsing_setting(Pulsing_Status_t input)
{
    static Pulsing_Status_t state = 0; 
    if(input == OFF_STATE || input == ON_STATE) state = input;
    return state;
}

int get_automatic_pulsing_state(void)
{
    return automatic_pulsing_setting(-1); 
}

void set_automatic_pulsing_state(Pulsing_Status_t input)
{
    automatic_pulsing_setting(input); 
}


/**@brief provides detection and outputs pulses
@param
 *      u_val : strain index finger
 *      v_val : strain middle finger
 *      w_val : strain ring finger
 *      x_val : accelerometer x axis 
 *      y_val : accelerometer y axis 
 *      z_val : accelerometer z axis 
 */ 
int sensor_detection(int u_val, int v_val, int w_val, int x_val, int y_val, int z_val)
{
    const int resting_time = 60; 
    const int sign_time = 100;
    const int avg_deviation_range_strain = 300;
    const int avg_deviation_range_acc = 300;

    static bool state_straight_u = true;
    static bool state_straight_v = true;
    static bool state_straight_w = true;

    static bool state_avg_range_x = true;
    static bool state_avg_range_y = true;
    static bool state_avg_range_z = true;
    
    static int timestamp = 0;
    static int u_avg = 0, v_avg = 0, w_avg = 0, 
               x_avg = 0, y_avg = 0, z_avg = 0; 

    int32_t pulsing_info = 0x00; 
    
    if(timestamp == 0)
    {
        printf("addup state entered::stay still\n\r"); 
        send_log_via_bluetooth("stay still");
    }
    // Average Calculation 
    else if(timestamp < 100)
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
        printf("gesture state entered::perform gesture\n\r");
        send_log_via_bluetooth("perform gesture");
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
                printf("pulse_straight\n\r"); 
                give_pulse(1);
                pulsing_info += 0b100000000000; 
            }
        }
        else 
        {
            if(state_straight_u == true) 
            {
                state_straight_u = false; 
                printf("pulse_bent\n\r"); 
                give_pulse(2);
                pulsing_info += 0b010000000000;

            }
        }

        // v strain 
        if(v_val <= v_avg + avg_deviation_range_strain)
        {
            if(state_straight_v == false)
            {
                state_straight_v = true; 
                printf("v_pulse_straight\n\r"); 
                give_pulse(3);
                pulsing_info += 0b001000000000;

            }
        }
        else
        {
            if(state_straight_v == true) 
            {
                state_straight_v = false; 
                printf("v_pulse_bent\n\r"); 
                give_pulse(4);
                pulsing_info += 0b000100000000;
            }
        }

        // w strain : ring finger
        if(w_val <= w_avg + avg_deviation_range_strain)
        {
            if(state_straight_w == false)
            {
                state_straight_w = true; 
                printf("w_pulse_straight\n\r");
                give_pulse(5);
                pulsing_info += 0b000010000000;

            }
        }
        else 
        {
            if(state_straight_w == true)
            {
                state_straight_w = false; 
                printf("w_pulse_bent\n\r");
                give_pulse(6); 
                pulsing_info += 0b000001000000;
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
                if(derivative_x < 0) 
                { 
                    give_pulse(7);
                    printf("acc_x_negative_pulse\n\r");   // negative pulse 
                    pulsing_info += 0b000000100000; 
                }
                else if(derivative_x > 0) 
                {
                    give_pulse(8);
                    printf("acc_x_positive_pulse\n\r");   // positive pulse
                    pulsing_info += 0b000000010000; 
                }
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
                if(derivative_y < 0) 
                {
                    give_pulse(9);
                    printf("acc_y_negative_pulse\n\r");   // negative pulse 
                    pulsing_info += 0b000000001000; 
                }
                else if(derivative_y > 0)
                {
                    give_pulse(10);
                    printf("acc_y_positive_pulse\n\r");   // positive pulse 
                    pulsing_info += 0b000000000100;
                }
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
                if(derivative_z < 0) 
                {
                    give_pulse(11);
                    printf("acc_z_negative_pulse\n\r"); // negative pulse 
                    pulsing_info += 0b000000000010; 
                }
                else if(derivative_z > 0)
                { 
                    give_pulse(12);
                    printf("acc_z_positive_pulse\n\r");  // positive pulse
                    pulsing_info += 0b000000000001; 
                }
            }
        }
    }
    else // initialize 
    {
        printf("AUTOMATIC PULSING PERIOD FINISHED\n\r");
        send_log_via_bluetooth("done. ready.");
        timestamp = 0; 
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

        set_automatic_pulsing_state(OFF_STATE);
    }

    timestamp++;
    if(pulsing_info != 0) printf("%d\n\r", pulsing_info); 
    return pulsing_info; 
}




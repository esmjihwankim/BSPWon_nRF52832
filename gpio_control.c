#include "gpio_control.h"

BLE_NUS_DEF(m_nus, NRF_SDH_BLE_TOTAL_LINK_COUNT);   
static uint16_t   m_conn_handle          = BLE_CONN_HANDLE_INVALID;       
static uint32_t i;
int pulse_status = 0;
//int idle_loop = 124;
int idle_loop = 248;
int looper = 0;
int test_looper = 0;
//int* pulse_arr;

static int16_t buff = 1;
int pulse_no;
bool pulseSending = false;
bool pulse_complete = false;
bool pulseTesting = false;
bool testFinished = false;
void gpio_init(void)
{   
    // Initialize Control Pins
    nrf_gpio_cfg_output(PULSE_PIN_1);
    nrf_gpio_cfg_output(PULSE_PIN_2);
    nrf_gpio_cfg_output(TEST_PIN);
    // Turn off Control Pins
    nrf_gpio_pin_clear(PULSE_PIN_1);
    nrf_gpio_pin_clear(PULSE_PIN_2);
    nrf_gpio_pin_clear(TEST_PIN);
    app_timer_start(m_app_timer_id, PULSE_INTERVAL, NULL); // initialize the timer
    app_timer_start(pulse_test_id, TEST_INTERVAL, NULL); // initialize the timer
}

/* Turn on and off Control Pins */





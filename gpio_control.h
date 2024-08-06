
#ifndef _GPIO_CONTROL_H
#define _GPIO_CONTROL_H


#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_clock.h"
#include "helper.h"
#include "bluetooth.h"
#include "nrf_delay.h"
/*
GPIOs for Toggling Event : PIN_1, PIN_2
C:\NRF_SDK17_MAIN\nRF5_SDK_17.1.0_ddde560\examples\SOHN_LAB\ADC_TEST_6_16_2\gpio_control.h
GPIOs for Cascade Action : LED_PIN_1,LED_PIN_2,LED_PIN_3,LED_PIN_4,LED_PIN_5
*/

#define PULSE_PIN_1 31
#define PULSE_PIN_2 30
#define TEST_PIN 29
#define PULSE_INTERVAL APP_TIMER_TICKS(0.2)
#define TEST_INTERVAL APP_TIMER_TICKS(1)
extern bool pulseSending;
extern int pulse_status;
extern bool pulseTesting;
extern bool testFinished;
APP_TIMER_DEF(m_app_timer_id);
APP_TIMER_DEF(pulse_test_id);
void gpio_init(void);

//void pulse_com_idle(void);


#endif
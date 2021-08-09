
#ifndef _GPIO_CONTROL_H
#define _GPIO_CONTROL_H


#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_clock.h"
#include "helper.h"
#include "gpio_control.h"
/*
GPIOs for Toggling Event : PIN_1, PIN_2
GPIOs for Cascade Action : LED_PIN_1,LED_PIN_2,LED_PIN_3,LED_PIN_4,LED_PIN_5
*/

#define TOGGLE_PIN_1 12
#define TOGGLE_PIN_2 13

#define LED_PIN_1 12
#define LED_PIN_2 22
#define LED_PIN_3 23 
#define LED_PIN_4 24 
#define LED_PIN_5 25 
#define LED_INTERVAL APP_TIMER_TICKS(100)
APP_TIMER_DEF(m_app_timer_id);
void gpio_init(void);
void control_table(ble_nus_evt_t * p_evt);
void led_on(void); 
void led_off(void);
void led_cascade_on(void);
void led_cascade_off(void);
void led_toggle(void);
#endif
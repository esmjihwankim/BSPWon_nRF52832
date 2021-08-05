
#ifndef _GPIO_CONTROL_H
#define _GPIO_CONTROL_H


#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "helper.h"
#include "gpio_control.h"


#define LED_PIN_1 31


void gpio_init(void);
void control_table(ble_nus_evt_t * p_evt);
void led_on(void); 
void led_off(void);
void led_cascade(void);
void led_toggle(void);


#endif
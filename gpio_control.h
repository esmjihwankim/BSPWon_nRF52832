#ifndef _GPIO_CONTROL_H
#define _GPIO_CONTROL_H


#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_clock.h"
#include "helper.h"
#include "detection.h"

#define CONTROL_PIN_1 11
#define CONTROL_PIN_2 12
#define CONTROL_PIN_3 13
#define CONTROL_PIN_4 14

#define CASCADE_PIN_1 11
#define CASCADE_PIN_2 12
#define CASCADE_PIN_3 13
#define CASCADE_PIN_4 14
#define CASCADE_PIN_5 15

#define PULSE_PIN_1 4       // Strain Index Straight
#define PULSE_PIN_2 5       // Strain Index Bent 
#define PULSE_PIN_3 7       // Strain Middle Striaght 
#define PULSE_PIN_4 9       // Strain Middle Bent 
#define PULSE_PIN_5 11      // Strain Ring Straight
#define PULSE_PIN_6 12      // Strain Ring Bent 
#define PULSE_PIN_7 13      // Acc X Positive Swing 
#define PULSE_PIN_8 14      // Acc X Negative Swing 
#define PULSE_PIN_9 15      // Acc Y Positive Swing 
#define PULSE_PIN_10 22     // Acc Y Negative Swing 
#define PULSE_PIN_11 23     // Acc Z Positive Swing 
#define PULSE_PIN_12 24     // Acc Z Negative Swing 

#define CASCADE_INTERVAL APP_TIMER_TICKS(100)
#define PULSE_INTERVAL APP_TIMER_TICKS(50)

APP_TIMER_DEF(m_cascade_app_timer_id);

APP_TIMER_DEF(m_pulsing_ch1_timer_id);
APP_TIMER_DEF(m_pulsing_ch2_timer_id);
APP_TIMER_DEF(m_pulsing_ch3_timer_id);
APP_TIMER_DEF(m_pulsing_ch4_timer_id);
APP_TIMER_DEF(m_pulsing_ch5_timer_id);
APP_TIMER_DEF(m_pulsing_ch6_timer_id);
APP_TIMER_DEF(m_pulsing_ch7_timer_id);
APP_TIMER_DEF(m_pulsing_ch8_timer_id);
APP_TIMER_DEF(m_pulsing_ch9_timer_id);
APP_TIMER_DEF(m_pulsing_ch10_timer_id);
APP_TIMER_DEF(m_pulsing_ch11_timer_id);
APP_TIMER_DEF(m_pulsing_ch12_timer_id);
APP_TIMER_DEF(m_pulsing_ch13_timer_id);
APP_TIMER_DEF(m_pulsing_ch14_timer_id);


void timers_init(void);
void lfclk_config(void);
void gpio_init(void);
void control_table(ble_nus_evt_t * p_evt);
void led_on(void); 
void led_off(void);
void led_cascade_on(void);
void led_cascade_off(void);
void led_toggle(void);

void give_pulse(int pin_number); 


#endif
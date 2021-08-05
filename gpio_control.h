#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "helper.h"


void control_table(ble_nus_evt_t * p_evt);
void gpio_init();
void led_on(void); 
void led_off(void);
void led_cascade(void);
void led_toggle(void);
#include "gpio_control.h"


static uint32_t i;

void gpio_init(void)
{   
    nrf_gpio_cfg_output(LED_PIN_2); // Initialize the pin
    nrf_gpio_cfg_output(LED_PIN_3); // Initialize the pin
    nrf_gpio_cfg_output(LED_PIN_4); // Initialize the pin
    nrf_gpio_cfg_output(LED_PIN_5); // Initialize the pin
    nrf_gpio_pin_clear(LED_PIN_2); // Turn off the LED
    nrf_gpio_pin_clear(LED_PIN_3); // Turn off the LED
    nrf_gpio_pin_clear(LED_PIN_4); // Turn off the LED
    nrf_gpio_pin_clear(LED_PIN_5); // Turn off the LED
    nrf_gpio_cfg_output(LED_PIN_1);
    nrf_gpio_pin_clear(LED_PIN_1);
    uint32_t err_code = app_timer_start(m_app_timer_id, LED_INTERVAL, NULL); // initialize the timer
    
}


void control_table(ble_nus_evt_t * p_evt)
{
    int idx = 0;
    char buffer_rx[20] = "";
    if (p_evt->type == BLE_NUS_EVT_RX_DATA)
    {
        uint32_t err_code;
        NRF_LOG_DEBUG("Received data from BLE NUS. Writing data on UART.");
        NRF_LOG_HEXDUMP_DEBUG(p_evt->params.rx_data.p_data, p_evt->params.rx_data.length);
        for (uint32_t i = 0; i < p_evt->params.rx_data.length; i++)
        {
            do
            {
                err_code = app_uart_put(p_evt->params.rx_data.p_data[i]);
                
                if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
                {
                    NRF_LOG_ERROR("Failed receiving NUS message. Error 0x%x. ", err_code);
                    APP_ERROR_CHECK(err_code);
                }

            } while (err_code == NRF_ERROR_BUSY);
            if(p_evt->params.rx_data.p_data[i] == '<' || p_evt->params.rx_data.p_data[i] == '>') continue;
            buffer_rx[idx] = p_evt->params.rx_data.p_data[i];
            idx++;
        }
        if (p_evt->params.rx_data.p_data[p_evt->params.rx_data.length - 1] == '\r')
        {
            while (app_uart_put('\n') == NRF_ERROR_BUSY);
        }
        

        printf("\r\nCENTRAL RECEIVED MESSAGE:::%s\r\n", buffer_rx);

        // operate LED
        if(strcmp(buffer_rx, "LEDON") == 0) led_on(); 
        else if(strcmp(buffer_rx, "LEDOFF") == 0) led_off(); 
        else if(strcmp(buffer_rx, "LEDCASCADE")==0) led_cascade_on();
        else if(strcmp(buffer_rx, "LEDCASCADEOFF")==0) led_cascade_off();
    }
}
static void app_timer_handler(void * p_context)
{

  static uint32_t cascader_number; // remainder iteration variable
  static uint32_t cascader_pin_start; // start pin is 22 thus we add 22 to the iteration variable. 
  bool status1, status2, status3, status4; // returns pin state
  cascader_number = (i++) % 5; // there are 4 pins and one led_off timer which gives us 5 ticks in total. starting at 0 we increment i to give us remainder iteration. 
  cascader_pin_start = cascader_number + 22; // since there are consecutive 4 pins and the first pin starts at 22, we add the remainder 0 + 22 to start at pin 22
  status1 = nrf_gpio_pin_out_read(LED_PIN_2);
  status2 = nrf_gpio_pin_out_read(LED_PIN_3);
  status3 = nrf_gpio_pin_out_read(LED_PIN_4);
  status4 = nrf_gpio_pin_out_read(LED_PIN_5);
  nrf_gpio_pin_toggle(cascader_pin_start);
  if ((status1 == 1) && (status2 == 1) && (status3 == 1) && (status4 == 1))
    {
      nrf_gpio_pin_clear(LED_PIN_2); // Turn off the LED
      nrf_gpio_pin_clear(LED_PIN_3); // Turn off the LED
      nrf_gpio_pin_clear(LED_PIN_4); // Turn off the LED
      nrf_gpio_pin_clear(LED_PIN_5); // Turn off the LED
    }

}

void create_timer(void)
{
  ret_code_t err_code;
  err_code = app_timer_create(&m_app_timer_id, APP_TIMER_MODE_REPEATED, app_timer_handler);
    APP_ERROR_CHECK(err_code);    
}

/* LED Control Functions */
void led_on(void)
{
    printf("FUNC LED ON\r\n");
    nrf_gpio_pin_set(LED_PIN_1);
}

void led_off(void)
{
    printf("FUNC LED OFF\r\n");
    nrf_gpio_pin_clear(LED_PIN_1);
}

void led_cascade_on(void)
{
    printf("FUNC LED CASCADE ON\r\n");
    
    if (app_timer_cnt_get() == 0)
    {
      create_timer();
      printf("App Timer Value: %d\r\n",app_timer_cnt_get());
      app_timer_start(m_app_timer_id, LED_INTERVAL, NULL); // initialize the timer
    }
    else if(app_timer_cnt_get() > 0)
    {
      printf("App Timer Value: %d\r\n",app_timer_cnt_get());
      printf("LEDCASCADE HAS ALREADY STARTED\r\n");
    }
    
}
void led_cascade_off(void)
{
  printf("FUNC LED CASCADE OFF\r\n");
  if (app_timer_cnt_get() != 0)
  {
    app_timer_stop(m_app_timer_id);
    nrf_gpio_pin_clear(LED_PIN_2); // Turn off the LED
    nrf_gpio_pin_clear(LED_PIN_3); // Turn off the LED
    nrf_gpio_pin_clear(LED_PIN_4); // Turn off the LED
    nrf_gpio_pin_clear(LED_PIN_5); // Turn off the LED
    i = 0;
  }
}

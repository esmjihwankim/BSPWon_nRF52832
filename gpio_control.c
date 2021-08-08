#include "gpio_control.h"
static const nrf_drv_timer_t   TIMER_LED = NRF_DRV_TIMER_INSTANCE(3);


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
        else if(strcmp(buffer_rx, "LEDCASCADE")==0) led_cascade();
    }
}

static void timer_handler(nrf_timer_event_t event_type, void* p_context)
{
   static uint32_t i,x, val;
  bool status1, status2, status3, status4;
  
  val = (i++) % (5);
  x = val + 22;
  switch(event_type)
  {
    
    case NRF_TIMER_EVENT_COMPARE0:
    status1 = nrf_gpio_pin_out_read(LED_PIN_2);
    status2 = nrf_gpio_pin_out_read(LED_PIN_3);
    status3 = nrf_gpio_pin_out_read(LED_PIN_4);
    status4 = nrf_gpio_pin_out_read(LED_PIN_5);
    nrf_gpio_pin_toggle(x);
    if ((status1 == 1) && (status2 == 1) && (status3 == 1) && (status4 == 1))
    {
      nrf_gpio_pin_clear(LED_PIN_2); // Turn off the LED
      nrf_gpio_pin_clear(LED_PIN_3); // Turn off the LED
      nrf_gpio_pin_clear(LED_PIN_4); // Turn off the LED
      nrf_gpio_pin_clear(LED_PIN_5); // Turn off the LED
    }
    
    break;
    default:
    // Nothing
    break;
  }
}
void timer_init(void)
{
  uint32_t err_code = NRF_SUCCESS;

  uint32_t time_ms = 500;

  uint32_t time_ticks;

  nrf_drv_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG; // Configure the timer instance to default settings

  err_code = nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_handler); // Initialize the timer0 with default settings
  APP_ERROR_CHECK(err_code); // check if any error occured 

  time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms); // convert ms to ticks

  nrf_drv_timer_extended_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

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

void led_cascade(void)
{
    printf("FUNC LED CASCADE\r\n");
    nrf_drv_timer_enable(&TIMER_LED);
    
}
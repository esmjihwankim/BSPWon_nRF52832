#include "gpio_control.h"
#define PIN 00
#define BTN1 13
#define BTN2 14
#define LED 17
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
            if(buffer_rx[i] == '<' || buffer_rx[i] == '>') continue;
            buffer_rx[idx] = p_evt->params.rx_data.p_data[i];
            idx++;
        }
        if (p_evt->params.rx_data.p_data[p_evt->params.rx_data.length - 1] == '\r')
        {
            while (app_uart_put('\n') == NRF_ERROR_BUSY);
        }
        
        // operate LED
        if(strcmp(buffer_rx, "LEDOFF") == 0) led_on(); 
        else if(strcmp(buffer_rx, "LEDON") == 0) led_off(); 
        else if(strcmp(buffer_rx, "LEDCASCADE")==0) led_cascade();
    }
    
}
void gpio_init()
{
  nrf_gpio_cfg_output(PIN);
}

void led_on(void)
{

    nrf_gpio_pin_clear(PIN);
    
}
void led_off(void)
{

    nrf_gpio_pin_set(PIN);

}
void led_cascade(void)
{
    
}
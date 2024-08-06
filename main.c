#include "main.h"


/**@brief Application main function.

 */


int main(void)
{
    ret_code_t err_code;
    
    bool erase_bonds;
    bool saadc_enabled = false;
    //err_code = ble_dfu_buttonless_async_svci_init();
    // Initialize.
    gpio_init();
    uart_init();
    log_init();
    lfclk_config();
    timers_init();
    //buttons_leds_init(&erase_bonds);
    ble_stack_init();
    gap_params_init();
    gatt_init();
    services_init();
    twi_master_init();
    nrf_delay_ms(1000);
    
    advertising_init();
    
    err_code = sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, m_advertising.adv_handle, 0);
    APP_ERROR_CHECK(err_code);

    conn_params_init();
    
    
    while(mpu6050_init() == false)
    {
      printf("MPU_6050 initialization failed!!!"); 
      nrf_delay_ms(1000);
    }
    printf("MPU6050 Init Success");
    // Start execution.C:\NRF_SDK17_MAIN\nRF5_SDK_17.1.0_ddde560\examples\JOOJANGHOON_PROJ\TWI_TEST_2\main.c
    NRF_LOG_INFO("Debug logging for UART over RTT started.");
    sw_timer_init();
    advertising_start();

    for(;;){
      //sd_app_evt_wait();
    }


}


/**
 * @}
 */
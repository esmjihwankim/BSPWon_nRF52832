#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "app_timer.h"
#include "ble_nus.h"
#include "app_uart.h"
#include "app_util_platform.h"
#include "bsp_btn_ble.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_log.h"
#include "nrf_drv_twi.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
//C:\NRF_SDK17_MAIN\nRF5_SDK_17.1.0_ddde560\components\drivers_ext\mpu6050\mpu6050.c
#include "gpio_control.h"
#include "temperature.h"

/* DFU Specific */ 
#include "nrf_dfu_ble_svci_bond_sharing.h" 
#include "nrf_svci_async_function.h"
#include "nrf_svci_async_handler.h" 
#include "ble_dfu.h" 
#include "nrf_bootloader_info.h" 

#include "peer_manager_types.h"
#include "peer_manager_handler.h"
#include "fds.h"
#include "nrf_power.h"

APP_TIMER_DEF(i2c_ble_sampler_id);
#define FREQUENCY APP_TIMER_TICKS(1000)
#define SEC_PARAM_BOND                  1                                           /**< Perform bonding. */
#define SEC_PARAM_MITM                  0                                           /**< Man In The Middle protection not required. */
#define SEC_PARAM_LESC                  0                                           /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS              0                                           /**< Keypress notifications not enabled. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                        /**< No I/O capabilities. */
#define SEC_PARAM_OOB                   0                                           /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                           /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16       


/* Define */
#define APP_BLE_CONN_CFG_TAG            1                                           /**< A tag identifying the SoftDevice BLE configuration. */

#define DEVICE_NAME                     "BSPWON_PULSE"                           /**< Name of device. Will be included in the advertising data. */
#define NUS_SERVICE_UUID_TYPE           BLE_UUID_TYPE_VENDOR_BEGIN                  /**< UUID type for the Nordic UART Service (vendor specific). */

#define APP_BLE_OBSERVER_PRIO           3                                           /**< Application's BLE observer priority. You shouldn't need to modify this value. */

#define APP_ADV_INTERVAL                64                                          /**< The advertising interval (in units of 0.625 ms. This value corresponds to 40 ms). */

#define APP_ADV_DURATION                18000                                       /**< The advertising duration (180 seconds) in units of 10 milliseconds. */

#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(20, UNIT_1_25_MS)             /**< Minimum acceptable connection interval (20 ms), Connection interval uses 1.25 ms units. */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(75, UNIT_1_25_MS)             /**< Maximum acceptable connection interval (75 ms), Connection interval uses 1.25 ms units. */
#define SLAVE_LATENCY                   0                                           /**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(4000, UNIT_10_MS)             /**< Connection supervisory timeout (4 seconds), Supervision Timeout uses 10 ms units. */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000)                       /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000)                      /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3                                           /**< Number of attempts before giving up the connection parameter negotiation. */
#define BLE_NUS_BUFFER                  26
#define UART_TX_BUF_SIZE                256                                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE                256                                         /**< UART RX buffer size. */

#define SAADC_SAMPLES_IN_BUFFER         1
#define SAADC_SAMPLE_RATE               1      
#define SAADC_SAMPLE_RATE_ACTIVE        40                                     /**< SAADC sample rate in ms. */               
#ifndef AT24C02_H__
#define AT24C02_H__
#include "nrf_delay.h"

//I2C Pins Settings, you change them to any other pins
#define TWI_SCL_M           22         //I2C SCL Pin
#define TWI_SDA_M           23         //I2C SDA Pin


#define MPU6050_ADDRESS_LEN  1         //MPU6050
#define MPU6050_ADDRESS     (0xD0>>1)  //MPU6050 Device Address
#define MPU6050_WHO_AM_I     0x68U     //MPU6050 ID


#define MPU6050_GYRO_OUT        0x43
#define MPU6050_ACC_OUT         0x3B

#define ADDRESS_WHO_AM_I          (0x75U) //  WHO_AM_I register identifies the device. Expected value is 0x68.
#define ADDRESS_SIGNAL_PATH_RESET (0x68U) // 

//MPU6050 Registers addresseson -> https://pdf1.alldatasheet.com/datasheet-pdf/download/517744/ETC1/MPU-6050.html
#define MPU_SELF_TESTX_REG		0x0D	
#define MPU_SELF_TESTY_REG		0x0E	
#define MPU_SELF_TESTZ_REG		0x0F	
#define MPU_SELF_TESTA_REG		0x10	
#define MPU_SAMPLE_RATE_REG		0x19	
#define MPU_CFG_REG                     0x1A	
#define MPU_GYRO_CFG_REG		0x1B	
#define MPU_ACCEL_CFG_REG		0x1C	
#define MPU_MOTION_DET_REG		0x1F	
#define MPU_FIFO_EN_REG			0x23	
#define MPU_I2CMST_CTRL_REG		0x24	
#define MPU_I2CSLV0_ADDR_REG            0x25	
#define MPU_I2CSLV0_REG			0x26	
#define MPU_I2CSLV0_CTRL_REG            0x27	
#define MPU_I2CSLV1_ADDR_REG            0x28	
#define MPU_I2CSLV1_REG			0x29	
#define MPU_I2CSLV1_CTRL_REG            0x2A	
#define MPU_I2CSLV2_ADDR_REG            0x2B	
#define MPU_I2CSLV2_REG			0x2C	
#define MPU_I2CSLV2_CTRL_REG            0x2D	
#define MPU_I2CSLV3_ADDR_REG            0x2E	
#define MPU_I2CSLV3_REG			0x2F	
#define MPU_I2CSLV3_CTRL_REG            0x30	
#define MPU_I2CSLV4_ADDR_REG            0x31	
#define MPU_I2CSLV4_REG			0x32	
#define MPU_I2CSLV4_DO_REG		0x33	
#define MPU_I2CSLV4_CTRL_REG            0x34	
#define MPU_I2CSLV4_DI_REG		0x35	


#define MPU_PWR_MGMT1_REG		0x6B	
#define MPU_PWR_MGMT2_REG		0x6C	

#define MPU_I2CMST_STA_REG		0x36	
#define MPU_INTBP_CFG_REG		0x37	
#define MPU_INT_EN_REG			0x38	
#define MPU_INT_STA_REG			0x3A	

#define MPU_I2CMST_DELAY_REG            0x67	
#define MPU_SIGPATH_RST_REG		0x68	
#define MPU_MDETECT_CTRL_REG            0x69	
#define MPU_USER_CTRL_REG		0x6A	
#define MPU_PWR_MGMT1_REG		0x6B	
#define MPU_PWR_MGMT2_REG		0x6C	
#define MPU_FIFO_CNTH_REG		0x72	
#define MPU_FIFO_CNTL_REG		0x73	
#define MPU_FIFO_RW_REG			0x74	
#define MPU_DEVICE_ID_REG		0x75	


#endif


BLE_ADVERTISING_DEF(m_advertising);                                                 /**< Advertising module instance. */

void uart_init(void);
void buttons_leds_init(bool * p_erase_bonds);
void ble_stack_init(void);
void gap_params_init(void);
void gatt_init(void);
void services_init(void);
void conn_params_init(void);
void saadc_sampling_event_init(void);
void saadc_sampling_event_enable(void);
void advertising_start(void);
void saadc_init(void);
void pulse_saadc_active(void);
void advertising_init(void);
void sw_timer_init(void);


void twi_master_init(void); 
bool mpu6050_init(void);   
bool mpu6050_register_write(uint8_t register_address, const uint8_t value);
bool mpu6050_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes);
bool mpu6050_verify_product_id(void);
bool MPU6050_ReadGyro(int16_t *pGYRO_X , int16_t *pGYRO_Y , int16_t *pGYRO_Z );
bool MPU6050_ReadAcc( int16_t *pACC_X , int16_t *pACC_Y , int16_t *pACC_Z );


#endif
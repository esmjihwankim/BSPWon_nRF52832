# **BSPWon_nRF52**
![GitHub Logo](sensor.jpg)

## Project Overview
--------------------------------------------
> #### The objective of this project is to enable wireless communication among peripheral devices to receive and transmit data and commands. The NRF board provides a developer  environment where the user can manually configure low level application procedures, giving the creator freedom to manage the incoming and outgoing data. With this functional flexibility, the microprocessor can be programmed to transmit data at configured rates and also provide interrupts to execute commands at certain instances. Some key functions that will be implemented include:
>  * Wirelessly transmit data
>  * Receive transmitted data from peripheral
>  * Execute commands based on received data
----------------------------------------------

## *Data Transmission*
------------------------------------------
> #### The BLE microprocessor will be integrated into a bio-sensor circuit which will continuously return data based on its current environment. The processor will receive the sensor's data and wirelessly transmit them to a central device, where a UI will be implemented to display the receieved raw data. 
----------------------------------------

## *Recieve Data from Peripheral* 
--------------------------------------------
> #### Enabling bi-directional communication is paramount in effective communication. Along with transmitting data, the BLE chip must be able to receieve data sent by the peripheral device. The received data will automatically be parsed to a string data format. The received string data can trigger certain commands that are programmed into the chip.
--------------------------------------------

## *Command Execution* 
--------------------------------------------
> #### The BLE chip will be programmed to trigger certain actions based on the received string data of the peripheral device. Currently, the chip can execute two key commands:
> Single LED ON/OFF | Cascade Multiple LED's
> ----------------- | ----------------------
> LEDON: String data "LEDON", from the peripheral device will have the chip trigger the registered LED pin as high to turn on the LED. | LEDCASCADE: String data "LEDCASCADE", > > from peripheral device will have the chip trigger multiple pins consecutively based on the timer frequency. 
> LEDOFF: String data "LEDOFF", from the peripheral device will have the chip trigger the registered LED pin as low to turn off the LED. | LEDCASCADEOFF: String data "LEDCASCADEOFF", from peripheral device will have the chip set all of the registered pins to LOW. 
--------------------------------------------

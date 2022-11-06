/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "BLEDevice.h"
#include "UARTService.h"
#include "nrf_temp.h"

#define MAX_REPLY_LEN           (UARTService::BLE_UART_SERVICE_MAX_DATA_LEN)
#define SENSOR_READ_INTERVAL_S  (0.05F) 
#define ADV_INTERVAL_MS         (1000UL)
#define UART_BAUD_RATE          (9600UL)
#define DEVICE_NAME             ("DEMO SENSOR 1") // This can be read AFTER connecting to the device.
#define SHORT_NAME              ("MODULO1")    // Keep this short: max 8 chars if a 128bit UUID is also advertised.

#define DEBUG(...)              { pc.printf(__VA_ARGS__); }


BLEDevice   m_ble;
Serial      pc(USBTX, USBRX);  // TX pin, RX pin
DigitalOut  m_cmd_led(LED1);
DigitalOut  m_error_led(LED2);
AnalogIn    m_analog_in(p1);
uint16_t    m_analog_in_value,m_analog_in_value1,m_analog_in_value2,m_analog_in_value3,m_analog_in_value4;
UARTService *m_uart_service_ptr;


/**
 * This callback is used whenever a disconnection occurs.
 */
void disconnectionCallback(Gap::Handle_t handle, Gap::DisconnectionReason_t reason)
{
    switch (reason) {
    case Gap::REMOTE_USER_TERMINATED_CONNECTION:
        DEBUG("Disconnected (REMOTE_USER_TERMINATED_CONNECTION)\n\r");
        break;
    case Gap::LOCAL_HOST_TERMINATED_CONNECTION:
        DEBUG("Disconnected (LOCAL_HOST_TERMINATED_CONNECTION)\n\r");
        break;
    case Gap::CONN_INTERVAL_UNACCEPTABLE:
        DEBUG("Disconnected (CONN_INTERVAL_UNACCEPTABLE)\n\r");
        break;
    }

   // DEBUG("Restarting the advertising process\n\r");
    m_ble.startAdvertising();
}


/**
 * This callback is used whenever the host writes data to one of our GATT characteristics.
 */
void dataWrittenCallback(const GattCharacteristicWriteCBParams *params)
{
    // Ensure that initialization is finished and the host has written to the TX characteristic.
    if ((m_uart_service_ptr != NULL) && (params->charHandle == m_uart_service_ptr->getTXCharacteristicHandle())) {
        uint8_t  buf[MAX_REPLY_LEN];
        uint32_t len = 0;

        if (1 == params->len) {
            switch (params->data[0]) {
        
            case 'a':
                len = snprintf((char*) buf, MAX_REPLY_LEN, "%d", m_analog_in_value);
                break;
            case 'b':
                len = snprintf((char*) buf, MAX_REPLY_LEN, "%d", m_analog_in_value1);
                break;
            case 'c':
                len = snprintf((char*) buf, MAX_REPLY_LEN, "%d", m_analog_in_value2);
                break;
            case 'd':
                len = snprintf((char*) buf, MAX_REPLY_LEN, "%d", m_analog_in_value3);
                break;
           /* case 'e':
                len = snprintf((char*) buf, MAX_REPLY_LEN, "%d", m_analog_in_value4);
                break;*/    
            default:
                len = snprintf((char*) buf, MAX_REPLY_LEN, "ERROR: Unknown char");
                break;
            }
        }
        else
        {
            len = snprintf((char*) buf, MAX_REPLY_LEN, "ERROR: Invalid len");
        }

        m_ble.updateCharacteristicValue(m_uart_service_ptr->getRXCharacteristicHandle(), buf, len);

        //DEBUG("%d bytes received from host\n\r", params->len);
    }
}


/**
 * This callback is used whenever a write to a GATT characteristic causes data to be sent to the host.
 */
void dataSentCallback(unsigned count)
{
    // NOTE: The count always seems to be 1 regardless of data.
    //DEBUG("%d bytes sent to host\n\r", count);
}


int sensor(){
    DEBUG("1");
    int n=10;
    int v[n],c=0;
    int x;
    //uint16_t m;
    while(c<n){
        //m=m_serial_port.getc();
        if(pc.readable()){
        v[c]=pc.getc();
        DEBUG("%d",v[c]);
        c++;}}
        c=0;
    if(c==0){
        if(v[1]==0){
        x=v[0];
        return x;
        }}
       else
         return 90;
}

int sensor1(){
    DEBUG("2");
    int n=10;
    int v[n],c=0;
    int x;
    //uint16_t m;
    while(c<n){
        //m=m_serial_port.getc();
        if(pc.readable()){
        v[c]=pc.getc();
        c++;}}
        c=0;
    if(c==0){
        if(v[3]==1){
        x=v[2];
        return x;
        }}
       else
         return 90;
}

int sensor2(){
    DEBUG("3");
    int n=10;
    int v[n],c=0;
    int x;
    //uint16_t m;
    while(c<n){
        //m=m_serial_port.getc();
        if(pc.readable()){
        v[c]=pc.getc();
        c++;}}
        c=0;
    if(c==0){
        if(v[5]==2){
        x=v[4];
        return x;
        }}
       else
         return 90;
}

int sensor3(){
    //DEBUG("1");
    int n=10;
    int v[n],c=0;
    int x;
    //uint16_t m;
    while(c<n){
        //m=m_serial_port.getc();
        if(pc.readable()){
        v[c]=pc.getc();
        c++;}}
        c=0;
    if(c==0){
        if(v[7]==3){
        x=v[6];
        return x;
        }}
       else
         return 90;
}

int sensor4(){
    //DEBUG("1");
    int n=10;
    int v[n],c=0;
    int x;
    //uint16_t m;
    while(c<n){
        //m=m_serial_port.getc();
        if(pc.readable()){
        v[c]=pc.getc();
        c++;}}
        c=0;
    if(c==0){
        if(v[9]==4){
        x=v[8];
        return x;
        }}
       else
         return 90;
}


/**
 * This callback is scheduled to be called periodically via a low-priority interrupt.
 */
void periodicCallback(void)
{
    //m_analog_in_value = m_analog_in.read_u16();
    m_analog_in_value = sensor();
    m_analog_in_value1 = sensor1();
    m_analog_in_value2 = sensor2();
   /* m_analog_in_value3 = sensor3();
    /*m_analog_in_value4 = sensor4();*/
    
}


void error(ble_error_t err, uint32_t line)
{
    m_error_led = 1;
   // DEBUG("Error %d on line number %d\n\r", err, line);
}



int main(void)
{
    ble_error_t err;
    Ticker      ticker;

    pc.baud(UART_BAUD_RATE);

    DEBUG("a");

    m_cmd_led      = 0;
    m_error_led    = 0;
    m_analog_in_value    = 0;

    ticker.attach(periodicCallback, SENSOR_READ_INTERVAL_S);
DEBUG("b");
    m_ble.init();
    DEBUG("c");
    m_ble.onDisconnection(disconnectionCallback);
    DEBUG("d");
    m_ble.onDataWritten(dataWrittenCallback);
    m_ble.onDataSent(dataSentCallback);

    // Set the TX power in dBm units.
    // Possible values (in decreasing order): 4, 0, -4, -8, -12, -16, -20.
    err = m_ble.setTxPower(4);
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    // Setup advertising (GAP stuff).
    err = m_ble.setDeviceName(DEVICE_NAME);
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    err = m_ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED);
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    m_ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);

    err = m_ble.accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,
                                                (const uint8_t *)SHORT_NAME,
                                                (sizeof(SHORT_NAME) - 1));
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }
DEBUG("b");
    err = m_ble.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_128BIT_SERVICE_IDS,
                                                (const uint8_t *)UARTServiceUUID_reversed,
                                                sizeof(UARTServiceUUID_reversed));
    if (BLE_ERROR_NONE != err) {
        error(err, __LINE__);
    }

    m_ble.setAdvertisingInterval(Gap::MSEC_TO_ADVERTISEMENT_DURATION_UNITS(ADV_INTERVAL_MS));
    m_ble.startAdvertising();

    // Create a UARTService object (GATT stuff).
    UARTService uartService(m_ble);
    m_uart_service_ptr = &uartService;
DEBUG("c");
static uint8_t rx_buf[20];
static uint8_t rx_len=0;

    while (1) {
        DEBUG("d");
        //m_ble.waitForEvent();
    }
}

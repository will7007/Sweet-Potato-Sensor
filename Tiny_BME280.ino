//Run this at 8Mhz
#include <TinyBME280.h>
#include <TinyWireM.h>
#include <VirtualWire.h>

int32_t  temperature = 0;

const int BME280address = 119;

void setup() {
//  //OSCCAL = 0x8B; //9600 baud at 1Mhz
  TinyWireM.begin(); //must include this for the BME280 to work!
  BME280setup();

    // Initialize the IO and ISR
    vw_set_tx_pin(3);
    //vw_set_rx_pin(receive_pin);
    //vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec

    TinyWireM.beginTransmission(BME280address);
    TinyWireM.write(0xF4);                             // ctrl_meas
    TinyWireM.write(0b00100101);                       // Forced mode
    TinyWireM.endTransmission();
}

void loop() {
    temperature = BME280temperature();

    byte txLength = sizeof(temperature);
    byte txBuffer[txLength] = {0};
    memcpy(txBuffer, &temperature, txLength); 

    vw_send((uint8_t *)txBuffer, txLength); //buffer must be reversed upon being received to get the right integer, and maybe a /0 needs to be added to to stop the newline?
    vw_wait_tx();

    delay(5000);
}

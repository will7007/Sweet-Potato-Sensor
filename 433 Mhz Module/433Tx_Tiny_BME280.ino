//Runs at 1Mhz
#include <TinyBME280.h>
#include <TinyWireM.h>
#include <Manchester.h>

int32_t  temperature, tempMSB, tempLSB, humidity = 0;
const int BME280address = 119;

void setup() {
    TinyWireM.begin(); //must include this for the BME280 to work!
    BME280setup();
    man.setupTransmit(4, MAN_1200);
}

void loop() {
    forcedMode(); //turns off pressure measurement
    temperature = BME280temperature();
    tempMSB = temperature/100; //8 bit, for Manchester (TEMP)
    man.transmit(tempMSB);
    delay(1000);
    tempLSB = temperature % 100; //8 bit, for Manchester (TEMP)
    man.transmit(tempLSB);
    delay(1000);
    humidity = BME280humidity();
    humidity = humidity/100;
    man.transmit(humidity);
    delay(2000);
    
}

void forcedMode() { //tell the sensor to take a reading and then go back to sleep
    TinyWireM.beginTransmission(BME280address); 
    TinyWireM.write(0xF4);                             // ctrl_meas
    TinyWireM.write(0b00100001);                       // Temp sampling 1, pressure sampling 0 (no reading), forced mode
    TinyWireM.endTransmission();
    delay(100); //a built-in delay to give the sensor time to read the value and go to sleep again
}

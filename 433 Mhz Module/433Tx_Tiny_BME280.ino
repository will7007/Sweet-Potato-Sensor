//Works at 1Mhz
#include <TinyWireM.h>
#include <Manchester.h>
#include "CORE_BME280_I2C.h"
 
BME280_I2C sensebme; // Set to used address 0x77 as default // or BME280_I2C bme(0x76); // I2C using address 0x76
 
void setup() {
 man.setupTransmit(4, MAN_1200);

 
if (!sensebme.begin()) {while (1);}
}
 
void loop() {
sensebme.readSensor();
man.transmit((int)sensebme.getTemperature_F());
man.transmit((int)sensebme.getHumidity());
delay(3000); 
}

void forcedMode() { //tell the sensor to take a reading and then go back to sleep
    TinyWireM.beginTransmission(119); 
    TinyWireM.write(0xF4);                             // ctrl_meas
    TinyWireM.write(0b00100010);                       // Temp sampling 1, pressure sampling 0 (no reading), forced mode
    TinyWireM.endTransmission();
    delay(100); //a built-in delay to give the sensor time to read the value and go to sleep again
}

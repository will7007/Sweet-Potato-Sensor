//Works at 1Mhz
#include <TinyWireM.h>
#include <Manchester.h>
#include "CORE_BME280_I2C.h"
 
BME280_I2C sensebme;
const int sensorAddress = 0xA;
int temp, humid = 0;
 
void setup() {
 man.setupTransmit(4, MAN_300);

if (!sensebme.begin()) {while (1);}
}
 
void loop() {
  sensebme.readSensor();
  temp = (int)sensebme.getTemperature_F();
  humid = (int)sensebme.getHumidity();
  
  man.transmit(0xAA);
  delay(500);
  man.transmit(sensorAddress);
  delay(500);
  man.transmit(0xBB);
  delay(500);
  man.transmit(temp);
  delay(500);
  man.transmit(0xCC);
  delay(500);
  man.transmit(humid);
  
  delay(1000); 
}

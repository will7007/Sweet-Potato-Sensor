//Works at 1Mhz
#include <TinyWireM.h>
#include <Manchester.h>
#include "CORE_BME280_I2C.h"

//0: Reserved
//1: Address
//2: Temperature
//3: Humidity
//4: EOF
//5: Sensor error
//6: Nominal temp/humidity, even address following (we may only need one of these if there is a checksum in a data array)
//7: Nominal temp/humidity, odd address following
//8: Low battery voltage
//9: Reserved
  
BME280_I2C sensebme;
const uint8_t ADDRESS = 10;
const uint8_t LENGTH = 4;
//int temp, humid = 0;
uint8_t data[4] = {LENGTH, ADDRESS, 1, 2}; //the first spot in the data array must be the packet length for the message to send
 
void setup() {
  man.setupTransmit(4, MAN_300);
  pinMode(3,INPUT);

  if (!sensebme.begin()) {
    while(1){
    man.transmit(5);
    delay(50);
    }
  }
}
 
void loop() {
  sensebme.readSensor();
  data[2] = (int)sensebme.getTemperature_F();
  data[3] = (int)sensebme.getHumidity();

  if(data[2] <= 9) data[2] = 10;
  if(data[3] <= 9) data[3] = 10;

  man.transmitArray(LENGTH,data); //remember: datalength does not correspond to array indecies (send spot 0 and spot 1 == datalength of 2)
  if(!(digitalRead(3))) delay(5000);
}

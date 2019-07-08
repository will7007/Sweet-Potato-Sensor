//For an AtTiny85 @ 1Mhz
#include <Manchester.h>
#include "CORE_BME280_I2C.h"
#include "tinysnore.h"


//Transmission "abreviations" (the address of the sender will follow one of these messages, and possibly following this address will be a value
//One of these will always be in the second slot of the transmission array (after the message length), or after the conclusion of another device's data in a repackaged array

//0: No error
//1: Temperature outside threshold (followed by address and temperature)
//2: Humidity outside threshold (followed by address and humidity)
//3: Temperature AND humidity outside threshold (followed by address, temperature, then humidity)
//4: Low battery voltage (followed by address and voltage level)
//5: Sensor error (not responding)
  
BME280_I2C sensebme;
const uint8_t ADDRESS = 10;
const uint8_t LENGTH = 4;

uint8_t data[4] = {LENGTH, ADDRESS, 0, 0}; //the first spot in the data array must be the packet length for the message to send
 
void setup() {
  man.setupTransmit(4, MAN_300);
  pinMode(3,INPUT);

  if (!sensebme.begin()) {
    while(1){
    man.transmit(5);
    delay(100);
    }
  }
}
 
void loop() {
  sensebme.readSensor();
  
  data[2] = (int)sensebme.getTemperature_F();
  data[3] = (int)sensebme.getHumidity();

  man.transmitArray(LENGTH,data); //remember: datalength does not correspond to array indecies (send spot 0 and spot 1 == datalength of 2)
  
  if(!(digitalRead(3))) snore(8000);
  else snore(1000);
}

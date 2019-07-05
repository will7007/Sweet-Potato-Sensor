#include <Manchester.h>
#include "CORE_BME280_I2C.h"

const int BUTTON = 1; //button pin
const int ADDRESS = 60;
const int LENGTH = 4;

uint8_t buffer[LENGTH];
uint8_t transmitBuffer[7] = {7,ADDRESS,1,2,6,7,8};
BME280_I2C sensebme;

void setup() {
//  man.workAround1MhzTinyCore(); DO NOT USE THIS FUNCTION! It makes the program transmit too fast
  man.setupReceive(4, MAN_300);
  man.setupTransmit(3, MAN_300);
  man.beginReceiveArray(LENGTH, buffer);

  pinMode(BUTTON,OUTPUT);

  if (!sensebme.begin()) {
    while(1) {
      man.transmit(5);
      delay(100);
    }
  }
}
 
void loop() {
  if (man.receiveComplete()) { //|| digitalRead(BUTTON)
    man.stopReceive(); 
    delay(100);

    transmitBuffer[4] = buffer[1]; //address
    transmitBuffer[5] = buffer[2]; //temp
    transmitBuffer[6] = buffer[3]; //humidity

    sensebme.readSensor();
    
    transmitBuffer[2] = (int)sensebme.getTemperature_F();
    transmitBuffer[3] = (int)sensebme.getHumidity();

    if(transmitBuffer[2] <= 9) transmitBuffer[2] = 10;
    if(transmitBuffer[3] <= 9) transmitBuffer[3] = 10;

    man.transmitArray(7,transmitBuffer);

    man.beginReceiveArray(LENGTH, buffer);
  }
}

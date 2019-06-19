//Works at 1Mhz
#include <TinyWireM.h>
#include <Manchester.h>
#include "CORE_BME280_I2C.h"

BME280_I2C sensebme;
const int ADDRESS = 0xA;
uint16_t buffering[7] = {0,0,0,0,0,0,0}; 
int temp, humid, receive, counter = 0;
 
void setup() {
  man.setupTransmit(4, MAN_300);
//  man.setupReceive(3, MAN_300);
//  man.beginReceive();

  if (!sensebme.begin()) {
    while(1){
    man.transmit(5);
    delay(10);
    }
  }
}
 
void loop() {
  sensebme.readSensor();
  temp = (int)sensebme.getTemperature_F();
  humid = (int)sensebme.getHumidity();

  if(temp <= 5) temp = 6;
  if(humid <= 5) humid = 6;
  
  man.transmit(1); //hex values sent out seem to cause issues on the receiving end,
  delay(200);      //particularly when printing out what is received to the serial monitor
  man.transmit(ADDRESS);
  delay(200);
  man.transmit(2);
  delay(200);
  man.transmit(temp);
  delay(200);
  man.transmit(3); //0xCC
  delay(200);
  man.transmit(humid);
  delay(200);
  man.transmit(4);

//  while(receive != 4) {
//    if (man.receiveComplete()) {
//      receive = man.getMessage();
//      buffering[counter] = receive;
//      counter++;
//      man.beginReceive();
//    }
//    if (counter > 6) counter = 0;
//  }
//
//  for(int i = 0;i <= 6; i++) man.transmit(buffering[i]);
//  
//  counter = 0;
//  receive = 0;
//  delay(500); 
}

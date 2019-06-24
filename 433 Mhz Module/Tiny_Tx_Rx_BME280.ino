#include <Manchester.h>
#include "CORE_BME280_I2C.h"

uint16_t buffering[7] = {0,0,0,0,0,0,0}; 
int temp,humid,counter = 0;
const int BUTTON = 1; //button pin
const int ADDRESS = 60;
BME280_I2C sensebme;

void setup() {
  man.setupReceive(4, MAN_300);
  man.setupTransmit(3, MAN_300);
  man.beginReceive();

//  pinMode(LED,OUTPUT); //led
  pinMode(BUTTON,INPUT);

  if (!sensebme.begin()) {
    while(1) {
    man.transmit(5);
    delay(10);
    }
  }
}
 
void loop() {
  if (man.receiveComplete()) {
    buffering[counter] = man.getMessage();
    counter++;
    man.beginReceive();
  }
  
  if (counter > 6) {
    counter = 0;
//    digitalWrite(LED, HIGH);
  }
  
  if (digitalRead(BUTTON)) {
    man.stopReceive(); //must include this to transmit
    
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
    man.transmit(3);
    delay(200);
    man.transmit(humid);
    delay(200);
    man.transmit(4);
    delay(200);
    
    for(int i = 0;i <= 6; i++) man.transmit(buffering[i]);
    
//    digitalWrite(LED,LOW);
    counter = 0;
    man.beginReceive();
  }
}
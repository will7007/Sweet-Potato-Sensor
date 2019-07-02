#include <Manchester.h>
#include "CORE_BME280_I2C.h"

uint16_t buffering[7] = {0,0,0,0,0,0,0}; 
int temp,humid,counter = 0;
bool eof = false;

const int BUTTON = 1; //button pin
const int ADDRESS = 60;

BME280_I2C sensebme;

void setup() {
  man.setupReceive(4, MAN_300);
  man.setupTransmit(3, MAN_300);
  man.beginReceive();

  pinMode(BUTTON,INPUT);

  if (!sensebme.begin()) {
    while(1) {
    man.transmit(5);
    delay(100);
    }
  }
}
 
void loop() {
  if (man.receiveComplete()) {
    buffering[counter] = man.getMessage();
    if(buffering[counter] == 4) eof = true;
    counter++;
    man.beginReceive();
    
  }
  
  if (counter > 6) counter = 0;
  
  if (digitalRead(BUTTON) || eof) {
    man.stopReceive(); //must include this to transmit

    sensebme.readSensor();
    temp = (int)sensebme.getTemperature_F();
    humid = (int)sensebme.getHumidity();

    if(temp <= 5) temp = 6;
    if(humid <= 5) humid = 6;

    if(eof) delay(1000); //extra delay for auto-send
    
    man.transmit(1); //hex values sent out seem to cause issues on the receiving end,
    delay(50);      //particularly when printing out what is received to the serial monitor
    man.transmit(ADDRESS);
    delay(50);
    man.transmit(2);
    delay(50);
    man.transmit(temp);
    delay(50);
    man.transmit(3);
    delay(50);
    man.transmit(humid);
    delay(50);
    man.transmit(4);
    delay(50);
    
    for(int i = 0;i <= 6; i++) {
      man.transmit(buffering[i]);
      delay(50); //not sure we even need this delay but we might as well include it just in case
    }
    
    counter = 0;
    eof = false;
    man.beginReceive();
  }
}

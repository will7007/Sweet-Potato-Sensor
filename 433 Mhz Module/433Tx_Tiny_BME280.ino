//Works at 1Mhz
#include <TinyWireM.h>
#include <Manchester.h>
#include "CORE_BME280_I2C.h"

BME280_I2C sensebme;
const int ADDRESS = 10;
int temp, humid = 0;
 
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
  temp = (int)sensebme.getTemperature_F();
  humid = (int)sensebme.getHumidity();

  if(temp <= 9) temp = 10;
  if(humid <= 9) humid = 10;

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
    delay(50); //these might be lowered to 0 but I am not 100% sure that would be wise
    
    if(!(digitalRead(3))) delay(5000);
}

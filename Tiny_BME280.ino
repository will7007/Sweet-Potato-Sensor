//#include <SoftwareSerial.h> //DOES NOT WORK AT 1MHZ
#include <TinyBME280.h> //worked at 8mhz
#include <TinyWireM.h>
//SoftwareSerial SSerial(4,3);

int32_t  temp = 0;
int32_t  tempTemp = 0;

void setup() {
  //OSCCAL = 0x8B; //9600 baud at 1Mhz
  TinyWireM.begin(); //must include this for the BME280 to work!
  //SSerial.begin(300);
  BME280setup();
  pinMode(4,OUTPUT); //RED
  pinMode(3,OUTPUT); //Green?
  pinMode(1,OUTPUT); //Blue?
}

void loop() {
  temp = BME280temperature();
//  if((lastTemp-temp) > 10 || (lastTemp-temp) < -10 ) digitalWrite(4,HIGH); //2250 in here?
//  else digitalWrite(4,LOW);

tempTemp = temp/1000;
for (int i = tempTemp;i>0;i--) {
  digitalWrite(4,HIGH);
  delay(1500);
  digitalWrite(4,LOW);
  delay(1500);
}
tempTemp = (temp - (temp/1000)*1000)/100;
for (int i = tempTemp;i>0;i--) {
  digitalWrite(3,HIGH);
  delay(1500);
  digitalWrite(3,LOW);
  delay(1500);
}
//
//tempTemp = (temp - ((temp - 2000))/10);
//for (int i = tempTemp; i>=0; i--) {
//  digitalWrite(1,HIGH);
//  delay(1000);
//  digitalWrite(1,LOW);
//  delay(1000);
//}

//temp -= 2200;
//  if (temp > 0 && temp < 10) {
//    digitalWrite(4,LOW);
//    digitalWrite(3,LOW);
//    digitalWrite(1,LOW);
//  }
//  else if (temp > 10 && temp < 20) { //the sensor was right on the edge of blue and green during testing (22 and 23 degrees) It seemed to be about 22.1 or 22.2 when doing 0.1 degree tests
//    digitalWrite(4,LOW);
//    digitalWrite(3,LOW);
//    digitalWrite(1,HIGH);    
//  }
//  else if (temp > 20 && temp < 30) { 
//    digitalWrite(4,LOW);
//    digitalWrite(3,HIGH);
//    digitalWrite(1,LOW);    
//  }
//  else if (temp > 30 && temp < 40) {
//    digitalWrite(4,LOW);
//    digitalWrite(3,HIGH);
//    digitalWrite(1,HIGH);    
//  }
//  else if (temp > 40 && temp < 40) {
//    digitalWrite(4,HIGH);
//    digitalWrite(3,LOW);
//    digitalWrite(1,LOW);    
//  }
//  else if (temp > 50 && temp < 60) {
//    digitalWrite(4,HIGH);
//    digitalWrite(3,LOW);
//    digitalWrite(1,HIGH);    
//  }
//  else if (temp > 60 && temp < 70) {
//    digitalWrite(4,HIGH);
//    digitalWrite(3,HIGH);
//    digitalWrite(1,LOW);    
//  }
//   else /*if (temp > 2700 && temp < 2800)*/ {
//    digitalWrite(4,HIGH);
//    digitalWrite(3,HIGH);
//    digitalWrite(1,HIGH);    
//  }
  delay(10000);
}

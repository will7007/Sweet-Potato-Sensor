#include <Manchester.h>

/*
Manchester Receiver example
  In this example receiver will receive one 16 bit number per transmittion
Try different speeds using this constants, your maximum possible speed will 
  depend on various factors like transmitter type, distance, microcontroller speed, ...
  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7
*/
int dataNumber = 0;

#define RX_PIN 12
void setup() {
  Serial.begin(9600);
  man.setupReceive(RX_PIN, MAN_300);
  man.beginReceive();
    pinMode(13,OUTPUT);
    pinMode(12,INPUT);
    pinMode(10,OUTPUT);
  
    digitalWrite(13,HIGH);
    digitalWrite(10,LOW);
}

void loop() {
  if (man.receiveComplete()) {
    uint16_t m = man.getMessage();
    if(dataNumber == 0) {Serial.print("Address: "); Serial.println(m); dataNumber = 1;}
    else if(dataNumber == 1) {Serial.print("Temperature: "); Serial.print(m); Serial.println(" F"); dataNumber = 2;}
    else {Serial.print("Humidity: "); Serial.print(m); Serial.println("%"); Serial.println(); dataNumber = 0;}
    //dataNumber++;
    man.beginReceive(); //start listening for next message right after you retrieve the message
  }
  if(dataNumber >= 3) dataNumber = 0;
}

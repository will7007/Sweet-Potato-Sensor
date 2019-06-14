#include <Manchester.h>

 
void setup() {
  man.setupReceive(12, MAN_300);
  man.setupTransmit(6, MAN_300);
  man.beginReceive();

  pinMode(13,OUTPUT);
//  pinMode(12,INPUT);
  pinMode(10,OUTPUT);

  digitalWrite(13,HIGH);
  digitalWrite(10,LOW);

  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  Serial.begin(9600);
}
 
void loop() {
  if (man.receiveComplete()) {
    uint16_t m = man.getMessage();
    man.transmit(m);
    Serial.println(m);
    man.beginReceive();
  }
}

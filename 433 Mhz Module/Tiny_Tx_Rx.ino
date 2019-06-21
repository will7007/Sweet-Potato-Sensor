#include <Manchester.h>

uint16_t buffering[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
int counter = 0;

void setup() {
  man.setupReceive(4, MAN_300);
  man.setupTransmit(0, MAN_300);
  man.beginReceive();

  pinMode(2,OUTPUT); //led
  pinMode(3,INPUT);
}
 
void loop() {
  if (man.receiveComplete()) {
    buffering[counter] = man.getMessage();
    counter++;
    man.beginReceive();
  }
  
  if (counter > 25) {
    counter = 0;
    digitalWrite(2, HIGH);
  }
  
  if (digitalRead(3)) {
    man.stopReceive(); //must include this to transmit
    for(int i = 0;i < 25; i++) man.transmit(buffering[i]);
    digitalWrite(2,LOW);
    counter = 0;
    man.beginReceive();
  }
}

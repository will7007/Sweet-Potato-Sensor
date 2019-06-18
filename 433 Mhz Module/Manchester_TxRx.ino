#include <Manchester.h>

uint16_t buffering[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
int counter, timer = 0;
bool led = false;
void setup() {
  man.setupReceive(11, MAN_300);
  man.setupTransmit(5, MAN_300);
  man.beginReceive();

  pinMode(13,OUTPUT);
  pinMode(7,INPUT);

  pinMode(12,OUTPUT);
  pinMode(9,OUTPUT);

  digitalWrite(12,HIGH);
  digitalWrite(9,LOW);

  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  Serial.begin(9600);
}
 
void loop() {
  if (man.receiveComplete()) {
    buffering[counter] = man.getMessage();
    Serial.print((char)buffering[counter]);Serial.print(" counter: "); Serial.println(counter);
    digitalWrite(13, led);
    counter++;
    man.beginReceive();
  }
  
  if (counter > 25) counter = 0;
  
  if (digitalRead(7)) {
    delay(10); //delay to give transmitter time just in case
    Serial.println("Sending...");
    digitalWrite(13,HIGH);
    for(int i = 0;i < 25; i++) man.transmit(buffering[i] + 32);
    Serial.println("Sent!");
    digitalWrite(13,LOW);
  }
}

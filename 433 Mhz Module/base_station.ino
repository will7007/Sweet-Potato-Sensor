#include <Manchester.h>

int counter = 0;

#define RX_PIN 12
void setup() {
  Serial.begin(9600);
  man.setupReceive(RX_PIN, MAN_300);
  man.setupTransmit(14, MAN_300);
  man.beginReceive();

  //Receiver pins
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(10,OUTPUT);

  digitalWrite(13,HIGH);
  digitalWrite(10,LOW);

  //Transmitter pins
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);

  digitalWrite(15,HIGH);
  digitalWrite(16,LOW);

  //Button pin
  pinMode(7,INPUT);
}

void loop() {
  if (man.receiveComplete()) {
    uint16_t m = man.getMessage();
    switch (m) {
      case 1: 
      Serial.print("Address: ");
      break;
      case 2:
      Serial.print("Temperature: ");
      break;
      case 3:
      Serial.print("Humidity: ");
      break;
      case 4:
      Serial.println("End of transmission\n");
      break;
      case 5:
      Serial.print("Sensor setup error");
      break;
      default:
      Serial.println(m);
      break;
    }
    man.beginReceive(); //start listening for next message right after you retrieve the message
  }
  else if (digitalRead(7)) {  //comment out for just receiving
    delay(10);
    man.stopReceive(); //must not be receiving if you want to transmit
    Serial.print("Transmitting ");Serial.println(counter);
    man.transmit(counter);
    counter++;
    man.beginReceive();
  }
}

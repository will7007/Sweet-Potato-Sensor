//Run on an AtMEGA2560
#include "Manchester.h"

//Transmission keywords
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
//10 >=: Standard numbers

#define RX_PIN 11
#define LED_PIN 13

uint8_t moo = 1;
#define BUFFER_SIZE 22
uint8_t buffer[BUFFER_SIZE];
const uint8_t FAKE_DATA[4] = {4,13,20,30};

void setup() 
{
  pinMode(LED_PIN, OUTPUT);  
  digitalWrite(LED_PIN, moo);
  Serial.begin(9600);
  man.setupReceive(RX_PIN, MAN_300);
  man.setupTransmit(14, MAN_300);
  man.beginReceiveArray(BUFFER_SIZE, buffer);

  //Receiver pins
  pinMode(12,OUTPUT);
  pinMode(9,OUTPUT);
  
  digitalWrite(12,HIGH);
  digitalWrite(9,LOW);

  //Transmitter pins
  pinMode(15,OUTPUT);
  pinMode(16,OUTPUT);

  digitalWrite(15,HIGH);
  digitalWrite(16,LOW);  
}

void loop() 
{
  if (man.receiveComplete()) 
  {
    uint8_t receivedSize = 0;

    //do something with the data in 'buffer' here before you start receiving to the same buffer again
    receivedSize = buffer[0];
    for(uint8_t i=1; i<receivedSize; i++)
      Serial.println(buffer[i]);
    
    Serial.println();

    man.beginReceiveArray(BUFFER_SIZE, buffer);
    moo = ++moo % 2; //FIXME: Remove this ugly example code
    digitalWrite(LED_PIN, moo);
  }
  
  else if (Serial.available() > 0) {  //comment out for just receiving
    Serial.read(); //throw away whatever character we got
    delay(10);
    man.stopReceive(); //must not be receiving if you want to transmit
    Serial.print("Transmitting... ");

    man.transmitArray(4,FAKE_DATA);
    
    Serial.println("Done.");
    man.beginReceiveArray(BUFFER_SIZE, buffer);
  }
}

#include <Manchester.h>
#include "CORE_BME280_I2C.h"
#include <avr/sleep.h> //Reference: http://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html#gabf889562cc5ea768ee80cfc8a5bb0312

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // From http://www.technoblogy.com/show?KX0

const int BUTTON = 1; //button pin
const int ADDRESS = 60;
const int LENGTH = 4;

volatile uint8_t buffer[LENGTH];

uint8_t transmitBuffer[7] = {7, ADDRESS, 1, 2, 6, 7, 8};
BME280_I2C sensebme;

void setup() {
  adc_disable(); 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //mode name found from http://www.technoblogy.com/show?KX0

  //This part is from https://thewanderingengineer.com/2014/08/11/pin-change-interrupts-on-attiny85/
  GIMSK = 0b00100000;    // turns on pin change interrupts
  PCMSK = 0b00010000;    // turn on interrupts on pins PB4

  //  man.workAround1MhzTinyCore(); DO NOT USE THIS FUNCTION! It makes the program transmit too fast
  man.setupReceive(4, MAN_300);
  man.setupTransmit(3, MAN_300);
  man.beginReceiveArray(LENGTH, buffer);

  pinMode(BUTTON, OUTPUT);
  pinMode(1,OUTPUT); //LED for sleep testing
  digitalWrite(1,LOW);
  
  if (!sensebme.begin()) {
    while (1) {
      man.transmit(5);
      delay(100);
    }
  }
}

void loop() {
  sleep();
  //Post-sleep//
  cli();
  digitalWrite(1,LOW);
  int i=0;
  do {
    if(receiveMessage()) break;
    else {
      delay(1);
      i++;
    }
  }
  while(i<100); //this limit will likely need to be raised when larger packets are sent
}

ISR(PCINT0_vect) {} //the interupt does not need to do anything, it just needs to happen to exit sleep mode

bool receiveMessage() {
  if (man.receiveComplete()) {
    digitalWrite(1,HIGH);
      man.stopReceive();

      transmitBuffer[4] = buffer[1]; //address
      transmitBuffer[5] = buffer[2]; //temp
      transmitBuffer[6] = buffer[3]; //humidity

      sensebme.readSensor();

      transmitBuffer[2] = (int)sensebme.getTemperature_F();
      transmitBuffer[3] = (int)sensebme.getHumidity();

      if (transmitBuffer[2] <= 9) transmitBuffer[2] = 10;
      if (transmitBuffer[3] <= 9) transmitBuffer[3] = 10;

      man.transmitArray(7, transmitBuffer);

      man.beginReceiveArray(LENGTH, buffer);
      
      return true;
    }
  else return false;
}

void sleep() {
  sleep_enable();
  sleep_bod_disable(); //not 100% sure the BOD is off due to the AtTiny core I'm using
  sei();
  sleep_cpu();
  //POST-INTERRUPT//
  sleep_disable();
}

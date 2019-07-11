#include <Manchester.h>
#include "CORE_BME280_I2C.h"
#include "tinysnore.h" //remove once I figure out how to set the watchdog timer myself

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // From http://www.technoblogy.com/show?KX0

const int ADDRESS = 60;
const int LENGTH = 4;

volatile uint8_t buffer[LENGTH];

uint8_t transmitBuffer[7] = {7, ADDRESS, 1, 2, 6, 7, 8};

unsigned long delayTime, timer = 0; //millis timer

int state = 0; //FIXME: IMPROVE HOW STATES ARE TRACKED

BME280_I2C sensebme;

void setup() {

  //This part is from https://thewanderingengineer.com/2014/08/11/pin-change-interrupts-on-attiny85/
  PCMSK = 0b00010000;    // allow pin change interrupts on pin PB4
  sei(); //not sure I need this since the Manchester library already uses interrupts without this
  
  //  man.workAround1MhzTinyCore(); DO NOT USE THIS FUNCTION! It makes the program transmit too fast
  man.setupReceive(4, MAN_300);
  man.setupTransmit(3, MAN_300);
  man.beginReceiveArray(LENGTH, buffer);

  //pinMode(RF_POWER, OUTPUT); //implement in the future to turn stuff on/off
  
  pinMode(1,OUTPUT); //LED for sleep testing
  digitalWrite(1,LOW);
  
  if (!sensebme.begin()) state = 2;
}

void loop() {
  switch (state) {
    case 0: //we have just started up the sensor
      GIMSK = 0b00000000;    // turns OFF pin change interrupts
      while(!(transceiveMessage())) delay(1); //wait for the first message to come in
      timer = millis() - 700; //record when the first message was received
      
      while(!(transceiveMessage())) delay(1); //now wait for the second message to come in
      timer = (millis() - 700) - timer; //FIXME: ACCOUNT FOR 50-DAY ROLLOVER
      delayTime = (timer > 2000) ? timer : 2000; //set the delay time, and make sure it doesn't loop around when 1000 is subtracted
         
      if(delayTime <= 1200000) state = 1; //leave the initial state and go to the deep-sleep state if our delay time isn't more than 20 minutes
      
      break;
    case 1: //we are in normal sensor operation
      GIMSK = 0b00000000;    // turns OFF pin change interrupts
      //digitalWrite(RF_POWER,LOW); //turn off the RF power
      snore(delayTime-2000); //sleep for the delay time minus 3 seconds
      
      //digitalWrite(RF_POWER,HIGH); //turn on the RF power
      GIMSK = 0b00100000;    // turns on pin change interrupts
      snore(3000); //wait a few seconds (we can also be awoken by the receiver at this point)
      
      digitalWrite(1,HIGH);
      
      //even if the sleep times out we will still wake up and check for a message just in case
      for(int i=0;i<1000;i++) {
        if(transceiveMessage()) {
          state = 1; //stay in the normal state if we got a message correctly
          break;
        }
        else {
          delay(1);
          state = 0; //if we still haven't got any message, then we have messed up, time to spend time listening again in the initial state
        }
      }
      digitalWrite(1,LOW);
      break;
      default://state 2, the sensor isn't working or we have some other error
        man.transmit(5);
        delay(100);
      break;
  }
}

ISR(PCINT0_vect) {} //the interupt does not need to do anything, it just needs to happen to exit sleep mode

bool transceiveMessage() {
  if (man.receiveComplete()) {
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

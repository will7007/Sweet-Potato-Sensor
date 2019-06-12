#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  delay(5000);
  Serial.println(readDynamicReg(false,0x20,0x04));
  delay(2000);
  presentI2CPassword();
  
}

//Take off the LSB from the 8-bit I2C addresses in the datasheet for Wire.beginTransmission
//Do not use 0x[binary] for Wire.write, it will treat it as a hex number
//The tag will return 255 (1 for every bit) if you give it the system address when you should have given it the normal one

//I2C_SSO_Dyn 2004h page 55
//EH_CTRL_Dyn 2002h page 41

int readDynamicReg(bool systemAddress, int msb, int lsb) {
  if(!systemAddress) Wire.beginTransmission(0x53);
  else Wire.beginTransmission(0x57);
  
  Wire.write(msb);       
  Wire.write(lsb);       
  Wire.endTransmission();

  if(!systemAddress) Wire.requestFrom(0x53,1);
  else Wire.requestFrom(0x57,1);
  
  return Wire.read();
}

void enableMailboxMode() {
  Wire.beginTransmission(0x57);  
  Wire.write(0);       
  Wire.write(0x0D);    
  Wire.write(1);       
  Wire.endTransmission();
}

//presenting the password doesn't seem to be working for now via I2C
void presentI2CPassword() { //page 72 for password present sequence
  Wire.beginTransmission(0x57);  //write mode, system area (174 decimal) 7 BIT ADDRESS
  Wire.write(0x09);
  Wire.write(0x00);
  for(int i=0;i<8;i++) Wire.write(0); /*Serial.println(i);*/ //CONDITION OF FOR LOOP EVALUATED, THEN LOOP RUNS, THEN COUNTER INCRIMENTED
  Wire.write(0x09);
  for(int i=0;i<8;i++) Wire.write(0);
  Wire.endTransmission();
}

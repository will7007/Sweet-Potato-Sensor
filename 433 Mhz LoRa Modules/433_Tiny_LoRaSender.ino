#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setPins(4,3,11); //don't use dio0
  
  if (!LoRa.begin(43245E4)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("BEACON KN4WAI ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}

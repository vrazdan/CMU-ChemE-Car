#include <Data.h>
#include <SD.h>
#include <SPI.h>

#define SENSEPIN A0

TemperatureSensor temp = Data.temperatureSensor("Temp", SENSEPIN);

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  Data.display(&temp);
  delay(1234);
}

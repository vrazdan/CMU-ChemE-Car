#include <Data.h>

INA219CurrentSensor current = Data.ina219CurrentSensor("Current");

void setup() {
  Data.beginSerial();
  Data.beginTimer();
}

void loop() {
  Data.display(&current);
  
  delay(1234);
}

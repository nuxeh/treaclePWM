#include <Arduino.h>

#include <treaclePWM.h>

treaclePWM tpwm(5);

void setup() {
  tpwm.setFrequency(5.0);
  tpwm.setDutyCycle(50.0);
  tpwm.start();
}

void loop() {
  tpwm.ping();
}

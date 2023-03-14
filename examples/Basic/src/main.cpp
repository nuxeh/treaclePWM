#include <Arduino.h>

#include <treaclePWM.h>

treaclePWM tpwm(6);

void setup() {
  tpwm.setFrequency(8.0);
  tpwm.setDutyCycle(0.1);
  tpwm.start();
}

void loop() {
  tpwm.ping();
}

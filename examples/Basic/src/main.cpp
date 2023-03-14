#include <Arduino.h>

#include <treaclePWM.h>

treaclePWM tpwm(6);

void setup() {
  tpwm.setFrequency(5.0);
  tpwm.setDutyCycle(0.5);
  tpwm.start();
}

void loop() {
  tpwm.ping();
}

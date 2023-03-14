#include <TimerOne.h>
#include <treaclePWM.h>

treaclePWM tpwm(6);

void ping() { tpwm.ping(); }

void setup() {
  Serial.begin(115200);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(ping);
  tpwm.setFrequency(2.0);
  tpwm.setDutyCycle(0.5);
  tpwm.start();
}

void loop() {
  tpwm.ping();
}

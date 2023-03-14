#include <TimerOne.h>
#include <treaclePWM.h>

treaclePWM tpwm(6);

void ping() { tpwm.ping(); }

void setup() {
  Timer1.initialize(5000);
  Timer1.attachInterrupt(ping);
  tpwm.setFrequency(8.0);
  tpwm.setDutyCycle(0.1);
  tpwm.start();
}

void loop() {
  tpwm.ping();
}

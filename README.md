## treaclePWM

A very small PWM library providing (almost) arbitrary frequency and duty cycle
on a GPIO pin. Pulse width and period may be freely configured. `treaclePWM`
works with timeouts, calculating time using the `micros()` Arduino API call,
and a maintenance function, which may be run in task context, or triggered from
a timer interrupt for reduced jitter.

It would be possible to include the entire source code for the library in this
readme, but here is an example:

```c++
#include <treaclePWM.h>

treaclePWM tpwm(6);

void setup() {
  tpwm.setFrequency(5);
  tpwm.setDutyCycle(0.75);
  tpwm.start();
}

void loop() {
  tpwm.ping();
}
```
Or, using a timer:

```c++
#include <TimerOne.h>
#include <treaclePWM.h>

treaclePWM tpwm(6);

void ping() { tpwm.ping(); }

void setup() {
  Timer1.initialize(5000);
  Timer1.attachInterrupt(ping);
  tpwm.setFrequency(5);
  tpwm.setDutyCycle(0.75);
  tpwm.start();
}

void loop() {}
```

If calling `setDutyCycle()`, `setDutyCyclePercent()`, `setDutyCycleByte()`, one
of `setFrequency()`, `setPeriodMs()` or `setPeriodUs()` should be called first,
since the former functions require the period to be known, to calculate the
high pulse timeout.

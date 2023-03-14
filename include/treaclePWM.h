#ifndef __TREACLE_PWM_H__
#define __TREACLE_PWM_H__

#include <Arduino.h>

struct treaclePWM {
  treaclePWM(uint8_t pin) : pin(pin) {};
  treaclePWM(uint8_t pin, bool inv) : inverted(inv), pin(pin) {};

  void setPin(int p) { pin = p; }
  void setPeriodMs(uint16_t ms) { timeout = ms * 1000UL; }
  void setPeriodUs(uint32_t us) { timeout = us; }
  void setHighPeriodUs(uint16_t ms) { timeoutHigh = ms * 1000UL; }
  void setHighPeriodUs(uint32_t us) { timeoutHigh = us; }
  void setLowPeriod(uint32_t us) { if (us < timeout) { timeoutHigh = timeout - us; } else { timeoutHigh = 0; } }
  void setFrequency(float hz) { timeout = (uint32_t)((1.0 / hz) * 1000000.0); }
  void setDutyCyclePercent(float pc) { timeoutHigh = (uint32_t)((float)timeout * pc / 100.0); }
  void setDutyCycle(float r) { timeoutHigh = (uint32_t)((float)timeout * r); }
  void setDutyCycleByte(uint8_t v) { timeoutHigh = (uint32_t)((((timeout * (uint32_t)v) << 4) / 255UL) >> 4); }
  void start() { running = true; pinMode(pin, OUTPUT); }
  void stop() { running = false; drive(false); }
  bool isRunning() { return running; }
  void setInverted(bool i) { inverted = i; }
  void drive(bool state) { digitalWrite(pin, state ^ inverted); }
  void ping() {
    if (!running) return;
    if (timeout == 0) return;
    uint32_t t = micros();
    uint32_t i = t - lastTick;
    if (!state && i > timeout) {
      state = (timeoutHigh > 0);
      drive(state);
      lastTick = t;
    } else if (state && i > timeoutHigh) {
      state = false;
      drive(state);
    }
  }

private:
  bool state = false;
  bool inverted = false;
  bool running = false;
  uint32_t timeout = 0;
  uint32_t timeoutHigh = 0;
  uint32_t lastTick = 0;
  uint8_t pin;
};

#endif // __TREACLE_PWM_H__

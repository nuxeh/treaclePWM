#ifndef __TREACLE_PWM_H__
#define __TREACLE_PWM_H__

struct treaclePWM {
  treaclePWM(uint8_t pin) : pin(pin) {};

  void setPin(int p) { pin = p; }
  void setPeriodMs(uint16_t ms) { timeout = ms * 1000UL; }
  void setPeriodUs(uint32_t us) { timeout = us; }
  void setHighPeriodUs(uint16_t ms) { timeoutHigh = ms * 1000UL; }
  void setHighPeriodUs(uint32_t us) { timeoutHigh = us; }
  void setLowPeriod(uint32_t us) { timeoutHigh = timeout - us; }
  void setFrequency(float hz) {} /* calculate and set the period */
  void setDutyCycle(float pc) {} /* set high percentage of period */
  void start() { running = true; }
  void stop() { running = false; drive(false); }
  bool isRunning() { return running; }
  void setInverted(bool i) { inverted = i; }
  void ping() {
    if (!running) return;
    uint32_t t = micros();
    uint32_t i = t - lastTick;
    if (!state && i > timeout) {
      state = true;
      drive(state ^ inverted);
      lastTick = t;
    } else if (state && i > timeoutHigh) {
      state = false;
      drive(state ^ inverted);
    }
  }
  void drive(bool state) { digitalWrite(pin, state); }

private:
  bool state = false;
  bool inverted = false;
  bool running = false;
  uint32_t timeout;
  uint32_t timeoutHigh;
  uint32_t lastTick;
  uint8_t pin;
};

#endif // __TREACLE_PWM_H__

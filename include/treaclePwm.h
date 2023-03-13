#ifndef __TREACLE_PWM_H__
#define __TREACLE_PWM_H__

struct treaclePwm {
  void setPin(int pin);
  void setPeriodMs(uint32_t ms);
  void setFrequency();
  void setDutyCycle();
  void setHighPeriod();
  void setLowPeriod();
  void start();
  void stop();
  bool isRunning();
  void tick();

private:
  bool inverted = false;
  bool running = false;
  uint32_t timeout;
};

struct treaclePwmCallback {

}

#endif // __TREACLE_PWM_H__

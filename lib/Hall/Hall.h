#ifndef Hall_h
#define Hall_h

#include <Arduino.h>
#include <InterruptHandler.h>


class Hall: public InterruptHandler {
  uint8_t pin;

  volatile long previousPassing;
  volatile int rpm;
  volatile long delta;

  virtual void handleInterrupt(int8_t interruptNum);

public:
  /**
  * Initializes a Hall effect sensor.
  *
  * @param pin: The hall pin number on the micro-controller.
  */
  Hall(uint8_t pin);

  /**
  * The current wheel rpm;
  */
  int getRpm();

  long getDelta();
};

#endif

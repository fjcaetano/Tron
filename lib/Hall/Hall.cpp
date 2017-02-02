#include "Hall.h"

#include <limits.h>


/**
* Initializes a Hall effect sensor.
*/
Hall::Hall(uint8_t pin) {
  this->pin = pin;
  previousPassing = micros();
  delta = LONG_MAX;

  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), FALLING);
}

/**
* The current wheel rpm;
*/
int Hall::getRpm() {
  long passing = millis() - previousPassing;
  if (passing > delta) {
    delta = passing;
  }

  return 60000 / delta; // 1 min = 60,000 ms
}

// Private Methods

void Hall::handleInterrupt(int8_t interruptNum) {
  delta = millis() - previousPassing;

  previousPassing = millis();
}

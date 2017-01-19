#include "Hall.h"


/**
* Initializes a Hall effect sensor.
*/
Hall::Hall(uint8_t pin) {
  this->pin = pin;
  previousPassing = micros();
  rpm = 0;

  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), RISING);
}

/**
* The current wheel rpm;
*/
int Hall::getRpm() {
  return rpm;
}

long Hall::getDelta() {
  return delta;
}

// Private Methods

void Hall::handleInterrupt(int8_t interruptNum) {
  delta = millis() - previousPassing;

  // It is unlikely that delta will naturally go lower than 100ms.
  // This is to prevent noisy interrupts.
  if (delta > 100) {
    rpm = 60000 / delta;
  }

  previousPassing = millis();
}

#include "Button.h"


/**
* Initializes a button.
*/
Button::Button(uint8_t pin) {
  this->pin = pin;
  buttonDownStart = -1;

  upCallback = NULL;
  downCallback = NULL;

  upContext = NULL;
  downContext = NULL;

  pinMode(pin, INPUT);
  attachInterrupt(pin, CHANGE);
}

/**
* Sets the callback action for when the button is released.
*/
void Button::setUpCallback(CallbackFn callback, void *context) {
  upCallback = callback;
  upContext = context;
}

/**
* Sets the callback action for when the button is pushed down.
*/
void Button::setDownCallback(CallbackFn callback, void *context) {
  downCallback = callback;
  downContext = context;
}

/**
* Resets detection to avoid signaling existing button pushes.
*/
void Button::reset() {
  buttonDownStart = -2;
}

/**
* The button's loop function. Must be called inside the main loop.
*/
void Button::loop() {
  if (buttonDownStart >= 0 && digitalRead(pin) && upCallback) {
    upCallback(upContext, millis() - buttonDownStart);
  }
}

// Private Methods

void Button::handleInterrupt(int8_t interruptNum) {
  if (digitalRead(interruptNum)) {
    // Did press down
    buttonDownStart = millis();
    downCallback(downContext, millis() - buttonDownStart);
  }
  else if (buttonDownStart != -2) {
    // Did release
    if (upCallback != NULL) {
      upCallback(upContext, millis() - buttonDownStart);
    }

    buttonDownStart = -1;
  }
}

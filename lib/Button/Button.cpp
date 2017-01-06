#include "Button.h"

#include <Arduino.h>

static void fwdBtnUp(void *context);

/**
* Detects when `button` is pushed and sends the press duration to callback.
*/
void Button::down(CallbackFn callback, void *context) {
  int read = digitalRead(pin);
  if (read == LOW || buttonDownStart == -2) {
    return;
  }

  if (buttonDownStart == -1) {
    buttonDownStart = millis();
  }

  callback(context, millis() - buttonDownStart);
}

/**
* Detects when `button` is released and sends the press duration to callback.
*/
void Button::up(CallbackFn callback, void *context) {
  int read = digitalRead(pin);
  if (read == HIGH || buttonDownStart < 0) {
    if (read == LOW && buttonDownStart == -2) buttonDownStart = -1;
    return;
  }

  callback(context, millis() - buttonDownStart);
  buttonDownStart = -1;
}

/**
* Resets detection to avoid signaling existing button pushes.
*/
void Button::reset() {
  buttonDownStart = -2;
}

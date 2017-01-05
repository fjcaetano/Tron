#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button {
  int pin;
  long buttonDownStart;

public:
  /**
  * The callback function for detections.
  *
  * @param context: context to the callback.
  * @param duration: the press duration/
  */
  typedef void (*CallbackFn)(void *context, long duration);

  /**
  * Initializes a button.
  *
  * @param pin: The button pin number on the micro-controller.
  */
  Button(int pin) :
    pin(pin),
    buttonDownStart(-1)
    { }

  /**
  * Detects when `button` is pushed and sends the press duration to callback.
  *
  * @param callback: the callback function.
  * @param context: context to the callback function.
  */
  void down(CallbackFn callback, void *context);

  /**
  * Detects when `button` is released and sends the press duration to callback.
  *
  * @param callback: the callback function.
  * @param context: context to the callback function.
  */
  void up(CallbackFn callback, void *context);
};

#endif

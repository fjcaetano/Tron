#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <InterruptHandler.h>

/**
* The callback function for detections.
*
* @param context: context to the callback.
* @param duration: the press duration/
*/
typedef void (*CallbackFn)(void *context, long duration);


class Button: public InterruptHandler {
  long buttonDownStart;
  uint8_t pin;

  CallbackFn upCallback;
  CallbackFn downCallback;

  void *upContext;
  void *downContext;

  virtual void handleInterrupt(int8_t interruptNum);

public:
  /**
  * Initializes a button.
  *
  * @param pin: The button pin number on the micro-controller.
  */
  Button(uint8_t pin);

  /**
  * Sets the callback action for when the button is released.
  *
  * @param callback: The callback function.
  * @param context: Context to the callback function.
  */
  void setUpCallback(CallbackFn callback, void *context);

  /**
  * Sets the callback action for when the button is pushed down.
  *
  * @param callback: The callback function.
  * @param context: Context to the callback function.
  */
  void setDownCallback(CallbackFn callback, void *context);

  /**
  * Resets detection to avoid signaling existing button pushes.
  */
  void reset();

  /**
  * The button's loop function. Must be called inside the main loop.
  */
  void loop();
};

#endif

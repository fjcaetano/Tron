#ifndef Menu_h
#define Menu_h

#include <Button.h>
#include <LiquidCrystal.h>

/** The callback function to exiting the menu.
*/
typedef void (*Function)(void);

class Menu {
  Button button;
  Function menuEndedPtr;
  LiquidCrystal lcd;

  int eepromAddr;
  int wheelRadius;
  int isSecondDigit;

  void showWheelCirc();

public:

  /**
  * Initializes a menu to configure the wheel radius
  *
  * @param button: The controller button
  * @param lcd: A LiquidCrystal object
  * @param eaddr: The EEPROM address to the stored wheel radius
  * @param callback: A callback function to leave the menu
  */
  Menu(Button button, LiquidCrystal lcd, int eaddr, Function callback) :
    button(button),
    menuEndedPtr(callback),
    lcd(lcd),
    eepromAddr(eaddr),
    wheelRadius(0),
    isSecondDigit(false)
    { lcd.begin(16, 2); }

  /**
  * Starts the menu display
  */
  void show();

  /**
  * The loop function
  */
  void loop();

  /**
  * Informs the menu that the button has been released.
  *
  * @param duration: The button push duration
  */
  void buttonUp(long duration);

  /**
  * Informs the menu that the button has been pushed down.
  *
  * @param duration: The button push duration
  */
  void buttonDown(long duration);
};

#endif

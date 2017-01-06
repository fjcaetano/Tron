#ifndef Front_h
#define Front_h

#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Button.h>
#include <Menu.h>

class Front {
  float wheelRadius;
  int eepromAddr;
  LiquidCrystal *lcd;
  Button *button;
  Menu *menu;

  int speed(int rpm);
  void showMenu();

public:
  /**
  * Initializes the frontend to display the speed and tachometer.
  *
  * @param lcd: A pointer to the LCD screen
  * @param button: A pointer to the controller button
  * @param eepromAddr: The EEPROM address to the wheel radius.
  */
  Front(LiquidCrystal *lcd, Button *button, int eepromAddr) :
    eepromAddr(eepromAddr),
    lcd(lcd),
    button(button)
    { }

  /**
  * Shows the frontend speed and tachometer to the LCD screen.
  */
  void show();

  /**
  * The loop function.
  */
  void loop();

  /**
  * Informs the frontend that the button has been pushed down.
  *
  * @param duration: The button push duration
  */
  void buttonDown(long duration);
};

#endif

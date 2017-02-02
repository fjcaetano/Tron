#ifndef Front_h
#define Front_h

#include <LiquidCrystal.h>
#include <Button.h>
#include <Menu.h>
#include <Hall.h>

class Front {
  float wheelRadius;
  int eepromAddr;
  LiquidCrystal *lcd;
  Button *button;
  Hall *hall;
  Menu *menu;

  long previousLCDUpdate;

  int speed(int rpm);
  void showMenu();
  void updateLCD();

public:
  /**
  * Initializes the frontend to display the speed and tachometer.
  *
  * @param lcd: A pointer to the LCD screen
  * @param button: A pointer to the controller button
  * @param hall: The hall effect sensor.
  * @param eepromAddr: The EEPROM address to the wheel radius.
  */
  Front(LiquidCrystal *lcd, Button *button, Hall *hall, int eepromAddr) :
    eepromAddr(eepromAddr),
    lcd(lcd),
    button(button),
    hall(hall),
    previousLCDUpdate(0)
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

#define LONG_PRESS 500
#define EXIT_PRESS 5000

#include "Menu.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <math.h>

// Private Functions
void fwdBtnDown(void *, long);
void fwdBtnUp(void *, long);

short int secondDigit = -1;


/**
* Starts the menu display
*/
void Menu::show() {
  wheelRadius = EEPROM.read(eepromAddr);
  lcd.printf("Raio: %dcm ", wheelRadius);
  showWheelCirc();
}

/**
* The loop function
*/
void Menu::loop() {
  button.down(&fwdBtnDown, this);
  button.up(&fwdBtnUp, this);

  showWheelCirc();
  delay(50);
}

/**
* Informs the menu that the button has been pushed down.
*/
void Menu::buttonDown(long duration) {
  if (secondDigit == -1) secondDigit = isSecondDigit;

  isSecondDigit = (bool) (duration / LONG_PRESS % 2 + secondDigit) % 2;

  if (duration > EXIT_PRESS) {
    // Button is held down for over 5 seconds
    menuEndedPtr();
  }
}

/**
* Informs the menu that the button has been released.
*/
void Menu::buttonUp(long duration) {
  secondDigit = -1;
  if (duration >= LONG_PRESS) return;
  // Did tap button

  if (!isSecondDigit) {
    wheelRadius = (wheelRadius + 10) % 100;
    lcd.print(wheelRadius / 10);
  }
  else {
    int firstDigit = (wheelRadius / 10) * 10;
    int secondDigit = wheelRadius % 10;

    wheelRadius = firstDigit + (secondDigit + 1) % 10;
    lcd.print(wheelRadius % 10);

    EEPROM.write(eepromAddr, wheelRadius);
  }
}


// Private Functions

void Menu::showWheelCirc() {
  int wheelCirc = M_PI * wheelRadius * 2;

  lcd.noCursor();
  lcd.setCursor(0, 1);
  lcd.printf("Circ: %dcm ", wheelCirc);

  lcd.setCursor(6 + isSecondDigit, 0);
  lcd.cursor();
}

void fwdBtnDown(void *context, long l) {
  static_cast<Menu *>(context)->buttonDown(l);
}
void fwdBtnUp(void *context, long l) {
  static_cast<Menu *>(context)->buttonUp(l);
}

#define LONG_PRESS 3000

#include "Front.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Button.h>
#include <math.h>

// Private Functions
static void menuEnded(void *);
static void fwdBtnDown(void *, long);


/**
* Shows the frontend speed and tachometer to the LCD screen.
*/
void Front::show() {
  wheelRadius = (float) EEPROM.read(eepromAddr) / 100.0; // Radius is stored in centimeters
  Serial.printf("Radius: %f\n", wheelRadius);

  lcd->noCursor();

  // Resets the menu
  delete menu;
  menu = NULL;

  button->reset();
  button->setDownCallback(&fwdBtnDown, this);

  if (wheelRadius == 0) {
    showMenu();
  }
}

/**
* The loop function.
*/
void Front::loop() {
  if (menu != NULL) {
    menu->loop();
    return;
  }

  int rpm = hall->getRpm();

  lcd->setCursor(0, 0);
  lcd->printf("Velo: %d Km/h  ", speed(rpm));

  lcd->setCursor(0, 1);
  lcd->printf("RPM: %d    ", rpm);

  button->loop();

  delay(10);
}

/**
* Informs the frontend that the button has been pushed down.
*/
void Front::buttonDown(long duration) {
  if (duration < LONG_PRESS) return;

  showMenu();
}

// Private Functions
int Front::speed(int rpm) {
  float wheelCirc = M_PI * wheelRadius * 2;
  return rpm * wheelCirc * 6/100;
}

void Front::showMenu() {
  menu = new Menu(button, lcd, eepromAddr, menuEnded, this);
  menu->show();
}

static void menuEnded(void *context) {
  Front *front = static_cast<Front *>(context);
  front->show();
}

static void fwdBtnDown(void *context, long l) {
  static_cast<Front *>(context)->buttonDown(l);
}

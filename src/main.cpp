#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Menu.h>
#include <Button.h>

// Private Functions
void menuEnded();

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Menu menu = Menu(Button(8), lcd, 0, menuEnded);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  menu.show();
}

void loop() {
  menu.loop();
}


// Private Functions

void menuEnded() {
  lcd.setCursor(0, 0);
  lcd.print("Menu ended");
}

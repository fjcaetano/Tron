#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Button.h>
#include <Hall.h>
#include <Front.h>

const int EEPROMAddress = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 8); // initialize the library with the numbers of the interface pins
Button button = Button(7);
Hall hall = Hall(2);
Front front = Front(&lcd, &button, &hall, EEPROMAddress);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  front.show();
}

void loop() {
  front.loop();
}

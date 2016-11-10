//Lab 1A
//Author: Chris Park

#include <LiquidCrystal.h>

#define NCOLS 16
#define NROWS 2

LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
int _adcVal = 0;

void setup() {
  Serial.begin(9600);
  _lcd.begin(NCOLS, NROWS);
  _lcd.clear();
  _lcd.print("     I Did     ADC  Key  Testing");
  _lcd.setCursor(0, 1);
  _lcd.print("     The Thing!");
  delay(1000);

  for(int i = 0; i < NCOLS; i++){
    _lcd.scrollDisplayLeft();
    delay(500);
  }
}//end setup

void loop() {
  _lcd.setCursor(0, 1);
  _adcVal = analogRead(0);
  Serial.println(_adcVal);
}//end loop

//Lab 1B
//Author: Chris Park

#include <LiquidCrystal.h>

#define NUM_KEYS 5
#define MAX_DESC_LENGTH 7
#define NCOLS 16
#define NROWS 2

LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
int _adcVal, _conversionValue, _checkedKey;
int _adcValArray[NUM_KEYS] = {50, 179, 334, 526, 832};
char _adcCharArray[NUM_KEYS][MAX_DESC_LENGTH] =
  {"Right", "Up", "Down", "Left", "Select"};

void setup() {
  Serial.begin(9600);
  _lcd.begin(NCOLS, NROWS);
  _lcd.clear();
  _lcd.print("     Hello      ADC Key Testing ");
  _lcd.setCursor(0, 1);
  _lcd.print("     World!");
  delay(1000);

  for(int i = 0; i < NCOLS; i++){
    _lcd.scrollDisplayLeft();
    delay(500);
  }
}//end setup

void loop() {
  _checkedKey = checkForKey();

  if(_checkedKey != -1){
    _lcd.clear();
    _lcd.print("ADC Key Testing");
    _lcd.setCursor(0, 1);
    _lcd.print("Key: ");
    _lcd.print(_adcCharArray[_checkedKey]);
  }
}//end loop

int convertKey(){
  for (int i = 0; i < NUM_KEYS; i++){
    if(_adcValArray[i] > _adcVal)
      return i;
  }
  
  return -1;
}//end covertKey

int checkForKey(){
  static int lastKey = -1;
  
  delay(10);
  _adcVal = analogRead(0);
  _conversionValue = convertKey();

  if(_conversionValue != lastKey){
    lastKey = _conversionValue;
    return _conversionValue;
  }

  return -1;
}//end checkForKey

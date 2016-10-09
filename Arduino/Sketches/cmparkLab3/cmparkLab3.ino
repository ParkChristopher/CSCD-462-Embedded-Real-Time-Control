//Lab 3 - Class: Main
//Author: Chris Park

#include <TimerOne.h>
#include<LiquidCrystal.h>

#define READ_PIN 0

enum ScreenState{
  MAIN,
  SET_TIME  
};

int _cursorLocX, _cursorLocY;
ScreenState _LCDState;

/*-------------------------------------------*/

void setup() {
}

/*-------------------------------------------*/

void loop() {
}

/*-------------------------------------------*/

int getCursorLocationX(){
  return _cursorLocX;
}

/*-------------------------------------------*/

int getCursorLocationY(){
  return _cursorLocY;
}

/*-------------------------------------------*/

void drawMain(){
}

/*-------------------------------------------*/

void drawSetTime(){
}

/*-------------------------------------------*/

void setCursorPosition(int posX, int posY){
}

/*-------------------------------------------*/










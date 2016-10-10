//Lab 3 - Class: Main
//Author: Chris Park

#include <TimerOne.h>
#include<LiquidCrystal.h>

#define READ_PIN 0
#define NUM_COLS 16
#define NUM_ROWS 2

enum ScreenState{
  MAIN,
  SET_TIME
};

LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
int _cursorLocX, _cursorLocY;
ScreenState _lcdState;

/*-------------------------------------------*/

void setup() {
  Serial.begin(9600);
  _lcd.begin(NUM_COLS, NUM_ROWS);
  initTimer();
  _lcdState = MAIN;
  drawMain();
}

/*-------------------------------------------*/

void loop() {
  //check for input
  //if input
    //call handle input
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

void handleInput(int key){
  static int MainPositionArray[] = {0, 4, 10};
  static int SetTimePositionArray[] = {4, 11};
  
  //State MAIN
    //if left or right
      //move cursor to next position
    //if select
      //get cursor position
      //if at start
        //if timer not running
          //start timer (add isr?)
      //if at stop
        //stop timer (remove isr?)
      //if at set
        //change state to SET_TIME
        //draw set time screen

  //State SET_TIME
      //left or right
        //move cursor to next position
      //up down
        //increment or decrement current position (rapid inc/dec on hold)
      //select
        //if new value are numerical
        //set new start time values
        //set state to MAIN
        //draw main screen
        
}

/*-------------------------------------------*/

void drawMain(){
  noInterrupts();
  _lcd.setCursor(0, 0);
  _lcd.print("Main    ");
  _lcd.setCursor(0, 1);
  _lcd.print("Set Start Stop  ");
  _lcd.setCursor(0, 1);
  updateCursorLocation(0, 1);
  _lcd.blink();
  interrupts();
}

/*-------------------------------------------*/

void drawSetTime(){
  noInterrupts();
  _lcd.setCursor(0,0);
  _lcd.print("Set Time ");
  _lcd.setCursor(0,1);
  _lcd.print("Min=mm Sec=ss   ");
  _lcd.setCursor(4, 1);
  updateCursorLocation(4, 1);
  _lcd.blink();
  interrupts();
}

/*-------------------------------------------*/

void updateCursorLocation(int posX, int posY){
  _cursorLocX = posX;
  _cursorLocY = posY;
}

/*-------------------------------------------*/










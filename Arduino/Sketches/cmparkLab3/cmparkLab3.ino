//Lab 3 - Class: Main
//Author: Chris Park

#include <TimerOne.h>
#include<LiquidCrystal.h>

#define READ_PIN       0
#define NUM_COLS      16
#define NUM_ROWS       2
#define CURSOR_SET     0
#define CURSOR_START   4
#define CURSOR_STOP   10
#define CURSOR_MIN     4
#define CURSOR_SEC    11
#define KEY_NONE      -1
#define KEY_RIGHT      0
#define KEY_UP         1
#define KEY_DOWN       2
#define KEY_LEFT       3
#define KEY_SELECT     4

enum ScreenState{
  MAIN,
  SET_TIME
};

LiquidCrystal _lcd(8, 9, 4, 5, 6, 7);
int _cursorLocX, _cursorLocY, keyValue;
ScreenState _lcdState;

/*-------------------------------------------*/

void setup() {
  Serial.begin(9600);
  Timer1.initialize(100000);
  _lcd.begin(NUM_COLS, NUM_ROWS);
  _lcdState = MAIN;
  drawMain();
}

/*-------------------------------------------*/

void loop() {

  //if interrupt fired (some flag value was set)
    //deal with it
  
  handleInput(checkForKey());
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
  static bool isKeyReleased = true;
   
  if(key == KEY_NONE){
    isKeyReleased = true;
    return;
  }

  if(_lcdState == MAIN && isKeyReleased){
    isKeyReleased = false;
    
    if(key == KEY_RIGHT){
      if(getCursorLocationX() == CURSOR_SET){
        updateCursorLocation(CURSOR_START, 1);
      } else if(getCursorLocationX() == CURSOR_START){
        updateCursorLocation(CURSOR_STOP, 1);
      } else if(getCursorLocationX() == CURSOR_STOP){
        updateCursorLocation(CURSOR_SET, 1);
      }
      _lcd.setCursor(getCursorLocationX(), getCursorLocationY());
      return;
    }
    
    if(key == KEY_LEFT){
      if(getCursorLocationX() == CURSOR_SET){
        updateCursorLocation(CURSOR_STOP, 1);
      } else if(getCursorLocationX() == CURSOR_START){
        updateCursorLocation(CURSOR_SET, 1);
      } else if(getCursorLocationX() == CURSOR_STOP){
        updateCursorLocation(CURSOR_START, 1);
      }
      _lcd.setCursor(getCursorLocationX(), getCursorLocationY());
      return;
    }
    
    if(key == KEY_SELECT){
      if(getCursorLocationX() == CURSOR_START){
        //if timer not running start it
      } else if(getCursorLocationX() == CURSOR_STOP){
        //stop the timer and update the timer to current time setting
      } else if(getCursorLocationX() == CURSOR_SET){
        _lcdState = SET_TIME;
        drawSetTime();
      }
    }
  }//end MAIN State
  
  if(_lcdState == SET_TIME && isKeyReleased){
    isKeyReleased = false;
    
    if(key == KEY_LEFT || key == KEY_RIGHT){
      if(getCursorLocationX() == CURSOR_MIN){
        updateCursorLocation(CURSOR_SEC, 1);
      } else {
        updateCursorLocation(CURSOR_MIN, 1);
      }
      _lcd.setCursor(getCursorLocationX(), getCursorLocationY());
      return;
    }

    if(key == KEY_UP){
      //increment current cursor location (hold for steady increase)
    }

    if(key == KEY_DOWN){
      //decrement current cursor location (hold for steady decrease)
    }

    if(key == KEY_SELECT){
      //if values have been set, and the timer isn't running,
        //set those values to the timer display
      _lcdState = MAIN;
      drawMain();
    }
  }
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










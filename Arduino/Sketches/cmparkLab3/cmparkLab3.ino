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
int _setTimeMinutes, _setTimeSeconds;
ScreenState _lcdState;

/*-------------------------------------------*/

void setup() {
  Serial.begin(9600);
  _setTimeMinutes = _setTimeSeconds = 0;
  initTimer();
  _lcd.begin(NUM_COLS, NUM_ROWS);
  _lcdState = MAIN;
  drawMain();
}

/*-------------------------------------------*/

void loop() {
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
  bool isKeyHeld = false;
   
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
    }//end MAIN KEY_RIGHT
    
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
    }//end MAIN KEY_LEFT
    
    if(key == KEY_SELECT){
      if(getCursorLocationX() == CURSOR_START){
        if(getIsTimerRunning() == false){
          startTimer();
        }
      } else if(getCursorLocationX() == CURSOR_STOP){
        stopTimer();
      } else if(getCursorLocationX() == CURSOR_SET){
        _lcdState = SET_TIME;
        drawSetTime(true);
      }
    }//end MAIN KEY_SELECT
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
    }//end SET_TIME KEY_LEFT and KEY_RIGHT

    if(key == KEY_UP){
      isKeyHeld = true;
      
      while(isKeyHeld){
        if(checkForKey() == KEY_UP){
          if(getCursorLocationX() == CURSOR_MIN){
            _setTimeMinutes++;
            if(_setTimeMinutes > 99){
              _setTimeMinutes = 99;
            }
          }else{ //CURSOR_SEC
            _setTimeSeconds++;
            if(_setTimeSeconds > 99){
              _setTimeSeconds = 99;
            }
          }
          
          drawSetTime(false);
          delay(250);
        }else{
          isKeyHeld = false;
        }
      }
      return;
    }//end SET_TIME KEY_UP

    if(key == KEY_DOWN){
      isKeyHeld = true;

      while(isKeyHeld){
        if(checkForKey() == KEY_DOWN){
          if(getCursorLocationX() == CURSOR_MIN){
            _setTimeMinutes--;
            if(_setTimeMinutes < 0){
              _setTimeMinutes = 0;
            }
          }else{ //CURSOR_SEC
            _setTimeSeconds--;
            if(_setTimeSeconds < 0){
              _setTimeSeconds = 0;
            }
          }
          
          drawSetTime(false);
          delay(250);
        }else{
          isKeyHeld = false;
        }
      }
      return;
    }//end SET_TIME KEY_DOWN

    if(key == KEY_SELECT){
      setTimer(_setTimeMinutes, _setTimeSeconds);

      if(getIsTimerRunning() == false){
        drawTimer(true);
      }
      _lcdState = MAIN;
      drawMain();
    }
  }//end SET_TIME State     
}//end handleInput

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

void drawSetTime(bool isStateChange){
  noInterrupts();
  _lcd.setCursor(0,0);
  _lcd.print("Set Time ");

  if(_setTimeMinutes == 0 && _setTimeSeconds == 0){
    _lcd.setCursor(0, 1);
    _lcd.print("Min=mm Sec=ss   ");
  }else{
    updateActiveTimeSetting(_setTimeMinutes, _setTimeSeconds);
  }

  if(isStateChange){
    _lcd.setCursor(4, 1);
    updateCursorLocation(4, 1);
  }else{
    _lcd.setCursor(getCursorLocationX(), 1);
  }
  _lcd.blink();
  interrupts();
}

/*-------------------------------------------*/

void updateActiveTimeSetting(int minutes, int seconds){
  //called when the user increments or decrements the timer.
  //updates the printed values every time the value changes
  //(So after each delayed call while the button is held,
  //or when it's initially pressed)
  _lcd.setCursor(0,1);
  _lcd.print("Min=");
  _lcd.print(minutes); //need to add leading 0 here
  _lcd.print(" ");
  _lcd.print("Sec=");
  _lcd.print(seconds); //need to add leading 0 here
  _lcd.print("   ");
}

/*-------------------------------------------*/

void updateCursorLocation(int posX, int posY){
  _cursorLocX = posX;
  _cursorLocY = posY;
}

/*-------------------------------------------*/

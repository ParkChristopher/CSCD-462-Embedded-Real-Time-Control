//Lab 3 - Class: Timer
//Author: Chris Park

int _min, _sec, _tenths;
int _startMinutes, _startSeconds;
bool _isRunning;

/*-------------------------------------------*/

void initTimer(){
  Timer1.initialize(100000);
  _min = _sec = _tenths = 0;
  _startMinutes = _startSeconds = 0;
  _isRunning = false;  
}

void setTimer(int minutes, int seconds){
  _startMinutes = minutes;
  _startSeconds = seconds;
}

/*-------------------------------------------*/

void startTimer(){
  _min = _startMinutes;
  _sec = _startSeconds;
  _isRunning = true;
  Timer1.attachInterrupt(updateTimer);
}

/*-------------------------------------------*/

void stopTimer(){
  _isRunning = false;
  Timer1.detachInterrupt();
}

/*-------------------------------------------*/

void updateTimer(){

  _tenths--;
  
  if(_tenths < 0){
    if(_min == 0 && _sec == 0){
      stopTimer();
      return;
    }else if(_sec == 0 && _min > 0){
      _min--;
      _sec = 59;
      _tenths = 9;
      return;  
    } else if(_sec > 0){
      _sec--;
      _tenths = 9;
    }
  }
  
  drawTimer(false);
}

/*-------------------------------------------*/

void drawTimer(bool isNewTime){

  if(!_isRunning){
    if(isNewTime){
      _lcd.setCursor(9, 0);
      _lcd.print(_startMinutes);
      _lcd.print(":");
      _lcd.print(_startSeconds);
      _lcd.print(":");
      _lcd.print("0");
      _lcd.setCursor(getCursorLocationX(), 1); //Return to previous position.
    }
    return;
  }

  _lcd.setCursor(9, 0);
  _lcd.print(_min);
  _lcd.print(":");
  _lcd.print(_sec);
  _lcd.print(":");
  _lcd.print(_tenths);
  _lcd.setCursor(getCursorLocationX(), 1);
}

/*-------------------------------------------*/

int getStartMinutes(){
  return _startMinutes;  
}

/*-------------------------------------------*/

int getStartSeconds(){
  return _startSeconds;
}

/*-------------------------------------------*/

bool getIsTimerRunning(){
  return _isRunning;
}

/*-------------------------------------------*/

void setIsTimerRunning(bool isRunning){
  _isRunning = isRunning;
}

/*-------------------------------------------*/

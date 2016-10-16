//Lab 3 - Class: Timer
//Author: Chris Park

int _min, _sec, _tenths;
int _startMinutes, _startSeconds;
bool _isRunning;

/*-------------------------------------------*/

void initTimer(){
  Timer1.initialize(100000);
  _startMinutes = _startSeconds = 0;
  _isRunning = false;  
}

void setTimer(int minutes, int seconds){
  _startMinutes = minutes;
  _startSeconds = seconds;
}

/*-------------------------------------------*/

void startTimer(){
  Timer1.attachInterrupt(updateTimer);
}

/*-------------------------------------------*/

void stopTimer(){
  Timer1.detachInterrupt();
}

/*-------------------------------------------*/

void updateTimer(){

//calculate changes in time values
//draw the timer
}

/*-------------------------------------------*/

void drawTimer(bool isNewTime){

  if(!_isRunning){
    if(isNewTime){
      //draw the timer with the start times
    }
    return;
  }

  //draw with standard values (should already be update by updateTimer)
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

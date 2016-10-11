//Lab 3 - Class: Timer
//Author: Chris Park

int _min, _sec, _tenths;
int _startMinutes, _startSeconds;

/*-------------------------------------------*/

void setTimer(int minutes, int seconds){
  _startMinutes = minutes;
  _startSeconds = seconds;
}

/*-------------------------------------------*/

void startTimer(){
  //add isr function
}

/*-------------------------------------------*/

void stopTimer(){
  //remove isr function
  //should we reset the drawn timer to current start values here?
}

/*-------------------------------------------*/

void updateTimer(){
  //determine elapsed time since last timer update?
  //subrtract that from the current min sec tenths
  //update those values with these new values,
  //if those values are less than 0, set to 0
    //stop timer
  //draw timer
}

/*-------------------------------------------*/

void drawTimer(){
  //if timer is not running
    //draw with current starting values
    //return

  //draw updated values
}

/*-------------------------------------------*/

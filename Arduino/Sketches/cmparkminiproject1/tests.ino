/**
 * Score Interrupt Tests
 */
#define POINT_VALUE 8353

/**
 * 
 */
void cycleScoreA(){
  
  bool done = false;
  for (uint8_t i = 0; i < NUM_DISPLAYS && !done; i++) {

    mCurrentScores[i] ++;
    setScore(i, mCurrentScores[i]);
    
    if(mCurrentScores[i] > 8353) {
      done = true;
    }
  }
}

/**
 * Increase scores with a one display offset.
 */
void cycleScoreB() {
  
  static uint8_t displayNum = 0;
  
  mCurrentScores[displayNum] += POINT_VALUE;
  setScore(displayNum, mCurrentScores[displayNum]);
  displayNum = displayNum < NUM_DISPLAYS ? displayNum++ : 0;
}

/**
 * Write an initial score value
 */
void staticScoreTest(){

  for(uint8_t i = 0; i < NUM_DISPLAYS; i++){

    if(mCurrentScores[i] != POINT_VALUE){
      mCurrentScores[i] = POINT_VALUE;
      setScore(i, mCurrentScores[i]);
    }
  }
}

/**
 * Score Interrupt Tests
 */
#define POINT_VALUE 8353

/**
 * Increment scores until a maximum value is reached.
 */
void cycleScoreA(){
  
  static bool done = false;
  for (uint8_t i = 0; i < NUM_DISPLAYS && !done; i++) {

    if(mCurrentScores[i] >= POINT_VALUE) {
      done = true;
      break;
    }

    mCurrentScores[i] ++;
    setScore(i, mCurrentScores[i]);
  }
}

/**
 * Increase scores with a one display offset.
 */
void cycleScoreB() {
  
  static uint8_t offset = 0;
  
  for(uint8_t i = 0; i < NUM_DISPLAYS; i++){

    mCurrentScores[i] += POINT_VALUE;
    setScore(i, mCurrentScores[i]);

    if(offset <= i){
      offset++;
      return;
    }
  }
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

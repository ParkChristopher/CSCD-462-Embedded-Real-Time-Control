/**
 * Score Interrupt Tests
 */
#define POINT_VALUE = 8353


/**
 * Increase scores with a one display offset.
 */
 void cycleDisplay() {
  
  static uint8_t displayNum = 0;
  
  mCurrentScore[displayNum] += POINT_VALUE;
  setScore(displayNum, mCurrentScores[displayNum]);
  displayNum = displayNum < NUM_DISPLAYS ? displayNum++ : 0;
 }

void updateScoreInterrupt() {

  bool done = false;
  for (uint8_t i = 0; i < NUM_DISPLAYS && !done; i++) {

    mCurrentScores[i] ++;
    setScore(i, mCurrentScores[i]);

    if(mCurrentScores[i] > 8353) {
      done = true;
    }
  }
}

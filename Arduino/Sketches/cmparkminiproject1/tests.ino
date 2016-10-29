/**
 * Score Interrupt Tests
 */
#define POINT_VALUE 8353


/**
 * Increase scores with a one display offset.
 */
 void cycleDisplay() {
  
  static uint8_t displayNum = 0;
  
  mCurrentScores[displayNum] += POINT_VALUE;
  setScore(displayNum, mCurrentScores[displayNum]);
  displayNum = displayNum < NUM_DISPLAYS ? displayNum++ : 0;
 }

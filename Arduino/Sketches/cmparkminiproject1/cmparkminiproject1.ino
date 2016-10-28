
/**
 * @author Chris Park
 * @author Bruce Emehiser
 * @title Score Display
 * @date 2016 10 28
 * @url https://github.com/ParkChristopher/CSCD-462-Embedded-Real-Time-Control
 */

#define NUM_DISPLAYS 5      // Number of displays in the machine
#define NUM_DIGITS 7        // Number of digits in each display

// Output Pins
#define STROBE_DISPLAY5 38
#define ENABLE_STROBE 88    // A9
#define BLANK_DISPLAY 82    // A15
#define ENABLE_DIGIT_1 39   // Digit enables ordered LSB to MSB
#define ENABLE_DIGIT_2 40
#define ENABLE_DIGIT_3 41
#define ENABLE_DIGIT_4 50
#define ENABLE_DIGIT_5 51
#define ENABLE_DIGIT_6 52
#define ENABLE_DIGIT_7 53

volatile uint8_t mScoreArray[NUM_DISPLAYS][NUM_DIGITS];    // Score array to hold the byte values for the digits in each display.
volatile uint32_t mCurrentScores[NUM_DISPLAYS];            // Value of current score. Must be 32 bits, due to decimal 7 length.

void setup() {

  //Program flow:

  configureOutputPins();

  //Digits should update as fast as interrupt 2 can fire,
  //a timer should be used to update score data every 500ms.

  //NOTE: When you set up the Interrupt the, use rising edge
  //ie. attachInterrupt(digitalPinToInterrupt(2), ISRFunction, RISING);

  // todo set timer interrupt to update every half second
  // set display update on interrupt 2
  attachInterrupt(digitalPinToInterrupt(2), refreshDisplaysInterrupt, RISING);
}

void loop() {}

/**
 * Set the pins necessary to interface with the display.
 * Note: This method must be called before any other methods.
 */
void configureOutputPins(){
  DDRA = B11111111;                   // PORTA
  pinMode(STROBE_DISPLAY5,  OUTPUT);
  pinMode(BLANK_DISPLAY,    OUTPUT);
  pinMode(ENABLE_STROBE,    OUTPUT);
  pinMode(ENABLE_DIGIT_1,   OUTPUT);
  pinMode(ENABLE_DIGIT_2,   OUTPUT);
  pinMode(ENABLE_DIGIT_3,   OUTPUT);
  pinMode(ENABLE_DIGIT_4,   OUTPUT);
  pinMode(ENABLE_DIGIT_5,   OUTPUT);
  pinMode(ENABLE_DIGIT_6,   OUTPUT);
  pinMode(ENABLE_DIGIT_7,   OUTPUT);
}

/**
 * Set the score to display on a display.
 * @param display The display on which to set the score.
 * @param score The score to set on the display.
 */
void setScore(uint8_t display, uint32_t score){

  // copy the score digits to score array (we must copy because array is static)
  uint8_t *scoreDigits = parseScore(score);
  for(int i = 0; i < NUM_DIGITS; i ++) {
    mScoreArray[display][i] = scoreDigits[i];
  }
}

/**
 * Blank scores and update them based on the current
 * state of the score array.
 */
void updateDisplays(){
  static unsigned int currentDigit = 0;

  digitalWrite(BLANK_DISPLAY, HIGH);    // Blank all displays
  digitalWrite(currentDigit, LOW);      // Disable previous digit
  currentDigit ++;                      // Update current digit variable
//  PORTA = mScoreArray[currentDigit];    // Update current digit variable
  digitalWrite(ENABLE_STROBE, HIGH);    // Enable display strobes by setting A9 high
  //for each of the five displays
  for (int i = 0; i < NUM_DISPLAYS; i++) {
    // set lower nibble of PORTA to binary value to display.
    PORTA = mScoreArray[i][currentDigit];
    // toggle the displays strobe line high then low
    // todo toggle strobe line
  }
  digitalWrite(ENABLE_STROBE, LOW);     // Disable the display strobe by setting A9 low
  // set the enable bit for the new digit high (use current digit here?)
  // todo set enable bit
  // set the display blanking bit low (A15) this turns on all displays
  digitalWrite(BLANK_DISPLAY, LOW);
}

/**
 * Parse score digits into uint8_t array.
 * @const DIGITS The number of digits.
 * @param score The 32 bit score to parse.
 *              Note that a 16 bit int can't hold decimal
 *              value of zeven characters.
 * @return The byte array containing the parsed digits.
 * Note: This method statically allocates all memory.
 */
uint8_t* parseScore(uint32_t score){

  uint8_t digits[NUM_DIGITS];

  int i = 0;
  int cur = 0;
  while(score > 0) {
    digits[NUM_DIGITS - i - 1] = byte(score % 10); // byte converts parameter to uint8_t
    score = score / 10;
    i ++;
  }

  // fill remainder with zeros if score length < 7 digits
  while(i < NUM_DIGITS) {
    digits[NUM_DIGITS - i - 1] = B0;
    i ++;
  }
  return digits;
}

/**
 * Set display digit.
 * @param display The display to set the score on
 * @param digit The digit of that display to set
 * @param value The value to set the digit to
 */
void setDisplay(uint8_t display, uint8_t digit, uint8_t value){
  // todo set display
}

/**
 * Interrupt service routine which is called to refresh displays.
 */
void refreshDisplaysInterrupt() {

  for(uint8_t display = 0; display < NUM_DISPLAYS; display ++) {
    for(uint8_t digit = 0; digit < NUM_DIGITS; digit ++) {
      setDisplay(display, digit, mScoreArray[display][digit]);
    }
  }
}

/**
 * Interrupt service routine which is called to increment the scores.
 */
void updateScoreInterrupt() {

  bool done = false;
  for (uint8_t i = 0; i < NUM_DISPLAYS && !done; i++) {

    mCurrentScores[i] ++;
    setScore(i, parseScore(mCurrentScores[i]));

    if(mCurrentScores[i] > 8353) {
      done = true;
    }
  }
}

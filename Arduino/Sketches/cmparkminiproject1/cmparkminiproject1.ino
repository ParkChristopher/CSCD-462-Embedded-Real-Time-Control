
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
#define ENABLE_STROBE A9
#define ENABLE_STROBE_5 38
#define BLANK_DISPLAY A15
#define ENABLE_DIGIT_1 39   // Digit enables ordered LSB to MSB
#define ENABLE_DIGIT_2 40
#define ENABLE_DIGIT_3 41
#define ENABLE_DIGIT_4 50
#define ENABLE_DIGIT_5 51
#define ENABLE_DIGIT_6 52
#define ENABLE_DIGIT_7 53

const uint8_t ENABLE_DIGITS[NUM_DIGITS] = {ENABLE_DIGIT_1, ENABLE_DIGIT_2, ENABLE_DIGIT_3, ENABLE_DIGIT_4, ENABLE_DIGIT_5, ENABLE_DIGIT_6, ENABLE_DIGIT_7};

volatile uint8_t mScoreArray[NUM_DISPLAYS][NUM_DIGITS];    // Score array to hold the byte values for the digits in each display.
volatile uint32_t mCurrentScores[NUM_DISPLAYS];            // Value of current score. Must be 32 bits, due to decimal 7 length.
uint8_t mCurrentDigit;                                     // Current digit updating on display.

void setup() {

  Serial.begin(9600);
  Serial.print("Hello World!\n");

  mCurrentDigit = 0;
  configureOutputPins();
  attachInterrupt(2, refreshDisplaysInterrupt, RISING);
}

void loop() {

  updateScoreInterrupt();
  delay(500);
}

/**
 * Set the pins necessary to interface with the display.
 * Note: This method must be called before any other methods.
 */
void configureOutputPins(){
  DDRA = B11111111;         // PORTA
  pinMode(BLANK_DISPLAY,    OUTPUT);
  pinMode(ENABLE_STROBE,    OUTPUT);
  pinMode(ENABLE_STROBE_5,  OUTPUT);
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

  // save the score into the score array
  mCurrentScores[display] = score;

  int i = 0;
  while(score > 0 && i < NUM_DIGITS) {
    mScoreArray[display][NUM_DIGITS - i - 1] = score % 10;
    score = score / 10;
    i ++;
  }

  // fill remainder with zeros if score length < 7 digits
  while(i < NUM_DIGITS) {
    mScoreArray[display][NUM_DIGITS - i - 1] = 0;
    i ++;
  }
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
 * Blank scores and update them based on the current
 * state of the score array.
 */
void updateDisplays(){

  digitalWrite(BLANK_DISPLAY, HIGH);                // Blank (Turn Off) all displays
  digitalWrite(ENABLE_DIGITS[mCurrentDigit], LOW);  // Disable previous digit
                                                    // Update current digit variable
  mCurrentDigit = mCurrentDigit >= NUM_DIGITS ? 0 : mCurrentDigit + 1; 

  digitalWrite(ENABLE_STROBE, HIGH);                // Enable display strobes by setting A9 high
  digitalWrite(ENABLE_STROBE_5, HIGH);

  for (int i = 0; i < NUM_DISPLAYS; i++) {

    uint8_t digitValue = mScoreArray[i][mCurrentDigit];

    PORTA = (i << 4) | digitValue;                  // set display in upper nibble, and digit value in lower nibble of PORTA

    digitalWrite(ENABLE_DIGITS[i], HIGH);           // toggle the displays strobe line high then low
    digitalWrite(ENABLE_DIGITS[i], LOW);
  }

  digitalWrite(ENABLE_STROBE, LOW);                 // disable the display strobe by setting A9 low
  digitalWrite(ENABLE_STROBE_5, LOW);

  digitalWrite(ENABLE_DIGITS[mCurrentDigit], HIGH); // set the enable bit for the new digit high
  digitalWrite(BLANK_DISPLAY, LOW);                 // set the display blanking bit low (A15) this turns on all displays
}

/**
 * Interrupt service routine which is called to refresh displays.
 */
void refreshDisplaysInterrupt() {
  updateDisplays();
}

/**
 * Interrupt service routine which is called to increment the scores.
 */
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

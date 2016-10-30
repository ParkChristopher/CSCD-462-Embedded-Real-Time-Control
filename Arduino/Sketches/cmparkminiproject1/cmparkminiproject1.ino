
/**
 * @author Chris Park
 * @author Bruce Emehiser
 * @title Score Display
 * @date 2016 10 28
 * @url https://github.com/ParkChristopher/CSCD-462-Embedded-Real-Time-Control
 */

#define NUM_DISPLAYS 5      // Number of displays in the machine
#define NUM_DIGITS 7        // Number of digits in each display
#define DELAY_TIME_MSEC 500

// Output Pins
#define ENABLE_STROBE A9
#define BLANK_DISPLAY A15
#define ENABLE_DIGIT_1 39   // Digit enables ordered LSB to MSB
#define ENABLE_DIGIT_2 40
#define ENABLE_DIGIT_3 41
#define ENABLE_DIGIT_4 50
#define ENABLE_DIGIT_5 51
#define ENABLE_DIGIT_6 52
#define ENABLE_DIGIT_7 53

// PORTA Score Values (Lower Nibble - Ordered LSB to MSB)
#define PA_VALUE_1 22
#define PA_VALUE_2 23
#define PA_VALUE_3 24
#define PA_VALUE_4 25

// PORTA Display Strobes 1-4 (Upper Nibble - Ordered LSB to MSB)
#define DISPLAY_STROBE_1 26
#define DISPLAY_STROBE_2 27
#define DISPLAY_STROBE_3 28
#define DISPLAY_STROBE_4 29

// Display 5 Strobe
#define DISPLAY_STROBE_5 38

const uint8_t ENABLE_DIGITS[NUM_DIGITS] = {ENABLE_DIGIT_1, ENABLE_DIGIT_2, ENABLE_DIGIT_3, ENABLE_DIGIT_4, ENABLE_DIGIT_5, ENABLE_DIGIT_6, ENABLE_DIGIT_7};
const uint8_t DISPLAY_STROBES[NUM_DISPLAYS] = {DISPLAY_STROBE_1, DISPLAY_STROBE_2, DISPLAY_STROBE_3, DISPLAY_STROBE_4, DISPLAY_STROBE_5,};

volatile uint8_t mScoreArray[NUM_DISPLAYS][NUM_DIGITS];    // Score array to hold the byte values for the digits in each display.
volatile uint32_t mCurrentScores[NUM_DISPLAYS];            // Value of current score. Must be 32 bits, due to decimal 7 length.
uint8_t mCurrentDigit;                                     // Current digit updating on display.

void setup() {

  Serial.begin(9600);
  Serial.print("Running Setup\r\n");

  mCurrentDigit = 0;
  
  Serial.print("Configure Pins...");
  configureOutputPins();
  Serial.print("Done!\r\n");

  Serial.print("Initializing Scores...");
  initScores();
  Serial.print("Done!\r\n");
  
  Serial.print("Attach Interrupt...");
  attachInterrupt(2, refreshDisplaysInterrupt, RISING);
  Serial.print("Done!\r\n");
  Serial.print("Setup Complete!\r\n");
}

void loop() {

  updateScoreInterrupt();
  delay(DELAY_TIME_MSEC);
}

/**
 * Set the pins necessary to interface with the display.
 * Note: This method must be called before any other methods.
 */
void configureOutputPins(){
  DDRA = B11111111;         // PORTA (Upper nibble, DISPLAY_STROBE 1-4)
  pinMode(DISPLAY_STROBE_5, OUTPUT);
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
 * Initialize score values
 */
void initScores(){
  for(uint8_t i = 0; i < NUM_DISPLAYS; i++){
    mCurrentScores[i] = 0;
    setScore(i, mCurrentScores[i]);
  }
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
    mScoreArray[display][i] = score % 10;
    score = score / 10;
    i ++;
  }

  // fill remainder with zeros if score length < 7 digits
  while(i < NUM_DIGITS) {
    mScoreArray[display][i] = 0;
    i ++;
  }
}

/**
 * Blank scores and update them based on the current
 * state of the score array.
 */
void updateDisplays(){

  //Serial.print("Blank Bits\r\n");
  digitalWrite(BLANK_DISPLAY, HIGH);                // Blank (Turn Off) all displays
  digitalWrite(ENABLE_DIGITS[mCurrentDigit], LOW);  // Disable previous digit
                                                    // Update current digit variable
  mCurrentDigit = mCurrentDigit >= NUM_DIGITS ? 0 : mCurrentDigit + 1; 

  digitalWrite(ENABLE_STROBE, HIGH);                // Enable display strobes by setting A9 high

  for (int i = 0; i < NUM_DISPLAYS; i++) {

    uint8_t digitValue = mScoreArray[i][mCurrentDigit];
    
    PORTA = digitValue;                               // Set digit value in lower nibble of PORTA.
    digitalWrite(DISPLAY_STROBES[i], HIGH);           // toggle the displays strobe line high then low
    digitalWrite(DISPLAY_STROBES[i], LOW);
  }
  
  digitalWrite(ENABLE_STROBE, LOW);                 // disable the display strobe by setting A9 low
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
  //staticScoreTest();
  //cycleScoreA();
  cycleScoreB();
}

//Chris Park
//Mini Project 1

#define NUM_DISPLAYS 5
#define NUM_DIGITS 7
//NOTE: When you set up the Interrupt the, use rising edge
//ie. attachInterrupt(digitalPinToInterrupt(2), ISRFunction, RISING);


//Program flow:
//Digits should update as fast as interrupt 2 can fire,
//a timer should be used to update score data every 500ms.
/*----------------------------------------------------*/
//Output Pins

#define STROBE_DISPLAY5 38
#define ENABLE_STROBE 88    //A9
#define BLANK_DISPLAY 82    //A15
#define ENABLE_DIGIT_1 39   //Digit enables ordered LSB to MSB
#define ENABLE_DIGIT_2 40
#define ENABLE_DIGIT_3 41
#define ENABLE_DIGIT_4 50
#define ENABLE_DIGIT_5 51
#define ENABLE_DIGIT_6 52
#define ENABLE_DIGIT_7 53

/*----------------------------------------------------*/

unsigned volatile int _scoreArray[NUM_DISPLAYS][NUM_DIGITS];

/*----------------------------------------------------*/

void setup() {
  configureOutputPins();
}

/*----------------------------------------------------*/

void loop() {
}

/*----------------------------------------------------*/

void configureOutputPins(){
  DDRA = B11111111;                   //PORTA
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

/*----------------------------------------------------*/
void setScore(unsigned int display, unsigned int score){
  //_scoreArray[i] = parseScore(score);
}

/*----------------------------------------------------*/

void updateDisplays(){
  static unsigned int currentDigit;
  
  digitalWrite(BLANK_DISPLAY, HIGH);    //Blank all displays
  digitalWrite(currentDigit, LOW);      //Disable previous digit
  //Update current digit variable
  //Enable display strobes by setting A9 high
  //for each of the five displays
    //set lower nibble of porta to BCD value to display.
    //toggle the displays strobe line hight then low
  //disable the display strobe by setting a9 low
  //set the enable bit for the new digit high (use current digit here?)
  //set the display blanking bit low (a15) this turns on all displays
}

/*----------------------------------------------------*/

//Note: if the score is greater than seven digits, we should
//not return it. it will exceed the maximum digits of the display.

/**
 * Parse score digits into int array.
 * @const DIGITS 7
 * @param score The score to parse.
 * @return The int array containing the parsed digits.
 * Note: This method statically allocates all memory.
 */
int* parseScore(unsigned int score){

  const int DIGITS = 7;
  int digits[DIGITS];

  int i = 0;
  int cur = 0;
  while(score > 0) {
    digits[DIGITS - i - 1] = score % 10;
    score = score / 10;
    i ++;
  }

  // fill remainder with zeros if score length < 7 digits
  while(i < DIGITS) {
    digits[DIGITS - i - 1] = 0;
    i ++;
  }
  return digits;
} 

/*----------------------------------------------------*/

/**
 * Convert unsigned int to binary coded decimal.
 * @param val unsigned int decimal {val | 0 <= val <= 9}
 * @return unsigned int binary coded decimal
 */
unsigned int uIntToBCD(unsigned int val){

  // check value
  if(val < 0 || val > 9) {
    return 0;
  }

  unsigned int bcdValues[] = {
      0000, // 0
      0001, // 1
      0010, // 2
      0011, // 3
      0100, // 4
      0101, // 5
      0110, // 6
      0111, // 7
      1000, // 8
      1001, // 9
  };

  return bcdValues[val];
}

/*----------------------------------------------------*/

void setDisplay(){}

/*----------------------------------------------------*/

//Chris Park
//Mini Project 1
#define NUM_DISPLAYS 5
#define NUM_DIGITS 7

unsigned volatile int _scoreArray[NUM_DISPLAYS][NUM_DIGITS];
unsigned int _currentDigit;
/*
Task:
Create a test program on the pinball machine that
-cycles the score "simultaneously" on all 5 score displays
from 0 through 999999
updating once ever 500ms
with a circular increment of 8353, and an offset between displays of 8353
*/


//NOTE: When you set up the Interrupt the, use rising edge
//ie. attachInterrupt(digitalPinToInterrupt(2), ISRFunction, RISING);
void setup() {
  //Set PORTA pins to output
  pinMode(29, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(38, OUTPUT);

  //Set display 5 strobe to output
  pinMode(38, OUTPUT);
  //Set display strobe enable to output
  pinMode(A9, OUTPUT);
  //Set display blanking pin to output
  pinMode(A15, OUTPUT);

  //Set 7 Digit enable pins to output (Order is MSB to LSB/ Top Down)
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
}

//write an interrupt service routine
void loop() {
  // put your main code here, to run repeatedly:

}


void setScore(){}
void parseScore(){}
void setDisplay(){}

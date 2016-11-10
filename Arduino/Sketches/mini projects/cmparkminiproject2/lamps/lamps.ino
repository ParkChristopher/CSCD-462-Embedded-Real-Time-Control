
/**
 * @author Bruce Emehiser
 * @author Chris Park
 * @title Map Playfield Lamps
 * @date 2016 11 02
 */

#include <BallyLib.h>
#include <Printf.h>

#define CR_ROW   0    // credit
#define CR_COL   5
#define COIN_ROW 1    // coin
#define COIN_COL 0

#define TEST_BUTTON  4
#define COIN_BUTTON   8
#define CREDIT_BUTTON 16

Bally bally;

 void setup() {

//   flashLamps();
 }

void loop() {

  static int row = 0;
  static int col = 0;

  // set score display and lamp
  setScoreDisplay(row, col);
  bally.setLamp(row, col, true);

  // wait on user interaction
  int button = bally.waitForTestCreditCoin(CR_ROW, CR_COL, COIN_ROW, COIN_COL) ;

  // turn off lamp and update row and col
  bally.setLamp(row, col, false);

  if(button == CREDIT_BUTTON) {
    row = ++row >= N_LAMP_ROWS ? 0 : row;
    col = 0;
  }
  else if(button == COIN_BUTTON) {
    col = ++col >= N_LAMP_COLS ? 0 : col;
  }
  else {
    // reset button
    row = 0;
    col = 0;
  }
}

void setScoreDisplay(int row, int col) {

  const int display = 0;

  int val;
  int digit = 0;

  // check for col == zero
  if(col == 0) {
    bally.setDisplay(display, digit, col);
    digit ++;
  }

  // set col
  while(col > 0) {
    val = col % 10;
    col = col / 10;

    bally.setDisplay(display, digit, val);
    digit ++;
  }

  // add space
  digit ++;

  // check for row == zero
  if(row == 0) {
    bally.setDisplay(display, digit, row);
    digit ++;
  }

  // set row
  while(row > 0) {
    val = row % 10;
    row = row / 10;

    bally.setDisplay(display, digit, val);
    digit ++;
  }

  // zero bit to left of last digit
  bally.setDisplay(display, digit, 0);
}

void flashLamps() {
  for(int row = 0; row < N_LAMP_ROWS; row ++) {
    for(int col = 0; col < N_LAMP_COLS; col ++) {
      bally.setLamp(row, col, true);
      delay(500);
      bally.setLamp(row, col, false);
    }
  }
}
 


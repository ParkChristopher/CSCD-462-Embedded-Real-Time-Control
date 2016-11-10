/**************************************************
Reveille

***************************************************/
#include <BallyLib.h>

#define CR_ROW   0
#define CR_COL   5
#define COIN_ROW 1
#define COIN_COL 0

Bally bally ; 

// low, medium, and high bells
// note there are 4 bells, but reveille uses only 3 notes
// I tried the two possible sets for best match, which is
// why the bell numbers are placed in an array - that way
// the code below didn't need to change while I experimented.
int LMH[3] = {2,8,4} ; // {8,4,12} ; //  

void setup()
{
   Serial.begin(9600) ;
}

void loop()
{
   int button = bally.waitForTestCreditCoin(CR_ROW, CR_COL, COIN_ROW, COIN_COL) ;
   if (button==CREDIT) {
     playOne() ;
     playTwo() ;
     playTwo() ;
     playTwo() ;
     playThree() ;
     playTwo() ;
     playTwo() ;
     playTwo() ;
     playFour() ;
   }
}

void playOne()
{
   bally.fireSolenoid(LMH[0], true) ;
   delay(300) ;  
}

void playTwo()
{
   bally.fireSolenoid(LMH[1], true) ;
   delay(300) ;  
   bally.fireSolenoid(LMH[2], true) ;
   delay(150) ;  
   bally.fireSolenoid(LMH[1], true) ;
   delay(150) ;  
   bally.fireSolenoid(LMH[0], true) ;
   delay(300) ;  
   bally.fireSolenoid(LMH[2], true) ;
   delay(300) ;  
}

void playThree()
{
   bally.fireSolenoid(LMH[2], true) ;
   delay(600) ;  
   bally.fireSolenoid(LMH[1], true) ;
   delay(300) ;  
   bally.fireSolenoid(LMH[0], true) ;
   delay(300) ;  
}

void playFour()
{
   bally.fireSolenoid(LMH[1], true) ;
   delay(900) ;  
}




//Lab 3 - Class: Input
//Author: Chris Park

#define NUM_KEYS 5
#define MAX_DESC_LENGTH 7

int _adcVal, _conversionValue, _checkedKey;
int _adcValArray[NUM_KEYS] = {50, 179, 334, 526, 832};
char _adcCharArray[NUM_KEYS][MAX_DESC_LENGTH] =
  {"Right", "Up", "Down", "Left", "Select"};

/*-------------------------------------------*/

int convertKey(){
  for (int i = 0; i < NUM_KEYS; i++){
    if(_adcValArray[i] > _adcVal)
      return i;
  }
  
  return -1;
}//end covertKey

/*-------------------------------------------*/

int checkForKey(){
  static int lastKey = -1;
  
  delay(10);
  _adcVal = analogRead(0);
  _conversionValue = convertKey();

  if(_conversionValue != lastKey)
    lastKey = _conversionValue;

  return lastKey;
}//end checkForKey

/*-------------------------------------------*/

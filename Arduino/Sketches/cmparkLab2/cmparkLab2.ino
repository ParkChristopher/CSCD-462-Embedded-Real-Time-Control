//Lab 2
//Author: Chris Park

#define READ_PIN 0
#define WRITE_PIN 9
#define DELTA 100
#define NUM_SAMPLES 40
#define NUM_INDICES 256

unsigned int _minLedValue, _maxLedValue;
unsigned long _settlingTime;
bool _isVerbose;
int _lookupTable[NUM_INDICES];

/*-----------------------------------------------------*/

void setup() {
  Serial.begin(9600);

  _isVerbose = true;
}//end setup

/*-----------------------------------------------------*/

void loop() {

  requestInput("Calculate Settling Time");
  _settlingTime = getSettlingTimeMillis();
  clearBuffer();
  
  requestInput("Calculate Extreme Values");
  calculateExtremes();
  clearBuffer();
  
  requestInput("Linear Mapping and Calibration Loop");
  initLookupTable();
  linearMappingLoop();
  clearBuffer();

  requestInput("Lookup Mapping Test Loop");
  lookupTestLoop();
  clearBuffer();
}//end loop

/*-----------------------------------------------------*/

int getSampleVoltage(){
  int i;
  unsigned long res = 0;
  
  for(i = 0; i < NUM_SAMPLES; i++){
    res += analogRead(READ_PIN);
  }
  return res / (i + 1);
}//end getSampleVoltage

/*-----------------------------------------------------*/

unsigned long getSettlingTimeMillis(){
  bool isSettled;
  int prevSample, currSample;
  unsigned long startTime, endTime, sTime;

  isSettled = false;
  prevSample = currSample = 0;
  analogWrite(WRITE_PIN, 0);
  delay(1000);
  startTime = millis();
  analogWrite(WRITE_PIN, 127);

  while(!isSettled){
    currSample = getSampleVoltage();
    Serial.println(currSample);
      
    if(currSample > prevSample)
      prevSample = currSample;
    else
      isSettled = true;
  }
  
  endTime = millis();
  sTime = endTime - startTime;
  sTime += DELTA;
  Serial.print("Settling Time (msec): ");
  Serial.println(sTime);
  return sTime;
}//end estimateSettlingtime

/*-----------------------------------------------------*/

void calculateExtremes(){
  //Get minimum brightness reading
  analogWrite(WRITE_PIN, 0);
  delay(_settlingTime);
  _minLedValue = getSampleVoltage();
  Serial.print("Minimum Value: ");
  Serial.println(_minLedValue);

  //Get maximum brightness reading
  analogWrite(WRITE_PIN, 255);
  delay(_settlingTime);
  _maxLedValue = getSampleVoltage();
  Serial.print("Maximum Value: ");
  Serial.println(_maxLedValue);
}//end calculateExtremes

/*-----------------------------------------------------*/

void linearMappingLoop(){
  int i, sample;

  for(i = 0; i < NUM_INDICES; i++){
    analogWrite(WRITE_PIN, i);
    delay(_settlingTime);

    if(_isVerbose)
      Serial.print("LED=");
    Serial.print(i);
    Serial.print(", ");
    
    sample = getSampleVoltage();

    if(_isVerbose)
      Serial.print("Light=");
    Serial.print(sample);
    Serial.print(", ");
    
    sample = map(sample, _minLedValue, _maxLedValue, 0, 255);
    sample = constrain(sample, 0, 255);
    
    if(_isVerbose)
      Serial.print("LinearMapping=");
    Serial.println(sample);

    _lookupTable[sample] = i;
    
  }//end for loop
  
  backFillLookupTable();
}//end linearGuessLoop

/*-----------------------------------------------------*/

void lookupTestLoop(){
  int i, sample;

  for(i = 0; i < NUM_INDICES; i++){
    analogWrite(WRITE_PIN, i);
    delay(_settlingTime);

    if(_isVerbose)
      Serial.print("LED=");
    Serial.print(i);
    Serial.print(", ");
    
    sample = getSampleVoltage();
   
    if(_isVerbose)
      Serial.print("Light=");
    Serial.print(sample);
    Serial.print(", ");

    sample = map(sample, _minLedValue, _maxLedValue, 0, 255);
    sample = constrain(sample, 0, 255);
    
    if(_isVerbose)
      Serial.print("ReverseMapping=");
    Serial.println(_lookupTable[sample]);
  }//end for loop
  
}//end lookupTestLoop

/*-----------------------------------------------------*/

void initLookupTable(){
  for(int i = 0; i < NUM_INDICES; i++)
    _lookupTable[i] = -1;
}//end initLookupTable

/*-----------------------------------------------------*/

void backFillLookupTable(){

  //if the first index is -1, set it to zero
  if(_lookupTable[0] == -1)
    _lookupTable[0] = 0;
    
  for(int i = 1; i < NUM_INDICES; i++)
    if(_lookupTable[i] == -1)
      _lookupTable[i] = _lookupTable[i - 1];
}//end backFillLookupTable

/*-----------------------------------------------------*/

void clearBuffer(){
  while(Serial.available() > 0)
    Serial.read();
  analogWrite(WRITE_PIN, 0);
  Serial.println();
}//end clearBuffer

/*-----------------------------------------------------*/

void requestInput(char* taskStr){
  Serial.print("Next task: ");
  Serial.println(taskStr);
  Serial.println("Enter input to continue...");
  while(Serial.available() <= 0);
}//end requestInput

/*-----------------------------------------------------*/

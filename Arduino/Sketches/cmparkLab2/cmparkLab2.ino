//Lab 2
//Author: Chris Park

#define READ_PIN 0
#define WRITE_PIN 9

unsigned int _minLedValue, _maxLedValue;
unsigned long _settlingTime;

/*-----------------------------------------------------*/

void setup() {
  Serial.begin(9600);
  
  _settlingTime = getSettlingTimeMillis();
  calculateExtremes();
  
}//end setup

/*-----------------------------------------------------*/

void loop() {

  Serial.println();
  Serial.println("Enter input to begin linear mapping.");
  Serial.println();
  while(Serial.available()==0){}
  
  linearMappingLoop();
  
  Serial.read();
}//end loop

/*-----------------------------------------------------*/

int getSampleVoltage(){
  int i;
  unsigned int res = 0;
  
  for(i = 0; i < 20; i++){
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
  delay(3000);
  startTime = millis();
  analogWrite(WRITE_PIN, 127);

  while(!isSettled){
    currSample = getSampleVoltage();
      
    if(currSample > prevSample)
      prevSample = currSample;
    else
      isSettled = true;
  }
  
  endTime = millis();
  sTime = endTime - startTime;
  sTime += 50;
  Serial.print("Settling Time: ");
  Serial.println(sTime);
  return sTime;
}//end estimateSettlingtime

/*-----------------------------------------------------*/

void calculateExtremes(){
  //Get minimum brightness reading
  analogWrite(WRITE_PIN, 0);
  delay(_settlingTime);
  _minLedValue = getSampleVoltage();
  Serial.print("Minimum reading: ");
  Serial.println(_minLedValue);

  //Get maximum brightness reading
  analogWrite(WRITE_PIN, 255);
  delay(_settlingTime);
  _maxLedValue = getSampleVoltage();
  Serial.print("Maximum reading: ");
  Serial.println(_maxLedValue);

  //Reset the LED
  analogWrite(WRITE_PIN, 0);
}//end calculateExtremes

/*-----------------------------------------------------*/

void linearMappingLoop(){
  int i, sample;

  for(i = 0; i < 256; i++){
    analogWrite(WRITE_PIN, i);
    delay(_settlingTime);

    Serial.print("LED=");
    Serial.print(i);
    Serial.print(" ");
    
    sample = getSampleVoltage();
    sample = constrain(sample, _minLedValue, _maxLedValue);

    Serial.print("Light=");
    Serial.print(sample);
    Serial.print(" ");
    
    sample = map(sample, 0, 1023, 0, 255); //Is this the correct use?
    
    Serial.print("LinMap=");
    Serial.println(sample);
    
  }
  
  //Reset the LED
  analogWrite(WRITE_PIN, 0);
}//end linearGuessLoop

/*-----------------------------------------------------*/

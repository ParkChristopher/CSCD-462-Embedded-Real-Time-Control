//Lab 2
//Author: Chris Park


void setup() {
  Serial.begin(9600);
}

void loop() {
  analogWrite(9, 64);
}

//take some number of consecutive readings from the photsensor
//average those readings
//note: pwm period is 2ms

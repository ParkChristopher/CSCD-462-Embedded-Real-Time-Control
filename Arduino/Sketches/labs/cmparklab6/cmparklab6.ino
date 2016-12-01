#include <TimerOne.h>
#include <SPI.h>

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();
  TimerOne.initialize(800);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void dacWrite(unsigned int val){
  if(val > 4095) return;
  //sedn value to dac in a two byte command using the following protocol...
    //activiate spi communication to dac by sending CS Line low (from pin 8?)
}

//Chris Park
//Lab 6

#include <TimerOne.h>
#include <SPI.h>

#define MAX_INDEX 125
#define V_OUT A0
#define CS 8
#define PERIOD 800
#define PERIOD_SEC .0008
#define KP 4.5
#define KI 270
#define KD 0.01
unsigned int _rlc_data[125];
unsigned volatile int _rlc_index;

void setup() {
  
  Serial.begin(9600);
  pinMode(V_OUT, INPUT);
  pinMode(CS, OUTPUT);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();
  Timer1.initialize(PERIOD);
  dac_write(0);
}

void loop() {
  
  test_open_loop();
  request_input("Open loop test");
  clear_buffer();
  test_closed_loop();
  request_input("Closed loop test");
}

/**
 * Write a value to DAC
 */
void dac_write(unsigned int val){
  
  uint8_t config_byte;
  uint8_t dac_lower_byte;
  
  if(val > 4095){
    Serial.print("DAC value exceeds range.\r\n");
    return;
  }
  
  //Prepare
  config_byte = 0x10 | (val >> 0x08);
  dac_lower_byte = (val & 0xFF);

  //Send
  digitalWrite(CS, LOW);
  SPI.transfer(config_byte);
  SPI.transfer(dac_lower_byte);
  digitalWrite(CS, HIGH);
}

/**
 * RLC Sample ISR (Open Loop)
 */
void sample_rlc(){
  //static unsigned long response_time = 0;
  
  if(_rlc_index > 124){
    Timer1.detachInterrupt();
    Serial.print("Sampling finished.\r\n");
    return;
  }
  
  _rlc_data[_rlc_index] = analogRead(V_OUT);
  _rlc_index++;
  
  /*
  // DEBUG
  response_time = millis() - response_time;
  Serial.print("Response time: ");
  Serial.print(response_time);
  Serial.print("\r\n");
  */
}

/**
 * RLC Sample ISR (Closed Loop)
 */
void sample_rlc_closed(){
  float val;
  float val_conv;
  float err;
  float next_val;
  
  if(_rlc_index > 124){
    Timer1.detachInterrupt();
    Serial.print("Sampling finished.\r\n");
    return;
  }

  val = (analogRead(V_OUT));
  _rlc_data[_rlc_index] = val;
  
  val_conv = (val * (5.0 / 1023.0));
  err = (3 - val_conv);
  next_val = pid_compute_next(err, PERIOD_SEC, KP, KI, KD);
  dac_write(next_val);
  _rlc_index++;
}

/**
 * PID, Compute next DAC input
 */
float pid_compute_next(float err, int period, float kp, float ki, float kd){
  
  static float prev_err = 0; 
  static float cum_err = 0;
  float err_offset;
  float next_val;
  
  //Re-Initialize values
  if(period == -1){
    prev_err = cum_err = 0;
    return 0.0;
  }

  cum_err += (err * PERIOD_SEC);
  err_offset = (err - prev_err) / PERIOD_SEC;
  next_val = (kp * err) + (ki * cum_err) + (kd * err_offset);
  
  //Convert and constrain
  next_val = next_val * 1000;
  if(next_val > 4095) next_val = 4095;
  if(next_val < 0) next_val = 0;
  
  prev_err = err;
  return next_val;
}

/**
 * Test open loop response at 3 volts
 */
void test_open_loop(){
  bool done = false;
  _rlc_index = 0;
  dac_write(3000); 
  Timer1.attachInterrupt(sample_rlc);

  delay(1000);
  dac_write(0);
  print_response_values();
}

/**
 * Test closed loop response
 */
void test_closed_loop(){
  _rlc_index = 0;
  pid_compute_next(0.0, -1, 0.0, 0.0, 0.0);
  Timer1.attachInterrupt(sample_rlc_closed);

  delay(1000);
  dac_write(0);
  print_response_values();
}

/**
 * Print RLC response samples in volts
 */
void print_response_values(){
  int i;
  float volts;
  
  for(i = 0; i < MAX_INDEX; i++){
    volts = _rlc_data[i] * (5.0 / 1023.0);
    Serial.print(volts);
    Serial.print("\r\n");
  }
}

/**
 * Request user input
 */
void request_input(char* taskStr){
  Serial.print("Finished: ");
  Serial.println(taskStr);
  Serial.println("Enter single character input to continue...");
  while(Serial.available() <= 0);
}//end requestInput

/**
 * Clear serial buffer of user input.
 */
void clear_buffer(){
  while(Serial.available() > 0)
    Serial.read();
}

//Chris Park
//Lab 4

#include <ARTK.h>
#include <inline.h>
#include <kernel.h>
#include <machine.h>

#define INPUT_PIN 2

/**
 * Globals
 */
SEMAPHORE sem;

/**
 * ARTK Setup
 */
void Setup() {
  Serial.begin(9600);
  sem = ARTK_CreateSema(0);
  pinMode(INPUT_PIN, INPUT_PULLUP);
  ARTK_CreateTask(switch_monitor, 3);
  ARTK_CreateTask(consumer, 2);
  ARTK_CreateTask(busy, 1);
}

void consumer(){
  
  static uint8_t count = 0;
  
  while(true){

    ARTK_WaitSema(sem);
    Printf(F("Button press %d detected.\r\n"), (count + 1));
    count++;

    if(count == 5) ARTK_TerminateMultitasking();
  }
}

void switch_monitor(){

  static uint8_t previous = 1;
  uint8_t current = 1;
  
  while(true){
  
    current = digitalRead(INPUT_PIN);
    
    if(previous == 1 && current == 0) ARTK_SignalSema(sem);
    
    ARTK_Sleep(20);
    previous = current;
  }
}

void busy(){
 
  static int count = 0;
  
  while(true){
   
    count++;
    Printf(F("count is :%d\r\n"), count); 
    ARTK_Sleep(1000);
  }
}

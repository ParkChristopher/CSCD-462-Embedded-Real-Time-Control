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
  
  do{

    Serial.println("Waiting");
    ARTK_WaitSema(sem);
    Printf(F("Button press %d detected.\r\n"), count);
    count++;

    if(count == 4) ARTK_TerminateMultitasking();
  }while(true);
}

void switch_monitor(){

  static uint8_t previous = 1;
  uint8_t current = 1;
  
  do{
  
    current = digitalRead(INPUT_PIN);
    
    if(previous == 1 && current == 0)
      {
        Printf(F("We did it reddit!\r\n"));
        ARTK_SignalSema(sem);
      }
    
    delay(20);
    previous = current;
  }while(true);
}

void busy(){
  
  static int count = 0;
  
  do{
   
    count++;
    Printf(F("count is :%d\r\n"), count); 
    ARTK_Sleep(1000);
  }while(true);
}

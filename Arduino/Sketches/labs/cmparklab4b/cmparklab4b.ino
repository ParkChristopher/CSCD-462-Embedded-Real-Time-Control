//Chris Park
//Lab 4 B

#include <ARTK.h>
#include <inline.h>
#include <kernel.h>
#include <machine.h>

/**
 * Globals
 */
SEMAPHORE sema;

/**
 * ARTK Setup
 */
void Setup() {
  
    Serial.begin(9600);
    sema = ARTK_CreateSema(0);
    ARTK_CreateTask(high,    3);
    ARTK_CreateTask(medium,  2);
    ARTK_CreateTask(low,     1);
}

/**
 * Low Priority Task
 */
void low(){
  while(true){
  
  Printf(F("L Signaling Semaphore\r\n"));
  ARTK_SignalSema(sema);
  ARTK_Sleep(50);
  }
}

/**
 * Medium Priority Task
 */
void medium(){
  
  while(true){
    
    Printf(F("M%lu"), millis());

    for(int i = 0; i < 64; i++){
      Printf(F("."));
    }

    Printf(F("M%lu\r\n"), millis());
    ARTK_Sleep(100); //Prevent starvation
  }
}

/**
 * High Priority Task
 */

void high(){

  for(int i = 0; i < 3; i++){
    
    Printf(F("H Waiting on semaphore %d\r\n"), (i + 1));
    ARTK_WaitSema(sema);
    Printf(F("H Acquiring semaphore %d\r\n"), (i + 1));
  }

  ARTK_TerminateMultitasking();
}

//verify deadlock
//add single line to medium to prevent starving of low priority task


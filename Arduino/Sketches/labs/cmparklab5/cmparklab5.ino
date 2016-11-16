//Chris Park
//Lab 5

#include <ARTK.h>
#include <inline.h>
#include <kernel.h>
#include <machine.h>


#define NUM_CYCLES 3

SEMAPHORE sema_1;
SEMAPHORE sema_2;
SEMAPHORE sema_3;

void Setup() {
  Serial.begin(9600);
  sema_1 = ARTK_CreateSema(1);
  sema_2 = ARTK_CreateSema(1);
  sema_3 = ARTK_CreateSema(1);

  ARTK_CreateTask(phil_1, 1);
  ARTK_CreateTask(phil_2, 1);
  ARTK_CreateTask(phil_3, 1);
}

//Phil 1 picks up right first
void phil_1(){
  static int i = 0;
  
  while(i < NUM_CYCLES){

    Printf(F("Phil 1 waiting right (3)\r\n"));
    ARTK_WaitSema(sema_3);
    Printf(F("Phil 1 picked up right (3)\r\n"));

    //Introduce Deadlock
    ARTK_Yield();

    Printf(F("Phil 1 waiting for left (1)\r\n"));
    ARTK_WaitSema(sema_1);
    Printf(F("Phil 1 picked up left (1)\r\n"));

    Printf(F("Phil 1 eating...%d\r\n"), (i + 1));
    ARTK_Sleep(50);

    Printf(F("Phil 1 dropping left (1)\r\n"));
    ARTK_SignalSema(sema_1);

    Printf(F("Phil 1 dropping right (3)\r\n"));
    ARTK_SignalSema(sema_3);

    Printf(F("Phil 1 thinking...%d\r\n"), (i + 1));
    ARTK_Sleep(50);
    i++;
  }
}

void phil_2(){
  static int i = 0;
  
  while(i < NUM_CYCLES){

    Printf(F("Phil 2 waiting for left (2)\r\n"));
    ARTK_WaitSema(sema_2);
    Printf(F("Phil 2 picked up left (2)\r\n"));

    //Introduce Deadlock
    ARTK_Yield();

    Printf(F("Phil 2 waiting right (1)\r\n"));
    ARTK_WaitSema(sema_1);
    Printf(F("Phil 1 picked up right (1)\r\n"));

    Printf(F("Phil 2 eating...%d\r\n"), (i + 1));
    ARTK_Sleep(50);

    Printf(F("Phil 2 dropping left (2)\r\n"));
    ARTK_SignalSema(sema_2);

    Printf(F("Phil 2 dropping right (1)\r\n"));
    ARTK_SignalSema(sema_1);

    Printf(F("Phil 2 thinking...%d\r\n"), (i + 1));
    ARTK_Sleep(50);
    i++;
  }
}

void phil_3(){
  static int i = 0;
  
  while(i < NUM_CYCLES){

    Printf(F("Phil 3 waiting for left (3)\r\n"));
    ARTK_WaitSema(sema_3);
    Printf(F("Phil 3 picked up left (3)\r\n"));

    //Introduce Deadlock
    ARTK_Yield();
    
    Printf(F("Phil 3 waiting right (2)\r\n"));
    ARTK_WaitSema(sema_2);
    Printf(F("Phil 3 picked up right (2)\r\n"));

    Printf(F("Phil 3 eating...%d\r\n"), (i + 1));
    ARTK_Sleep(50);

    Printf(F("Phil 3 dropping left (3)\r\n"));
    ARTK_SignalSema(sema_3);

    Printf(F("Phil 3 dropping right (2)\r\n"));
    ARTK_SignalSema(sema_2);

    Printf(F("Phil 3 thinking...%d\r\n"), (i + 1));
    ARTK_Sleep(50);
    i++;
  }
}

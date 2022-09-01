#line 1 "d:\\Courses\\Embbedded and Microcontrollers\\Udemy_Embedded_System_Design_using_UML_State_Machines\\StateMachinePlayGround_Code\\UML_ProTimer\\Productivity-Timer-Using-Function-Pointers\\interface.h"
#pragma once 
#include <inttypes.h>
#include <Arduino.h> 


namespace PINS{
    const int INC_BUTT{6};
    const int DEC_BUTT{9};
    const int START_PAUSE_BUTT{8};
    const int BUZZER{10};
}
typedef enum {
    IDLE,
    TIME_SET,
    PAUSE,
    COUNT_DOWN,
    STAT
}State_t; 

typedef enum{
    RELEASED,
    PRESSED
}ButtonState_t;
typedef enum{
    INCR,
    DECR,
    START_PAUSE,
    ABRT ,
    TIME_TICK
}event_t;

typedef enum{
    HANDLED,
    IGNORED,
    TRANSITION
}EventStatus_t;

typedef struct 
{
    uint8_t sig;
}userEvent_t;

typedef struct 
{
    event_t sig;
    uint8_t ss; 
}superEvent_t;
struct ProTimer ; 
typedef void (*funptr)(superEvent_t event , struct ProTimer *proTimer) ; 
typedef struct ProTimer
{
    funptr currentState ;
    uint32_t currentTime ; 
    uint32_t elapsedTime  ; 
    uint32_t proTime ; 
}ProTimer_t;
State_t Idle_stateHandler(superEvent_t event,ProTimer_t *);
State_t TimeSet_stateHandler(superEvent_t event,ProTimer_t *);
State_t Pause_stateHandler(superEvent_t event,ProTimer_t *);
State_t CountDown_stateHandler(superEvent_t event,ProTimer_t *);
State_t Stat_stateHandler(superEvent_t event,ProTimer_t *);
ButtonState_t ButtonDebouncing(const int pin);
void buzzing();
void handleEvent(superEvent_t event , ProTimer_t *proTimer);
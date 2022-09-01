#include "LCD.h"
#include "interface.h""
uint64_t lastTime{};
uint32_t Delayms{300};
ButtonState_t incButtonState{RELEASED},decButtonState{RELEASED},startPauseButtonState{RELEASED};
ProTimer_t proTimer;
uint32_t startingTime{}; 
uint16_t oneSec{100} ; 

void setup() {
    proTimer.currentState = Idle_stateHandler;
    proTimer.proTime = 0 ; 
    pinMode(PINS::DEC_BUTT,INPUT);
    pinMode(PINS::INC_BUTT,INPUT);
    pinMode(PINS::START_PAUSE_BUTT,INPUT);
    pinMode(PINS::BUZZER,OUTPUT); 
    LCD_init();
}

void loop() {
    static superEvent_t event ; 
    if(millis()- lastTime >= Delayms)
    {
        incButtonState = ButtonDebouncing(PINS::INC_BUTT) ;
        decButtonState = ButtonDebouncing(PINS::DEC_BUTT); 
        startPauseButtonState= ButtonDebouncing(PINS::START_PAUSE_BUTT); 
        
        if(incButtonState == PRESSED &&decButtonState == PRESSED )
        {
            event.sig = ABRT;
           (*proTimer.currentState)(event,&proTimer); 
            
        }
        if(incButtonState == PRESSED)
        {
            event.sig = INCR;
            (*proTimer.currentState)(event,&proTimer); 
            
        }
        if(decButtonState == PRESSED)
        {
            event.sig = DECR;
            (*proTimer.currentState)(event,&proTimer);
            
        }
        if(startPauseButtonState == PRESSED)
        {
            event.sig = START_PAUSE;
            (*proTimer.currentState)(event,&proTimer) ;
            
        }
        lastTime = millis(); 
    }
   
    if(millis() - startingTime >= oneSec)
    {
        event.ss++; 
        if(event.ss >= 11)
            event.ss = 1 ; 
        event.sig = TIME_TICK;
        (*proTimer.currentState)(event,&proTimer);
        startingTime = millis() ; 
      
    }
}
#include "interface.h"
#include "LCD.h"
ButtonState_t  previousState{RELEASED} ; 
ButtonState_t ButtonDebouncing(const int pin)
{
    if(digitalRead(pin) == PRESSED && previousState == PRESSED)
    {
        return PRESSED; 
    }
    else if(digitalRead(pin) == PRESSED && previousState == RELEASED)
    {
        previousState = PRESSED ; 
    }
    else if(digitalRead(pin) == RELEASED && previousState == PRESSED)
    {
        previousState = RELEASED ; 
    }
    else
    {
        return RELEASED; 
    }
}

void buzzing()
{
    for(int i = 0 ; i < 50 ; i++)
    {
        digitalWrite(PINS::BUZZER , !digitalRead(PINS::BUZZER));
        delay(1);
    }
    
}


void handleEvent(superEvent_t event , ProTimer_t *proTimer)
{
    
}

State_t Idle_stateHandler(superEvent_t event , ProTimer_t *proTimer)
{
    lcd.setCursor(4,0);
                lcd.print("SET TIME");
                dispTime(0); 
                proTimer->currentTime = 0 ; 
                proTimer->elapsedTime = 0 ; 
                static int buzzerCount = 0 ; 
                switch (event.sig)
                {
                case INCR:  if( proTimer->currentTime +60 <= 59940)
                            {
                                proTimer->currentState = TimeSet_stateHandler; 
                                proTimer->currentTime += 60;
                                lcd.clear();
                                buzzerCount = 0 ; 
                            }
                            
                    break;

                case START_PAUSE:   proTimer->currentState = Stat_stateHandler ; 
                                    lcd.clear(); 
                                    
                    break;

                case TIME_TICK: if (buzzerCount <20 && event.ss%5 == 0)
                                    {
                                        buzzing(); 
                                        buzzerCount++ ;
                                    }
                                        
                    break;    
                default:
                    break;
                }
                
}
State_t TimeSet_stateHandler(superEvent_t event , ProTimer_t *proTimer)
{
    lcd.setCursor(4,0);
                lcd.print("SET TIME");
                dispTime(proTimer->currentTime); 
                switch (event.sig)
                {
                case INCR:  if( proTimer->currentTime +60 <= 59940)
                            {
                                proTimer->currentTime += 60 ; 
                            }
                    break;
                case DECR:  if( proTimer->currentTime-60 > 0)
                            {
                                proTimer->currentTime -= 60 ; 
                            }
                            else
                            {
                                proTimer->currentTime = 0 ; 
                                proTimer->currentState = Idle_stateHandler; 
                                lcd.clear(); 
                            }
                    break;
                case START_PAUSE:   proTimer->currentState = CountDown_stateHandler;   
                                    lcd.clear(); 
                    break;
                case ABRT:  proTimer->currentState = Idle_stateHandler ; 
                            proTimer->currentTime = 0 ; 
                            lcd.clear(); 
                    break;
                
                default:
                    break;
                }
}
State_t Pause_stateHandler(superEvent_t event , ProTimer_t *proTimer)
{
     lcd.setCursor(4,0);
                lcd.print("Paused");
                dispTime(proTimer->currentTime); 
                switch (event.sig)
                {
                case INCR: if( proTimer->currentTime +60 <= 59940)
                            {
                                proTimer->currentState = TimeSet_stateHandler; 
                                proTimer->currentTime += 60;
                                
                            }
                    break;
                case DECR:  if( proTimer->currentTime-60 > 0)
                            {
                                proTimer->currentTime -= 60 ; 
                                proTimer->currentState = TimeSet_stateHandler ; 

                            }
                            else
                            {
                                proTimer->currentTime = 0 ; 
                                proTimer->currentState = Idle_stateHandler ; 
                                lcd.clear() ; 
                            }
                            
                    break;
                case START_PAUSE:   proTimer->currentState = CountDown_stateHandler ; 
                                    lcd.clear() ; 
                    break;
                case ABRT:  proTimer->currentState = Idle_stateHandler ; 
                            proTimer->currentTime = 0  ; 
                            lcd.clear() ; 
                    break;
                  
                default:
                    break;
                }
}
State_t CountDown_stateHandler(superEvent_t event , ProTimer_t *proTimer)
{
                
                lcd.setCursor(6,0) ;
                lcd.print("Time"); 
                dispTime(proTimer->currentTime); 
         
                switch (event.sig)
                {
                case START_PAUSE:
                                proTimer->proTime += proTimer->elapsedTime;
                                proTimer->elapsedTime = 0 ; 
                                proTimer->currentState = Pause_stateHandler;
                                 proTimer->proTime += proTimer->elapsedTime;
                                 proTimer->elapsedTime = 0 ; 
                                lcd.clear() ;  
                    break;
                case ABRT:  
                                proTimer->proTime += proTimer->elapsedTime;
                                proTimer->elapsedTime = 0 ; 
                                proTimer->currentState = Idle_stateHandler ; 
                    break;
                case TIME_TICK: if(event.ss == 10) 
                                {
                                    proTimer->currentTime -= 1 ; 
                                    proTimer->elapsedTime += 1 ; 
                                    if(proTimer->currentTime == 0 )
                                    {
                                        proTimer->currentState = Idle_stateHandler ; 
                                        proTimer->proTime += proTimer->elapsedTime;
                                        proTimer->elapsedTime = 0 ; 
                                    }
                                }
                    break;    
                default:
                    break;
                }
}
State_t Stat_stateHandler(superEvent_t event , ProTimer_t *proTimer)
{
    lcd.setCursor(1,0);
                lcd.print("Productive Time");
                dispTime(proTimer->proTime);
                switch (event.sig)
                {
                case TIME_TICK:if(event.ss ==10 )
                                {  proTimer->currentState = Idle_stateHandler ; 
                                    lcd.clear();
                                } 
                    break;  
                default:
                    break;
                }
}
# 1 "d:\\Courses\\Embbedded and Microcontrollers\\Udemy_Embedded_System_Design_using_UML_State_Machines\\StateMachinePlayGround_Code\\UML_ProTimer\\Productivity-Timer-Using-Function-Pointers\\LCD.cpp"
# 2 "d:\\Courses\\Embbedded and Microcontrollers\\Udemy_Embedded_System_Design_using_UML_State_Machines\\StateMachinePlayGround_Code\\UML_ProTimer\\Productivity-Timer-Using-Function-Pointers\\LCD.cpp" 2

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void LCD_init()
{
    lcd.begin(16,2);
    lcd.clear();
    lcd.setCursor(0,0);
}

void dispTime( uint32_t s)
{
    int mm = s/(int)60;
    int ss = s - mm*60 ;
    int i = 10 ;
    lcd.setCursor(i,1);
    while(ss>0 || i>8)
    {
        lcd.print(ss%10);
        ss/=10;
        i--;
        lcd.setCursor(i,1);
    }
    lcd.print(":");
    while(i>5)
    {
        i--;
        lcd.setCursor(i,1);
        lcd.print(mm%10);
        mm/=10;
    }
}
# 1 "d:\\Courses\\Embbedded and Microcontrollers\\Udemy_Embedded_System_Design_using_UML_State_Machines\\StateMachinePlayGround_Code\\UML_ProTimer\\Productivity-Timer-Using-Function-Pointers\\UML_ProTimer_functionPointers.ino"

# 3 "d:\\Courses\\Embbedded and Microcontrollers\\Udemy_Embedded_System_Design_using_UML_State_Machines\\StateMachinePlayGround_Code\\UML_ProTimer\\Productivity-Timer-Using-Function-Pointers\\UML_ProTimer_functionPointers.ino" 2
uint64_t lastTime{};
uint32_t Delayms{300};
ButtonState_t incButtonState{RELEASED},decButtonState{RELEASED},startPauseButtonState{RELEASED};
ProTimer_t proTimer;
uint32_t startingTime{};
uint16_t oneSec{100} ;

void setup() {
    proTimer.currentState = Idle_stateHandler;
    proTimer.proTime = 0 ;
    pinMode(PINS::DEC_BUTT,0x0);
    pinMode(PINS::INC_BUTT,0x0);
    pinMode(PINS::START_PAUSE_BUTT,0x0);
    pinMode(PINS::BUZZER,0x1);
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

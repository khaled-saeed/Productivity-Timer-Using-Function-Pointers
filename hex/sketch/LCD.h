#line 1 "d:\\Courses\\Embbedded and Microcontrollers\\Udemy_Embedded_System_Design_using_UML_State_Machines\\StateMachinePlayGround_Code\\UML_ProTimer\\Productivity-Timer-Using-Function-Pointers\\LCD.h"
#pragma once 

#include <LiquidCrystal.h>
#include <Arduino.h> 

extern LiquidCrystal lcd;
void LCD_init();
void dispTime( uint32_t s); 
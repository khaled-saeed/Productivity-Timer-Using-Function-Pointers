#pragma once 

#include <LiquidCrystal.h>
#include <Arduino.h> 

extern LiquidCrystal lcd;
void LCD_init();
void dispTime( uint32_t s); 
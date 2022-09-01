#include "LCD.h"

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
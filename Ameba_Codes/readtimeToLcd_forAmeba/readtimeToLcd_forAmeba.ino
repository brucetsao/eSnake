 
#include <Wire.h>
#include "RTClib.h"

#include <LiquidCrystal_I2C.h>

RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup () {
    Serial.begin(9600);
    lcd.begin(16,2);               // initialize the lcd 
    lcd.backlight();    //背光
   lcd.clear();   //清除
   lcd.setCursor( 0, 0 );   //歸零點

    Wire1.begin();
    RTC.begin();
     RTC.adjust(DateTime(__DATE__, __TIME__));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void loop () {
    DateTime now = RTC.now(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
     lcd.setCursor( 0, 0 );   //歸零點
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
 
    //-------------
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); 
     lcd.setCursor( 0, 1 );   //歸零點
       lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
  
    delay(1000);
}

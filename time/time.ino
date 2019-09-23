#include <DateTime.h>
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void setup(){
 //lcd.begin(16, 2);
 DateTime.sync(812868312);
}
void  loop(){     
 if(DateTime.available()) { 
   unsigned long prevtime = DateTime.now(); 
   while( prevtime == DateTime.now() )
     ;
   DateTime.available();
   digitalClockDisplay();
 } 
}

void printDigits(byte digits){
 //lcd.print(":");
 Serial.print(":");
 if(digits < 10)
   Serial.print('0');
 Serial.print(digits,DEC);
}

void digitalClockDisplay(){
 //lcd.home();
 // digital clock display of current time
 Serial.print(DateTime.Hour,DEC);  
 printDigits(DateTime.Minute);  
 printDigits(DateTime.Second);
}

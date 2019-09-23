#include <LiquidCrystal.h>
#include<SoftwareSerial.h>

SoftwareSerial ArduinoUno(8,7);
    String msg;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  analogWrite(6,20);
  lcd.begin(16, 2);
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("MainNode");
  delay(3000);
  Serial.begin(9600);
ArduinoUno.begin(4800); 
}

void loop() {
 
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MainNode");
  delay(1000);
  lcd.setCursor(0,1);
   
String s;
   if(ArduinoUno.available()>0)
   {
   
   while(ArduinoUno.available()>0){
    
    s +=(char)ArduinoUno.read();
  }
   Serial.println(s);
  msg=s;
}

lcd.print(msg);
delay(1000);
}

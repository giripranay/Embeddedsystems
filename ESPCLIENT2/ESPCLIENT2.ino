#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 8, 7);
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
int c=0;                           // and the RX line from the esp to the Arduino's pin 3
void setup()
{
 // int c=0;
 analogWrite(6,20);
  lcd.begin(16, 2);
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("CLIENT1");
  delay(3000);
  //////////////////////
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  esp8266.println("AT");
  delay(500);
  c++;
  esp8266.println("AT+CWMODE=1");
  delay(500);
  c++; 
  String s1="AT+CWJAP=";
  String s2="ESPSERVER";
  String s3=s1+'"'+s2+'"'+','+'"'+'"';
  esp8266.println(s3);
  delay(500);
  c++;
  if(c==3)
  {
  //  delay(5000);
    tcp();
    }
}

void tcp()
{
  delay(5000);
  String s4="AT+CIPSTART=";
  String s5="TCP";
  String s6="192.168.4.1";
  String s7="80"; 
  String s8=s4+'"'+s5+'"'+','+'"'+s6+'"'+','+s7;
  esp8266.println(s8);
  //Serial.println(s8);
  delay(5000);
  esp8266.println("AT+CIPSEND=25");
  delay(500);
  ///////////////////////////
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CLIENT1");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("SENDING DATA");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("HI SERVER,I AM CLIENT");
  delay(1000);
  /////////////////////////////////////
  esp8266.println("hi server!, i am client2.");
  delay(500);
  esp8266.println("AT+CIPCLOSE=0");
  delay(3000);
  tcp();
  }
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    }  

  }
 
  
  if(Serial.available())
  {
    // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    delay(1000); 
    
    String command="";
    
    while(Serial.available()) // read the command character by character
    {
        // read one character
      command+=(char)Serial.read();
    }
    esp8266.println(command);
  }
}

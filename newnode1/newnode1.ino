#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2  
String command;// and the RX line from the esp to the Arduino's pin 3
int c=0;
void setup()
{
 
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  comm();
  
}

void comm()
{
  if(c==0)
  {
    esp8266.println("ATE0");
    c=c+1;
    delay(1000);
    comm();
    }
  if(c==1)
  {
    String s1="AT+CWJAP=";
    String s2="GATEWAY";
    String s3=s1+'"'+s2+'"'+','+'"'+'"';
    esp8266.println(s3);
    c=c+1;
    delay(5000);
    comm();
    }
  if(c==2)
  {
    esp8266.println("AT+CIPMUX=1");
    c=c+1;
    delay(1000);
    }  
  }


void tcp()
{
  String s4="AT+CIPSTART=0,";
  String s5="TCP";
  String s6="192.168.4.1";
  String s7="80"; 
  String s8=s4+'"'+s5+'"'+','+'"'+s6+'"'+','+s7;
  esp8266.println(s8);
 // Serial.println(s8);
  delay(1000);

  esp8266.println("AT+CIPSEND=0,5");
  delay(2000);
  esp8266.println("node1");
  delay(1000);
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c=esp8266.read(); // read the next character.
      Serial.write(c);
    }  
  }

  
}

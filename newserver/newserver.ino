#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
int storage[10];// and the RX line from the esp to the Arduino's pin 3  
String command;
int f1=0;
int node=0;
void setup()
{
  for(int i=0;i<10;i++)
{
  storage[i]=-1;
  }

  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  esp8266.println("ATE0");
  delay(1000);
  esp8266.println("AT");
  delay(1000);
  esp8266.println("AT+CIPMUX=1");
  delay(1000);
  esp8266.println("AT+CIPSERVER=1,80");
  delay(5000);
  
}


void store()
{
int var=atoi(&command[7]);
storage[var]=var;
node=node+1;
if(node==1)
  {
//  Broadcast();
  }
}

void Broadcast()
{
  //Serial.println(node);
  delay(8000);
  for(int i=0;i<node;i++)
  {
  esp8266.println("AT+CIPSEND=i,5");
  delay(3000);
  esp8266.println("+SEND");
  delay(1000);
    }
  
  }
 
void loop()
{
  
  if(esp8266.available()) // check if the esp is sending a message 
  {
    delay(1000);
    command="";
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      command+=(char)esp8266.read(); // read the next character.
      
    }  
    Serial.println(command);
    delay(500);
    if(f1==1)
    {
      store();
      f1=0;
      }
    if(command[0]=='L')
     {
      f1=1;
     }
     
  }
 
  
}


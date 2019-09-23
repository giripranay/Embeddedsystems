 #include <SoftwareSerial.h>

SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
int c1=0,c2=0,c3=0,flag=1,count=0,flag2=0,flag3=0;

void setup()
{
  
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  esp8266.println("AT+CWMODE?");
  delay(100);
  esp8266.println("AT+CWLAP");

  //delay(5000);
  //setup();
  

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
    /*   if(c=='"')
      {
       count++;
      }
   int r=count%2;
      int q=count/2;
       if(r==1 && q%2==0)
      {
        Serial.write(c);
      }
     */
      
      
    } }
    
  
}



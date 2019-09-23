#include <SoftwareSerial.h>

SoftwareSerial esp8266(2,3);

void setup() {

  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  esp8266.println("AT+RST");
  delay(1000);
  esp8266.println("AT+CWMODE=3");
  delay(1000);
 // esp8266.println("AT+CIPMUX=1");
  //delay(1000);
  esp8266.println("AT+CIFSR");
  // put your setup code here, to run once:

}

void loop() {

  if(esp8266.available()) // check if the esp is sending a message 
  {
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
     Serial.write(c);
    }
  }
  // put your main code here, to run repeatedly:

}

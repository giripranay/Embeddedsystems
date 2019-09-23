#include <SoftwareSerial.h>
SoftwareSerial esp8266(2,3);

String ssid="giri";
String psd="abcd1234";
String k='"'+ssid+'"'+','+'"'+psd+'"';
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
esp8266.begin(9600); // your esp's baud rate might be different
esp8266.println(k);
esp8266.println("AT+CWSAP="+k+",5,3");


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

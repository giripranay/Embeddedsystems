#include<SoftwareSerial.h>
#include<ESP8266WiFi.h>

SoftwareSerial nodemcu(D2,D3);

void setup() {
  Serial.begin(9600);
  nodemcu.begin(4800);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);

}

void loop(){ 

  
  nodemcu.print("10");
  nodemcu.println("\n");
  delay(3000);
}


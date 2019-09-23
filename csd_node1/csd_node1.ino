
#include<SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial nodemcu(D2,D3);

//char node='1';

WiFiServer server(80);
IPAddress IP(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);



void setup() {
  Serial.begin(9600);
    nodemcu.begin(4800);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("mainnode", "12345678");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
   pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);

//  pinMode(ledPin, OUTPUT);
 /* Serial.println();
  Serial.println("accesspoint_bare_01.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
*/
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}
//  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');
  //Serial.println("********************************");
  Serial.println(request);
  client.flush();
  nodemcu.print(request);
 // Serial.print("Byte sent to the repeater: ");
  //Serial.println(client.println("hii client\r"));
  //digitalWrite(ledPin, HIGH);
}

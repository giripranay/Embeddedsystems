/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "192.168.4.1";           // SSID of your AP
char pass[] = "12345678";         // password of your AP

IPAddress server(192,168,4,1);     // IP address of the AP
WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
}

void loop() {
  client.connect(server, 80);
  //digitalWrite(ledPin, LOW);
  Serial.println("********************************");
  int x=analogRead(A0);
  String y=String(x);
  Serial.print("Byte sent to the repeater: ");
  Serial.println(client.print("10 ....="+y+"\r"));
  
  //String answer = client.readStringUntil('\r');
  //Serial.println("From the repeater: " + answer);
  client.flush();
  //digitalWrite(ledPin, HIGH);
  client.stop();
  delay(1000);
}


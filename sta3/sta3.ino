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
int c;

void setup() {
  c=0;
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
  String msg="S,46";
  /*
if(Serial.available()>0)
{
delay(1000);
  while(Serial.available()>0)
  {
    msg +=(char)Serial.read();
    }*/
   msg.trim();
  client.connect(server, 80);
  //digitalWrite(ledPin, LOW);
  Serial.println("********************************");
  //c=c+1;
 // String k=String(c);
 // Serial.print("Byte sent to the repeater: ");
 // Serial.println(client.print("1 hiiserver from station 2|"+k+"\r"));
  Serial.print("Message sent:");
  Serial.print(msg);
  client.println(msg+"\r");
  //String answer = client.readStringUntil('\r');
  //Serial.println("From the repeater: " + answer);
  client.flush();
  //digitalWrite(ledPin, HIGH);
  client.stop();
  delay(10000);

}


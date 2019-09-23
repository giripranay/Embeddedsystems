/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>


char ssid[] = "192.168.4.3";           // SSID of your AP
char pass[] = "12345678";         // password of your AP

IPAddress server(192,168,4,3);     // IP address of the AP
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

  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
 
}

void loop() {
   String msg;
/*if(Serial.available()>0)
{
delay(1000);
  while(Serial.available()>0)
  {
    msg +=(char)Serial.read();
    }
   msg.trim();*/
   delay(2000);
   
   msg="helllo";
  client.connect(server, 80);
  
//  Serial.println("********************************");
 
  Serial.print("Message sent:");
  Serial.println(msg);
  client.println(msg);
 
  client.flush();
 
  client.stop();

//}
}



#include<ESP8266WiFi.h>
#include <WiFiUdp.h>

char node='1';
int f=0;

WiFiServer server(80);
IPAddress IP(192,168,4,1);
IPAddress mask = (255,255,255,0);  

//char ssid[]="";        
//char pass[] = "12345678";

const char* const ssid = "green"; // Your network SSID (name)
const char* const pass = "12345678"; // Your network password


int n_id;

String table="";
WiFiClient clientAP;
WiFiClient clientSTA;

void setup() {

 Serial.begin(9600);
 WiFi.mode(WIFI_STA);
 
 
 int n = WiFi.scanNetworks(); 
 if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.println("Available NODES");
    for (int i = 0; i < n ; ++i)
    {
      table=table+String(WiFi.SSID(i));
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print("NODE ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      table=table+String(WiFi.RSSI(i));
      Serial.println(")");
  }
 
}
}
void loop()
{
  
  
  
 
 
  
  
  }


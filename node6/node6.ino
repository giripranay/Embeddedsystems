/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/station-class.rst
 *  Works with: accesspoint_bare_01.ino
 */

#include <ESP8266WiFi.h>

char node='6';
int n_id;

char ssid[12];        
char pass[] = "12345678"; 

WiFiServer server(80);
IPAddress IP(192,168,4,6);
IPAddress mask = (255, 255, 255, 0);

WiFiClient clientAP;
WiFiClient clientSTA;


void setup() {
  
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("192.168.4.6", "12345678");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();

}



void sentof(String request)
{
String x="192.168.4.";
  
n_id=int(request[0])-48;

x =x+request[0];
x.trim();

int n = WiFi.scanNetworks();
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    int flag=0;
    for (int i = 0; i < n; ++i)
    {
      
      if(WiFi.SSID(i)==x)
      {
        flag=1;
        Serial.print("NODE found: ");
        Serial.println(request[0]);
       }
      }
     if(flag==0)
     {
      for (int i = 0; i < n; ++i)
      {
        if(WiFi.SSID(i)[3]=='.' && WiFi.SSID(i)[7]=='.' && WiFi.SSID(i)[9]=='.' && WiFi.SSID(i)[10]!=request[1])
        {
          x=WiFi.SSID(i);
          n_id=int(WiFi.SSID(i)[10])-48;
          }
        }
      
      }
    
    }
  x.trim();
  x.toCharArray(ssid,12);

 IPAddress source(192,168,4,n_id); 

 WiFi.mode(WIFI_STA);
  delay(500);
  
 WiFi.begin(ssid,pass); 
 
 while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("*****************************");
  Serial.println("Connected");
  

/////////////////////////////////////////////
  clientSTA.connect(source, 80);
 // Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(clientSTA.print(request + "\r"));
  //String answer = clientSTA.readStringUntil('\r');
  //Serial.println("From the AP: " + answer);
  clientSTA.flush();
  //Serial.print("Byte sent to the station: ");
  //Serial.println(client.println(answer+"\r"));
  clientSTA.stop();


  
 WiFi.mode(WIFI_AP);
 WiFi.softAP("192.168.4.6", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
}



void loop() {


String msg;

if(Serial.available()>0)
  {
  delay(1000);
  while(Serial.available()>0)
    {
      msg +=(char)Serial.read();
    }
  Serial.println(msg);

  msg[1]=node;
  msg.trim();
  
  sentof(msg);
  }

/////////////////////////////////////////////////////
  clientAP = server.available();
  if (!clientAP) {return;}
  String request = clientAP.readStringUntil('\r');
  Serial.println("From the station: " + request);
 
  if(request[0]=='5')
  {
    Serial.println("Packet was sent to me");
    Serial.println(request);
   }
  else
  {
    request[1]=node;
  sentof(request);
  }
  clientAP.flush();

/////////////////////////////////////////////////////////////////  








}


#include<ESP8266WiFi.h>
#include <WiFiUdp.h>

char node='1';
int f=0;


WiFiServer server(80);
IPAddress IP(192,168,4,1);
IPAddress mask = (255,255,255,0);  
 IPAddress source(192,168,4,2);

char ssid[]="";        
char pass[] = "12345678";
static uint32_t nextTime = 0;
const uint32_t stepDuration = 20000;

const char* const ss = "192.168.4.2"; // Your network SSID (name)
const char* const pa = "12345678"; // Your network password






WiFiClient clientAP;
WiFiClient clientSTA;

void setup() {

 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("192.168.4.1", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();


  
}


void sentof(String request)
{

WiFi.mode(WIFI_STA);
     delay(500);

     Serial.println(F("Sending  to 2..."));
  //Serial.println(ss);
  WiFi.begin(ss, pa);
while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  clientSTA.connect(source, 80);

  Serial.print("Byte sent: "+request);
  Serial.println(clientSTA.print(request+"\r"));
  Serial.println("Sent");
  clientSTA.flush();
 
  clientSTA.stop();


 WiFi.mode(WIFI_AP);
 WiFi.softAP("192.168.4.1", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
}

void loop()
{
  
 String msg;

if(Serial.available()>0)
  {
  delay(1000);
  while(Serial.available()>0)
    {
      msg +=(char)Serial.read();
    }
 
  msg.trim();
  Serial.println(msg);

  if(f==0)
  {
  sentof(msg);
  }
  else{
    Serial.println("Sent to BaseStation");
    }
  }



  if (millis()>=nextTime && f==1)
  {
    f=0;
    WiFi.mode(WIFI_STA);
     delay(500);

     Serial.print(F("Connecting to "));
  Serial.println(ss);
  WiFi.begin(ss, pa);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  clientSTA.connect(source, 80);
 
  Serial.println(clientSTA.print("AT\r"));
 
  clientSTA.flush();
 
  clientSTA.stop();

   WiFi.mode(WIFI_AP);
 WiFi.softAP("192.168.4.1", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();

  Serial.println("Chain Head Exchanged to 2");

    }





  
  clientAP = server.available();
  if (!clientAP) {return;}
  String request = clientAP.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("Message: " + request);
  
   
   if(f==1){
    
    Serial.println("Sent to BaseSation");
    }
   
   
   if(request=="AT" && f==0)
{
  f=1;
  Serial.println("Chain Head:1");
  nextTime=millis()+stepDuration;
  }
  
  if(f==0)
  {
    sentof(request);
    }
  


  }


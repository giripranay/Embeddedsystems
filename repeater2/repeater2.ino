#include<ESP8266WiFi.h>

node='4';

WiFiServer server(80);
IPAddress IP(192,168,4,4);
IPAddress mask = (255,255,255,0);  


char ssid[12];        
char pass[] = "12345678"; 

int n_id;


WiFiClient clientAP;
WiFiClient clientSTA;

void setup() {

 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("192.168.4.4", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();

 Serial.println("IP: ");     Serial.println(WiFi.softAPIP());
 Serial.println("MAC:");     Serial.println(WiFi.softAPmacAddress());
/*
 WiFi.begin(ssid, pass); 
 
 while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("*****************************");
  Serial.println("Connected");
  
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
 
*/
}


void sentof(String request)
{

n_id=int(request[0])-48;

String x="192.168.4.";

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
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(clientSTA.print(request + "\r"));
  String answer = clientSTA.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  clientSTA.flush();
  //Serial.print("Byte sent to the station: ");
  //Serial.println(client.println(answer+"\r"));
  clientSTA.stop();


  
 WiFi.mode(WIFI_AP);
 WiFi.softAP("192.168.4.4", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
}

  
  

void loop() { 

  char buf[50];
  clientAP = server.available();
  if (!clientAP) {return;}
  String request = clientAP.readStringUntil('\r');
  Serial.println("********************************");
  Serial.println("From the station: " + request);
 
  if(request[0]=='4')
  {
    Serial.println("Packet was sent to me");
    }
  else
  {
    request[1]=node;
  sentof(request);
  }
  clientAP.flush();
  
  
}

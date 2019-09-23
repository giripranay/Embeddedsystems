#include<ESP8266WiFi.h>
//char node='2';

WiFiServer server(80);
IPAddress IP(192,168,4,2);
IPAddress mask = (255,255,255,0);  


char ssid[]="mainnode";        
char pass[] = "12345678"; 




WiFiClient clientAP;
WiFiClient clientSTA;

void setup() {

 Serial.begin(9600);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("relay", "12345678");
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



 IPAddress source(192,168,4,1); 
 
  
 WiFi.mode(WIFI_STA);
  delay(500);
  
  WiFi.begin(ssid,pass); 
 
 while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 // Serial.println("*****************************");
  //Serial.println("Connected");
  

/////////////////////////////////////////////
  clientSTA.connect(source, 80);
 // Serial.println("********************************");
 Serial.print("Byte sent to the AP: ");
  Serial.println(clientSTA.print(request + "\r"));
 // String answer = clientSTA.readStringUntil('\r');
  //Serial.println("From the AP: " + answer);
  clientSTA.flush();
  //Serial.print("Byte sent to the station: ");
  //Serial.println(client.println(answer+"\r"));
  clientSTA.stop();


  
 WiFi.mode(WIFI_AP);
 WiFi.softAP("relay", "12345678");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
}

  
  

void loop() { 


  
  clientAP = server.available();
  if (!clientAP) {return;}
  String request = clientAP.readStringUntil('\r');
  //Serial.println("********************************");
  Serial.println("From the station: " + request);
 
  sentof(request);
  
  clientAP.flush();
  
}

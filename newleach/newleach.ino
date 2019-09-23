#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


const char* ssid = "green";
const char* password = "12345678";

WiFiClient client;

const uint16_t localPort = 54321;

const uint32_t stepDuration =10000,broadduration=60000;

IPAddress broadcastAddress;
IPAddress source(192,168,4,3); 

WiFiUDP udp;

char packetBuffer[255];

char broadcast[]="Broad";
bool sendpacket();
int count=1,flag,f;
static uint32_t next=broadduration;
String finalrep;
int pcount=0;

void setup()
{
  
   Serial.begin(115200);
  Serial.println();
  finalrep="L,1,28,28";
  // Serial.setDebugOutput(true);
  WiFi.mode(WIFI_STA);
 
   Serial.print(F("Connecting to "));
 Serial.println(ssid);
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print('.');
  }
  
  Serial.println("");
  //Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());


   broadcastAddress = (uint32_t)WiFi.localIP() | ~((uint32_t)WiFi.subnetMask());
   Serial.print(F("Broadcast address: "));
   Serial.println(WiFi.subnetMask());



 Serial.println(F("Starting UDP"));
  udp.begin(localPort);
  Serial.print(F("Local port: "));
  Serial.println(udp.localPort());

flag=1;
f=1;   
  }

int node=0;
String A;

void loop()
{



if(flag==1)
{
static uint32_t nextTime = 0;
  if (millis() >= nextTime) {
      
      WiFi.disconnect();    
      delay(500);
      WiFi.begin("192.168.4.3","12345678");
      while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print('.');
  }
  
      client.connect(source, 80);
  
  Serial.print("Message sent:");
  Serial.println(finalrep);
  pcount=pcount+1;
  Serial.print("Count:");
  Serial.println(pcount);
  client.println(finalrep);
  client.flush();
  client.stop();
    //  Serial.println(finalrep); 

       WiFi.disconnect();
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print('.');
  }
      
      sendpacket();
      finalrep="L,1";
      nextTime = millis() + stepDuration;
  }



  if (millis() >= next) {
      char numcheck[]="HeadDead";
      udp.beginPacket(broadcastAddress, localPort);
      delay(5000);
      udp.write(numcheck);
      udp.endPacket();
      Serial.println("HeadDead");
      flag=3;
      A="";
      return;
  }
  

  
int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.print("Contents:");
    Serial.println(packetBuffer);
    finalrep=finalrep+","+String(packetBuffer);
  }
}
 
  /*String message=String(packetBuffer);
  
  if(message=="numcheck")
  {
    count=count+1;
    broadcast[]="numcheck";
    sendpacket();
    }
  */

if(flag==0)
{
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.print("Contents:");
    Serial.println(packetBuffer);
  

String message=String(packetBuffer);
  
  if(message=="HeadDead")
  {
    delay(2000);
    message="1"+String(count);   
   char  reply[10];
   for (int j=0;j<10;j++)
    {
      reply[j]=message[j];
    }
  udp.beginPacket(udp.remoteIP(), 54321);
  udp.write(reply);
  udp.endPacket();
 Serial.println("RequestSent");
 flag=3;
  }

if(message=="Broad" || message=="Broad2" || message=="Broad3")
{

  
 // char reply[]="Reply1";
 char reply[3];
int ran=random(25,39);
//ran.toCharArray(reply,2);
String sran=String(ran);
sran.toCharArray(reply,3);
  udp.beginPacket(udp.remoteIP(), 54321);
  udp.write(reply);
  udp.endPacket();
  Serial.println("Reply sent");
}
  }
}




if(flag==3 && f==1){
  

  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    int len = udp.read(packetBuffer, 255);
    if (len > 0 && len==2) {
      packetBuffer[len] = 0;
    
    Serial.print("Contents:");
    Serial.println(packetBuffer);

    if(String(packetBuffer)=="OK")
    {
      flag=0;
      f=0;
      return;
      }  
    A=A+String(packetBuffer);
    Serial.println(A);
    
    node=node+1;
    }

    
    if(node==2)
    {
      Serial.println(A);
      char b;
      int(A[1])<=int(A[3])?b=A[0]:b=A[2];
      node=0;
      String S=String(b)+"Selected";
      S.trim();
      Serial.println(S);
      char  rep[9];
   for (int j=0;j<9;j++)
    {
      rep[j]=S[j];
    }
      
      udp.beginPacket(broadcastAddress, localPort);
      udp.write(rep, sizeof(rep));
      udp.endPacket();
           
      }
    
  }
}


if(flag==3 && f==0){

int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.print("Contents:");
    Serial.println(packetBuffer);
  

String message=String(packetBuffer);

message.trim();
if(message=="1Selected")
{
  count=count+1;
  flag=1;
  f=1;
  udp.beginPacket(udp.remoteIP(), 54321);
  udp.write("OK");
  udp.endPacket();
  
  next=millis()+broadduration;
  }

if(message!="1Selected")
{
  flag=0;
  f=0;
  }
  
  }  
}
 


  
  }

bool sendpacket()
{
   udp.beginPacket(broadcastAddress, localPort);
   udp.write(broadcast, sizeof(broadcast));
   Serial.println("Broadcast Sent");
  // broadcast[]="Broad";
   return (udp.endPacket() == 1);
  }
  
  
  
  
  
  

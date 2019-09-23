#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


#define MASTER // Comment this define to compile sketch on slave device

//SSID and Password to your ESP Access Point
const char* ssid = "giri";
const char* password = "12345678";
unsigned long t=millis(),b=0;


WiFiClient client;

const uint16_t localPort = 54321; // Local port to listen for UDP packets //const for reaDONLY N=MODE IF VARIABLE

#ifdef MASTER //if master has defined currently compile the block
const uint32_t stepDuration = 2000;

IPAddress broadcastAddress;
#endif

WiFiUDP udp;
int i;

bool sendPacket(const IPAddress& address, const char* buf, uint8_t bufSize);
void receivePacket();
char packetBuffer[255]; //buffer to hold incoming packet

void setup() {

  i=0;
  Serial.begin(115200);
  Serial.println();
 
   Serial.println("Configuring access point...");
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);
  //delay(1000);
  
 
  Serial.print("AP IP address: ");
//  Serial.println(myIP);
  delay(500);
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());//if of nodemcu

#ifdef MASTER
  broadcastAddress = (uint32_t)WiFi.localIP();
  Serial.print(F("Broadcast address: "));
  Serial.println(broadcastAddress);
#endif

 Serial.println(F("Starting UDP"));
  udp.begin(localPort);
  Serial.print(F("Local port: "));
  Serial.println(udp.localPort());


 

 
}

void loop() {
  
 
 String message ;
#ifdef MASTER
  static uint32_t nextTime = 0;
  const char* const info="broadcasting msg";
  if (millis() >= nextTime) {
   
    if (! sendPacket(broadcastAddress, (char*)&info, sizeof(info)))
      Serial.println(F("Error sending broadcast UDP packet!"));
    nextTime = millis() + stepDuration;
 
 }

 
#endif

// if there's data available, read a packet
  int packetSize = udp.parsePacket();
  if (packetSize) {
    //Serial.print("Received packet of size ");
  //Serial.println(packetSize);
   // Serial.print("From ");
    //IPAddress remoteIp = udp.remoteIP(); //the one which is sending now.
   // Serial.print(remoteIp);
    //Serial.print(", port ");
    //Serial.println(udp.remotePort());

    // read the packet into packetBufffer
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    message=String(packetBuffer);
    i=i+1;
    String count=String(i);
    Serial.println("i value");
    Serial.println(count);
    String packet = "/sensor/" + message+"-"+count;
   //delay(1000);
 

  Serial.println(packet);
 
  }

  if (udp.parsePacket())
    receivePacket();
 
 }

bool sendPacket(const IPAddress& address, const char* buf, uint8_t bufSize) {
  udp.beginPacket(address, localPort);
  udp.write(buf, bufSize);
  return (udp.endPacket() == 1);
}

void receivePacket() {
  char info;

  //udp.read((char*)&info, sizeof(info));
  //Serial.println(readpack);
  //udp.flush();
#ifdef MASTER
  if (udp.destinationIP() != broadcastAddress) {
    Serial.print(F("Client with IP "));
    Serial.print(udp.remoteIP());
    Serial.print(F(" connected "));

  } else {
    Serial.println(F("Skip broadcast packet"));
  }
//#else
  //digitalWrite(ledPin, led);
  //led = digitalRead(ledPin);
  //Serial.print(F("Turn led "));
  //Serial.println(led ? F("off") : F("on"));
 // if (! sendPacket(udp.remoteIP(), (uint8_t*)&led, sizeof(led)))
   // Serial.println(F("Error sending answering UDP packet!"));
#endif
} 


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "giri";
const char *password = "12345678";

unsigned long t;

WiFiUDP Udp;
unsigned int localUdpPort = 54321;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the msg---1:-)";  // a reply string to send back
void message();
int c=0,f=1;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{
  
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    delay(1000);
    if(f%2!=0)
    {
    IPAddress IP(0, 0, 0, 0);
    Udp.beginPacket(IP, Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
    c=c+1;
    Serial.print("count");
    Serial.println(c);
    f=f+1;
    }
    //delay(2000);
    // send back a reply, to the IP address and port we got the packet from
    
  }
}

void message()
{    
    Serial.println("msgsent_count"); 
    c=c+1;
    Serial.println(c);
    IPAddress IP(0, 0, 0, 0);
    Udp.beginPacket(IP, Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
    delay(2000);
    message();
  }

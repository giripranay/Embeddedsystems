#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define IO_USERNAME  "giripranay"
#define IO_KEY       "a68f2ef379d4470780176f536af0f462"

#define WLAN_SSID       "vijaykumar"             // Your SSID
#define WLAN_PASS       "12345678"        // Your password


#define AIO_SERVER      "io.adafruit.com" //Adafruit Cloud
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "giripranay"            // Username
#define AIO_KEY         "a68f2ef379d4470780176f536af0f462"   // Auth Key


WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe photocell = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/bin3");


void MQTT_connect();

void setup() {
  Serial.begin(115200);

  
 Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 }

 uint32_t x=0;




 
 

void loop() {
 
  MQTT_connect();
  
 /* int n = random(101);
 Serial.print(F("\nSending val "));
  Serial.print(n);
  Serial.print("...");
  if (! photocell.publish(n)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }*/

  Serial.println(photocell.subscribe());

delay(10000);
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

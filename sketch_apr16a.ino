#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
 
const char *ssid =  "HVN";  
const char *pass =  "hvn12345";
 
DHT dht(D3, DHT11);
 
WiFiClient client;
 
long myChannelNumber = 1705323;
const char myWriteAPIKey[] = "X3OG9MOVY6BDBAWR";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WIFI is connected !");
  
  dht.begin();
  ThingSpeak.begin(client);
}
 
void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(2000);
}

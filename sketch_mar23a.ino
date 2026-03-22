#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include <DHT.h>

// WIFI access to connect
const char* ssid = "Starlink";
const char* password = "s#34olms!3Aw#Pmsnw";

// ThingSpeak ID AND API KEY
unsigned long channelID = 3307862;
const char* writeAPIKey = "CYLJR9O8VJJHM9EY";


#define DHTPIN 2
#define DHTTYPE DHT22

const int lightPin = A0;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;


void setup() {
  Serial.begin(9600);
  dht.begin();

  connectWiFi();
  ThingSpeak.begin(client);
}


void loop() {
  float temperature = dht.readTemperature();
  int lightLevel = analogRead(lightPin);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" | Light: ");
  Serial.println(lightLevel);

 
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, lightLevel);

  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("Data sent to ThingSpeak ✅");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(response);
  }

  delay(30000);
}


void connectWiFi() {
  Serial.print("Connecting to WiFi...");

  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected!");
}
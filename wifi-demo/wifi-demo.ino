#include <WiFiNINA.h>
#include <SPI.h>
#include "secrets.h"
#include <ArduinoHttpClient.h>

char ssid[] = SECRET_SSID;                // your network SSID (name)
char pass[] = SECRET_PASS;                // your network password
int status = WL_IDLE_STATUS;

WiFiClient wifiClient;
HttpClient client = HttpClient(wifiClient, "192.168.168.222", 8080);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  
  Serial.println("You're connected to the network");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  Serial.print("MAC Address: ");
  Serial.println(getMacAddress());

  client.beginRequest();
  client.get("/api/Rooms");
  client.endRequest();
  
  // Read the status code and body of the response
  int getStatusCode = client.responseStatusCode();
  String getResponse = client.responseBody();
  
  Serial.print("Status code for GET request: ");
  Serial.println(getStatusCode);
  Serial.print("Response for GET request: ");
  Serial.println(getResponse);
  
  client.beginRequest();
  client.post("/api/Rooms", "application/json", "{\"id\": 0, \"name\": \"string\", \"humidity\": 0, \"client\": {\"id\": 0, \"name\": \"string\"}, \"clientId\": 0}");
  int postStatusCode = client.responseStatusCode();
  String postResponse = client.responseBody();
  client.endRequest();

  Serial.print("Status code for POST request: ");
  Serial.println(postStatusCode);
  Serial.print("Response for POST request: ");
  Serial.println(postResponse);
}

void loop() {
  // nichts zu tun hier
}

String getMacAddress() {
  byte mac[6];
  WiFi.macAddress(mac);
  String macStr = "";

  for (int i = 0; i < 6; i++) {
    if (mac[i] < 16) {
      macStr += "0";
    }
    macStr += String(mac[i], HEX);
    if (i < 5) macStr += ":";
  }

  macStr.toUpperCase();
  return macStr;
}

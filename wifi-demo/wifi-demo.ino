#include <WiFiNINA.h>
#include <SPI.h>
#include "secrets.h"
#include <ArduinoHttpClient.h>

char ssid[] = SECRET_SSID;                // your network SSID (name)
char pass[] = SECRET_PASS;                // your network password
int status = WL_IDLE_STATUS;

WiFiSSLClient sslClient; // Create a WiFiSSLClient object for secure connections
HttpClient client = HttpClient(sslClient, "m241.jzel.ch", 443); // HTTPS port is 443

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

  client.beginRequest();
  client.get("/WeatherForecast"); // Path to resource
  client.endRequest();
  
  // Read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}

void loop() {
  // nichts zu tun hier
}

#include <ESP8266WiFi.h>
 
const char* ssid = "OHMAMP";
const char* password = "a029453745";
 
const char* host = "www.google.co.th";
 
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Wait until we're connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  // Report success
  Serial.println("");
  Serial.print("Connected to wifi with IP ");  
  Serial.println(WiFi.localIP());
  
  // Connect to the site defined in "host" on port 80
  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("Connection failed :-(");
  }

  Serial.println("Connected to host - sending request...");
  
  client.print(String("GET HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  Serial.println("Request sent - waiting for reply...");

  delay(10);
  
  // Read the entire response and flush it to Serial output
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("Connection closed.");
}
 
void loop() {
}

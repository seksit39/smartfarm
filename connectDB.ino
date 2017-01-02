#include <ESP8266WiFi.h>
const char* ssid = "OHMAMP";
const char* password = "a029453745";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED){  
            delay(250);
            Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");         
    Serial.println(WiFi.localIP());  
}

void loop() {
  String data = "airHumi=6&airTemp=5&groundHumi=4&groundTemp=3&light=2&rain=1";
  if (client.connect("192.168.1.41",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /add.php HTTP/1.1"); 
    client.println("Host: 192.168.1.41"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.println("OK");
  } 

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  //delay(10000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}

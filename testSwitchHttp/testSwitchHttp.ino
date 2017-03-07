
#include <ESP8266WiFi.h>
const char*     ssid          = "seksu";
const char*     password      = "12345678";
const char*     serverAddress = "54.169.141.31";
const uint16_t  serverPort    = 80;
const uint16_t  id1           = 1;
const uint16_t  id2           = 2;
const uint16_t  id3           = 3;

WiFiServer server(serverPort);
WiFiClient client;

void test1(){
  float humidity    = 20;
  float temperature = 25;
  int   sensor0     = 30;
  float groundtemp  = 51;
  int   sensor1     = 22;
  int   sensor2     = 51;
  
  String out = "airHumi=";
  out += humidity;
  out += "&airTemp=";
  out += temperature;
  out += "&groundHumi=";
  out += sensor0;
  out += "&groundTemp=";
  out += groundtemp;
  out += "&light=";
  out += sensor1;
  out += "&rain=";
  out += sensor2;
  out += "&userId=";
  out += "023";

  sendToServer(out);
}
void test2(){
  float humidity    = random(100);
  float temperature = random(100);
  int   sensor0     = 40;
  float groundtemp  = 50;
  int   sensor1     = 60;
  int   sensor2     = 40;
  
  String out = "airHumi=";
  out += humidity;
  out += "&airTemp=";
  out += temperature;
  out += "&groundHumi=";
  out += sensor0;
  out += "&groundTemp=";
  out += groundtemp;
  out += "&light=";
  out += sensor1;
  out += "&rain=";
  out += sensor2;
  out += "&userId=";
  out += "030";
  
  sendToServer(out);
}
void test3(){
  float humidity    = 1;
  float temperature = 2;
  int   sensor0     = 3;
  float groundtemp  = 4;
  int   sensor1     = 5;
  int   sensor2     = 6;
  
  String out = "airHumi=";
  out += humidity;
  out += "&airTemp=";
  out += temperature;
  out += "&groundHumi=";
  out += sensor0;
  out += "&groundTemp=";
  out += groundtemp;
  out += "&light=";
  out += sensor1;
  out += "&rain=";
  out += sensor2;
  out += "&userId=";
  out += "025";

  sendToServer(out);
}
void sendToServer(String data){ 
  while (!client.connect(serverAddress, serverPort));

  client.println("POST /add.php HTTP/1.1");
  client.print("Host: ");
  client.println(serverAddress);
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println();
  client.print(data);
  client.println();
  client.println();
 
  if (client.connected()) {
    client.stop();  // DISCONNECT FROM THE SERVER
  } 
}

void setup() {
  Serial.begin(115200);
  pinMode(D0,INPUT);
  pinMode(D1,INPUT);
  pinMode(D2,INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(digitalRead(D0)==HIGH){
    test1();
    Serial.println("Press D0");
    delay(500);
  }
  else if(digitalRead(D1)==HIGH){
    test2();
    Serial.println("Press D1");
    delay(500);
  }
  else if(digitalRead(D2)==HIGH){
    test3();
    Serial.println("Press D2");
    delay(500);
  }
    
}

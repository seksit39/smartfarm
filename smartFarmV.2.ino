/*
  SD Card Module  -> D5,D6,D7,D8
  DHT Sensor      -> D1
  Dallas  Sensor  -> D2
  Analog Sensor0  -> D0 (digital selection) (Ground Humidity)
  Analog Sensor1  -> D3 (digital selection) (Light Sensor)
  Analog Sensor2  -> D4 (digital selection) (Rain Sensor)
*/

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

const char*     ssid          = "OHMAMP";
const char*     password      = "a029453745";
const char*     serverAddress = "52.74.27.220";
const uint16_t  serverPort    = 80;

#define DHTTYPE DHT21

const int chipSelect = D8;

DHT dht(D1, DHTTYPE);

OneWire oneWire(D2);
DallasTemperature dallas(&oneWire);

WiFiServer server(serverPort);
WiFiClient client;



int readAnalog0() {
  digitalWrite(D0, HIGH);
  delay(100);
  int tmp = 100 - map(analogRead(A0), 0, 900, 0, 100);
  digitalWrite(D0, LOW);
  return tmp > 0 ? tmp : 0;
}

int readAnalog1() {
  digitalWrite(D3, HIGH);
  delay(100);
  int tmp = 100 - map(analogRead(A0), 0, 900, 0, 100);
  digitalWrite(D3, LOW);
  return tmp > 0 ? tmp : 0;
}

int readAnalog2() {
  digitalWrite(D4, HIGH);
  delay(100);
  int tmp = 100 - map(analogRead(A0), 0, 900, 0, 100);
  digitalWrite(D4, LOW);
  return tmp > 0 ? tmp : 0;
}
String readSensorHttp() {
  dallas.requestTemperatures();
  int sensor0 = readAnalog0();
  int sensor1 = readAnalog1();
  int sensor2 = readAnalog2();
  float humidity = dhthumi();
  float temperature = dhttemp();
  float groundtemp = dallas.getTempCByIndex(0);

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

  return out;
}
String readSensorHttp(int x) {
  dallas.requestTemperatures();
  
  float humidity    = 1;
  float temperature = 2;
  int sensor0       = 3;
  float groundtemp  = 4;
  int sensor1       = 5;
  int sensor2       = 6;
  
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

  return out;
}
String readSensor() {
  dallas.requestTemperatures();
  int sensor0 = readAnalog0();
  int sensor1 = readAnalog1();
  int sensor2 = readAnalog2();
  float humidity = dhthumi();
  float temperature = dhttemp();
  float groundtemp = dallas.getTempCByIndex(0);

  String out = getTime();
  out += ",";
  out += sensor0;
  out += ",";
  out += sensor1;
  out += ",";
  out += sensor2;
  out += ",";
  out += temperature;
  out += ",";
  out += humidity;
  out += ",";
  out += groundtemp;

  return out;
}

void writeFile(String data) {
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  }
}

void sendToServer(String data) {
  while (!client.connect(serverAddress, serverPort));

  client.println("POST /add.php HTTP/1.1");
  client.print("Host: "); // SERVER ADDRESS HERE TOO
  client.println(serverAddress);
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println();
  client.print(data);
  Serial.println("OK");

  if (client.connected()) {
    client.stop();  // DISCONNECT FROM THE SERVER
  }
}

float dhttemp() {
  float temp = 0.0;
  for (int i = 0 ; i < 30 ; i++) {
    temp += dht.readTemperature();
    temp /= 2;
    //delay(100);
  }
  return temp;
}

float dhthumi() {
  float humi = 0.0;
  for (int i = 0 ; i < 30 ; i++) {
    humi += dht.readHumidity();
    humi /= 2;
    //delay(100);
  }
  return humi;
}

String GMT(String input) {
  String output = input;
  String stringtemp = input.substring(12, 14);
  int hour = stringtemp.toInt() + 7;
  Serial.println(hour);
  String temptime = input.substring(12);
  output.remove(12);
  temptime.replace(stringtemp, (String)hour);
  output += temptime;
  return output;
}

String getTime() {

  while (!client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");

  while (!!!client.available()) {
    yield();
  }

  while (client.available()) {
    if (client.read() == '\n') {
      if (client.read() == 'D') {
        if (client.read() == 'a') {
          if (client.read() == 't') {
            if (client.read() == 'e') {
              if (client.read() == ':') {
                client.read();
                String theDate = client.readStringUntil('\r');
                client.stop();
                theDate = theDate.substring(5, 25);
                return GMT(theDate);
              }
            }
          }
        }
      }
    }
  }
}
void setup ()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  dht.begin();
  dallas.begin();
  pinMode(D0, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D0, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (SD.begin(chipSelect))
    Serial.println("SD OK");

  //client.connect(server_ip, SERVER_PORT);

  ESP.wdtDisable();
}

void loop ()
{
  String temp = readSensorHttp(1);
  sendToServer(temp);
  writeFile(temp);
  for (int i = 0 ; i < 10 ; i++) {
    delay(1000);
    ESP.wdtDisable();
  }
}

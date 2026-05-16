#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

const char* servername = "http://ip/kelcy/insert.php";
const char* ssid = "Kelcy";             
const char* pass = "12345678";

#define DHTPIN 17
#define DHTTYPE DHT11

#define Greenpin 22
#define Redpin 21
#define Bluepin 23

DHT dht(DHTPIN, DHTTYPE);

float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(Greenpin, OUTPUT);
  pinMode(Redpin, OUTPUT);
  pinMode(Bluepin, OUTPUT);
  digitalWrite(Greenpin, LOW);
  digitalWrite(Redpin, LOW);
  digitalWrite(Bluepin, LOW);
  WiFi.begin(ssid, pass);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    
    digitalWrite(Redpin, HIGH);
    delay(500);
    digitalWrite(Redpin, LOW);
    delay(500);
    
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(servername);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    doc["device_name"] = "ESP32_01";
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;

    String jsondoc;
    serializeJson(doc, jsondoc);

    int responsecode = http.POST(jsondoc);

    Serial.print("Response Code: ");
    Serial.println(responsecode);

    if (responsecode > 0) {
      Serial.println("Data inserted successfully");
    } else {
      Serial.println("Server failed");
    }

    http.end();
  } else {
    Serial.println("Failed to connect to WiFi");
  }

  digitalWrite(Greenpin, LOW);
  digitalWrite(Bluepin, LOW);
  digitalWrite(Redpin, LOW);

  if (temperature <= 20) {
    digitalWrite(Bluepin, HIGH);
    Serial.println("BLUE LED ON - Cold temperature");
  } 
  else if (temperature <= 30) {
    digitalWrite(Greenpin, HIGH);
    Serial.println("GREEN LED ON - Normal temperature");
  } 
  else if (temperature <= 40) {
    digitalWrite(Redpin, HIGH);
    Serial.println("RED LED ON - Hot temperature");
  } 
  else {
    digitalWrite(Redpin, HIGH);
    digitalWrite(Bluepin, HIGH);
    delay(100);
    digitalWrite(Redpin, LOW);
    digitalWrite(Bluepin, LOW);
    Serial.println("EXTREME TEMPERATURE!");
  }

  delay(5000);
}

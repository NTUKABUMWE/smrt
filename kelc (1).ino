#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* servername = "http://YOUR_IP/kelcy/insert.php";
const char* ssid = "IAP4";
const char* pass = "123@Muhura";

// Ultrasonic Sensor Pins
#define trigpin 5
#define echopin 4

// LED Pins
#define Greenpin 6
#define Redpin 7
#define Bluepin 14

void setup() {

  Serial.begin(115200);

  // Pin Modes
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(Greenpin, OUTPUT);
  pinMode(Redpin, OUTPUT);
  pinMode(Bluepin, OUTPUT);

  // Turn OFF LEDs initially
  digitalWrite(Greenpin, LOW);
  digitalWrite(Redpin, LOW);
  digitalWrite(Bluepin, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, pass);

  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Trigger Ultrasonic Sensor
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigpin, LOW);

  // Read Echo Time
  long duration = pulseIn(echopin, HIGH);

  // Calculate Distance
  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send Data to Server
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(servername);

    http.addHeader("Content-Type", "application/json");

    // Create JSON
    StaticJsonDocument<200> doc;

    doc["device_name"] = "ESP32_01";
    doc["distance"] = distance;

    String jsondoc;

    serializeJson(doc, jsondoc);

    // POST Request
    int responsecode = http.POST(jsondoc);

    Serial.print("Response Code: ");
    Serial.println(responsecode);

    if (responsecode > 0) {
      Serial.println("Data inserted successfully");
    }
    else {
      Serial.println("Server failed");
    }

    http.end();
  }
  else {
    Serial.println("Failed to connect to WiFi");
  }

  // LED Conditions
  digitalWrite(Greenpin, LOW);
  digitalWrite(Bluepin, LOW);
  digitalWrite(Redpin, LOW);

  if (distance <= 20) {

    digitalWrite(Greenpin, HIGH);
    Serial.println("GREEN LED ON");

  }
  else if (distance <= 40) {

    digitalWrite(Bluepin, HIGH);
    Serial.println("BLUE LED ON");

  }
  else if (distance <= 60) {

    digitalWrite(Redpin, HIGH);
    Serial.println("RED LED ON");

  }
  else {

    Serial.println("Safe on the gate");

  }

  delay(500);
}

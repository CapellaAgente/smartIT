#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* wifi_name = "Capella";
const char* password = "capella24";
const char* mqtt_server = "10.155.27.205";


#define DHTTYPE DHT11
const int DHT_PIN = 33;
DHT dht(DHT_PIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(wifi_name, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
}

void mqtt_conect() {
  while (!client.connected()) {
    Serial.println("Tentando conexão MQTT...");
    if (client.connect("ESP32_Capella")) {
      Serial.println("Conectado!");
    } else {
      delay(5000);
    }
  }
  
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    mqtt_conect();
  }
  client.loop();

  static unsigned long lastMessage = 0;
  unsigned long now = millis();
  if (now - lastMessage > 5000) {
    lastMessage = now;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (!isnan(temperature) && !isnan(humidity)) {
      String jsonData = "{\"temp\":" + String(temperature) +  ", \"humi\":" +  String(humidity) + "}";
      client.publish("projeto/smart_it/data", jsonData.c_str());
      Serial.println("Dados enviados para o broker!");
    }
  }
}
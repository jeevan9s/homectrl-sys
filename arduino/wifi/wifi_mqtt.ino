// WiFi + MQTT module 
// wifi, mqtt, sinric init and control
#include "wifi/wifi_mqtt.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);
bool mqttConnected = false;

std::map<String, std::function<void(String)>> topicCallbacks;


// --- WIFI ---
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: connecting");

  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)
    WiFi.setSleep(false); 
    WiFi.setAutoReconnect(true);
  #endif

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void wifiLoop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi]: Reconnecting...");
    setupWiFi(); 
  }
}

// --- MQTT ---
void setupMQTT() {
  mqttClient.setServer("broker.hivemq.com", 1883);

  
  mqttClient.setCallback([](char* topic, byte* payload, unsigned int length){
    String msg = "";
    for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
    String t = String(topic);
    if (topicCallbacks.count(t)) topicCallbacks[t](msg);
  });
}

void mqttLoop() {
  if (!mqttClient.connected()) {
    mqttConnected = false;
    Serial.println("[MQTT]: Reconnecting...");
    while (!mqttClient.connected()) {
      String clientId = "ESP32-" + String(random(0xffff), HEX);
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("[MQTT]: Connected!");
        mqttConnected = true;

        
        for (auto &pair : topicCallbacks) {
          mqttClient.subscribe(pair.first.c_str());
        }
      } else {
        Serial.print("[MQTT]: Failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" retrying in 2s");
        delay(2000);
      }
    }
  }
  mqttClient.loop();
}
 // interaction
 void mqttPublish(const char* topic, const char* payload) {
  if (mqttClient.connected()) mqttClient.publish(topic, payload);
}

void mqttSubscribe(const char* topic, std::function<void(String)> callback) {
  topicCallbacks[String(topic)] = callback;
  if (mqttClient.connected()) mqttClient.subscribe(topic);
}

// --- SINRIC PRO ---
void setupSinric() {
  SinricPro.onConnected([]() { Serial.println("[SinricPro]: Connected!"); });
  SinricPro.onDisconnected([]() { Serial.println("[SinricPro]: Disconnected"); });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void sinricLoop() {
  SinricPro.handle();
}

void sinricAddSwitch(const char* deviceId, std::function<bool(const String&, bool&)> callback) {
  SinricProSwitch &sw = SinricPro[deviceId];
  sw.onPowerState(callback);  
}


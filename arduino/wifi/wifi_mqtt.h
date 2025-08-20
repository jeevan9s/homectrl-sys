// WiFi + MQTT header file

#ifndef WIFI_MQTT_H
#define WIFI_MQTT_H

#define BAUD_RATE 115200    

// WIFI CREDENTIALS
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

// SINRICPRO CREDENTIALS
#define APP_KEY  ""
#define APP_SECRET ""
#define SWITCH_ID_1  "" // RELAY
#define SWITCH_ID_2 "" // SENSOR
#define SWITCH_ID_3  "" // MOTOR

// INCLUDES & FUNCTIN DEFINITIONS
#include <WiFi.h>
#include <PubSubClient.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <functional>
#include <map>

extern WiFiClient espClient;
extern PubSubClient mqttClient;

void setupWiFi();
void wifiLoop(); 
void setupMQTT();
void setupSinric();
void mqttLoop();
void sinricLoop();


void mqttPublish(const char* topic, const char* payload);
void mqttSubscribe(const char* topic, std::function<void(String)> callback);
void sinricAddSwitch(const char* deviceId, std::function<bool(const String&, bool&)> callback);

#endif


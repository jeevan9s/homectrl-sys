// irrigation module 
// moisture sensor, pump control

#include "irrigation.h"
#include "wifi/wifi_mqtt.ino"
#include "wifi/wifi_mqtt.h"

// timing vars 
unsigned long lastPublishMs = 0;
unsigned long lastWaterStartMs = 0;
unsigned long lastWaterDurationMs = 0;
static unsigned long lastAutoWaterMs = 0;

// states n actions
bool pumpOn = false;
bool autoMode = true;
uint8_t autoThreshold = IRRIG_AUTO_THRESHOLD_PCT;
uint16_t soilRaw = 0;

uint16_t moistureWindow[IRRIG_MOVAG_WINDOW];
uint8_t movAgIndex = 0;
uint32_t moistureSum = 0;  

unsigned long irrigationGetLastWaterStartMs() { return lastWaterStartMs; }
unsigned long irrigationGetLastDurationMs() { return lastWaterDurationMs; }
bool irrigationPumpIsOn() { return pumpOn; }
bool irrigationModeIsAuto() { return autoMode; }

void publishStatus(const char* status) {
    mqttPublish(IRRIG_TOPIC_STATUS, status);
    Serial.println(status);
}

void setupIrrigation() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  digitalWrite(PUMP_RELAY_PIN, LOW);

  moistureSum = 0;
  for (uint8_t i = 0; i < IRRIG_MOVAG_WINDOW; i++) {
    moistureWindow[i] = analogRead(SENSOR_PIN);
    moistureSum += moistureWindow[i];
  }

  setupWiFi();
  setupMQTT();

  mqttSubscribe(IRRIG_TOPIC_PUMP_CMD, [](String msg){
      if (msg == "trigger") pumpOnHandler();
      if (msg == "off") pumpOffHandler(); 
  });

  mqttSubscribe(IRRIG_TOPIC_TELEM_REQ, [](String msg){
      if (msg == "moisture") mqttPublish(IRRIG_TOPIC_MOISTURE, String(irrigationGetMoisturePct()).c_str());
      if (msg == "last") mqttPublish(IRRIG_TOPIC_LAST_WATERING, String(irrigationGetLastWaterStartMs()).c_str());
  });

  addAlexaSoilMoisture();
  addAlexaLastWatered();

}


// mode switching
void pumpOnHandler(bool isManual = true) {
    if(isManual) autoMode = false;
    digitalWrite(PUMP_RELAY_PIN, HIGH);
    pumpOn = true;
    lastWaterStartMs = millis();
    publishStatus("pump on");
}

void pumpOffHandler() {
    digitalWrite(PUMP_RELAY_PIN, LOW);
    pumpOn = false;
    lastWaterDurationMs = millis() - lastWaterStartMs;
    publishStatus("pump off");
}

// sensor reading filtering
uint16_t updateMovingAverage(uint16_t newReading) {
  moistureSum -= moistureWindow[movAgIndex];
  moistureWindow[movAgIndex] = newReading;
  moistureSum += newReading;

  movAgIndex = (movAgIndex + 1) % IRRIG_MOVAG_WINDOW;

  return moistureSum / IRRIG_MOVAG_WINDOW;
}

uint8_t irrigationGetMoisturePct() {
  int pct = map(soilRaw, SOIL_RAW_DRY, SOIL_RAW_WET, 0, 100);
  return constrain(pct, 0, 100);
}

void readSoilSensor() {
  uint16_t raw = analogRead(SENSOR_PIN);
  if(raw < SOIL_RAW_DRY) raw = SOIL_RAW_DRY;
  if(raw > SOIL_RAW_WET) raw = SOIL_RAW_WET;
  soilRaw = updateMovingAverage(raw);
}

void publishMoisture() {
  unsigned long now = millis();
  if (now - lastPublishMs >= IRRIG_PUBLISH_MS) {
    lastPublishMs = now;

    uint8_t soilPct = irrigationGetMoisturePct();

    char buf[32];
    snprintf(buf, sizeof(buf), "%d", soilPct);
    mqttPublish(IRRIG_TOPIC_MOISTURE, buf);

    Serial.print("moisture: ");
    Serial.println(soilPct);
  }
}

// automated irrigation
void checkAutoWatering() {
    if (!autoMode) return; 

    uint8_t soilPct = irrigationGetMoisturePct();
    Serial.print("auto watering? "); Serial.println(autoMode);
    Serial.print("soil %: "); Serial.println(soilPct);

    if (!pumpOn && soilPct < autoThreshold && millis() - lastAutoWaterMs > IRRIG_COOLDOWN_MS) {
        pumpOnHandler(false);
        lastAutoWaterMs = millis();
    }

    if (pumpOn && millis() - lastWaterStartMs > IRRIG_MIN_ON_MS && autoMode) {
        pumpOffHandler();
    }
}

// --- SINRIC PRO ---
void addAlexaSoilMoisture() {
    sinricAddCustomDevice(SWITCH_ID_SENSOR
        [](const String& deviceId, const String& action, const String& value, String& response) -> bool {
            if (action == "getSoilMoisture") {
                uint8_t pct = irrigationGetMoisturePct();
                response = String(pct) + " percent";
                Serial.print("SINRIC soil moisture: ");
                Serial.println(response);
                return true;
            }
            return false;
        }
    );
}

void addAlexaLastWatered() {
    sinricAddCustomDevice(SWITCH_ID_PUMP,
        [](const String& deviceId, const String& action, const String& value, String& response) -> bool {
            if (action == "getLastWatered") {
                unsigned long elapsedMs = millis() - irrigationGetLastWaterStartMs();
                if (elapsedMs < 60000)
                    response = String(elapsedMs / 1000) + " seconds ago";
                else if (elapsedMs < 3600000)
                    response = String(elapsedMs / 60000) + " minutes ago";
                else
                    response = String(elapsedMs / 3600000) + " hours ago";

                Serial.print("SINRIC last watering: ");
                Serial.println(response);
                return true;
            }
            return false;
        }
    );
}

void irrigationLoop() {
  readSoilSensor();      
  publishMoisture();      
  checkAutoWatering();    
}

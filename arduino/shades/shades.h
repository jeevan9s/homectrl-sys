// shades header file 
#ifndef IRRIGATION_H
#define IRRIGATION_H

#include <Arduino.h>

#define BAUD_RATE 115200  

// --- HARDWARE ---
#define SENSOR_PIN 
#define PUMP_RELAY_PIN

// --- CALIBRATION ---
// to be tuned 
#define SOIL_RAW_DRY 10
#define SOIL_RAW_WET 1000

// --- TIMING ---
#define IRRIG_POLL_MS 1000 
#define IRRIG_PUBLISXH_MS 5000
#define IRRIG_MIN_ON_MS 10000
#define IRRIG_COOLDOWN_MS 60000

#define IRRIG_MOVAG_WINDOW 10 
#define IRRIG_AUTO_THRESHOLD_PCT 35 // default threshold 

// --- MQTT TOPICS --- 
#define IRRIG_MQTT_BASE              "homeauto/irrigation"
#define IRRIG_TOPIC_MOISTURE         IRRIG_MQTT_BASE "/moisture"          
#define IRRIG_TOPIC_PUMP_CMD         IRRIG_MQTT_BASE "/pump/cmd"          
#define IRRIG_TOPIC_PUMP_STATE       IRRIG_MQTT_BASE "/pump/state"        
#define IRRIG_TOPIC_LAST_WATERING    IRRIG_MQTT_BASE "/watering/last"     
#define IRRIG_TOPIC_SETTINGS         IRRIG_MQTT_BASE "/settings"          
#define IRRIG_TOPIC_TELEM_REQ        IRRIG_MQTT_BASE "/telemetry/request" 
#define IRRIG_TOPIC_TELEM_RESP       IRRIG_MQTT_BASE "/telemetry"         

// --- CONTROLS ---
void setupIrrigation();
void irrigationLoop();

void irrigationSetAuto();
void irrigationSetManual();
void irrigationSetManualOff();

void irrigationSetAutoThresholdPct(uint8_t pct);
void irrigationSetCalibration(int rawWet, int rawDry);

uint8_t irrigationGetMoisturePct();
bool    irrigationPumpIsOn();
bool    irrigationModeIsAuto();
unsigned long irrigationGetLastWaterStartMs();   
unsigned long irrigationGetLastWaterDurationMs();



#endif
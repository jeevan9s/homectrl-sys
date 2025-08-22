// shades header file 
#ifndef SHADES_H
#define SHADES_H

#include <Arduino.h>

#define BAUD_RATE 115200  

// --- HARDWARE ---
#define STEP_PIN 
#define DIR_PIN

// --- MOTOR CONFIG ---
#define STEPS_PER_REV 200
#define MICROSTEPS 16
#define TOTAL_STEPS_PER_REV 3200 // steps_per_rev * microsteps 
#define MAX_POSITION_STEPS 6400 // two full "cycles" (open/close)
#define POS_TOLERANCE 5
#define STEP_SPEED_DELAY 500 // fine tunin

// --- TIMING ---
#define SHADE_PUBLISH_MS 3000
#define SHADE_TIMEOUT_MS 10000

// --- MQTT TOPICS --- 
#define SHADE_MQTT_BASE              "home/shade"
#define SHADE_TOPIC_CMD              SHADE_MQTT_BASE "/cmd"              
#define SHADE_TOPIC_POSITION         SHADE_MQTT_BASE "/position"         
#define SHADE_TOPIC_STATE            SHADE_MQTT_BASE "/state"            
#define SHADE_TOPIC_TELEM_REQ        SHADE_MQTT_BASE "/telemetry/request" 
#define SHADE_TOPIC_STATUS           SHADE_MQTT_BASE "/status"           
#define SHADE_TOPIC_CALIBRATE        SHADE_MQTT_BASE "/calibrate"       

// --- CONTROL ---

void setupShading();
void shadingLoop();

void moveToPositionPct(uint8_t targetPct);
void openBlinds();
void closeBlinds();
void stopMotorHandler();
void calibrateHandler();

uint8_t shadingGetPositionPct();
bool shadingMotorIsRunning();
unsigned long shadingGetLastMoveMs();

#endif


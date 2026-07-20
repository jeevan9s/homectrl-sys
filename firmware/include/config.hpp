/**
 * @file        config.hpp
 * @brief       Header for general system configuration
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#pragma once

#include "pinouts.hpp"
#include "Controller.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

// WiFi-creds
extern const char* ssid;
extern const char* pswd;

extern int blinksRemaining;
extern unsigned long lastBlink;
extern uint8_t activeBlinkPin;
extern int blinkCount;

struct Scheduler {
    void update(const Controller &state) {}
};

extern Scheduler scheduler;

void led_startup(void);
void blinkLED(uint8_t ledPin, int count, int delayMs = 200);
void scanI2C();
void blinkP(uint8_t pin, int count);

// buzzer
const int PWM_FREQ = 4000;   // (4kHz resonant frequency)
const int PWM_RES = 8;  

// tmc 
#define R_SENSE          0.11f 
#define DRIVER_ADDRESS   0b00   
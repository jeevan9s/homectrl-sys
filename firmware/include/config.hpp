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
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

// WiFi-creds
const char* ssid = "abc"; 
const char* pswd = "def";

void led_startup(void);
void blinkLED(uint8_t ledPin, int count, int delayMs=200);
void scanI2C();
void blinkP(uint8_t pin, int count);

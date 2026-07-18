/**
 * @file        config.cpp
 * @brief       General system configuration
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "config.hpp"

int blinksRemaining = 0;
unsigned long lastBlink = 0;
uint8_t activeBlinkPin = 0;
int blinkCount = 0;

void led_startup(void) {
    mcp.digitalWrite(Pins::Indicators::WIFI, HIGH);
    delay(400);
    mcp.digitalWrite(Pins::iNDICA::CAM_LED, LOW);
    delay(400); 

    Indicators.digitalWrite(Pins::Indicators::DBG_LED, HIGH);
    delay(300);
    Indicators.digitalWrite(Pins::Indicators::DBG_LED, LOW);
    delay(300); 

    Indicators.digitalWrite(Pins::Indicators::CAM_LED, HIGH);
    delay(200);
    Indicators.digitalWrite(Pins::Indicators::CAM_LED, LOW);
    delay(200);
    Indicators.digitalWrite(Pins::Indicators::DBG_LED, HIGH);
    delay(200); 

    Indicators.digitalWrite(Pins::Indicators::DBG_LED, LOW);
    Indicators.digitalWrite(Pins::Indicators::CAM_LED, HIGH);
    delay(200);
    Indicators.digitalWrite(Pins::MCP::CAM_LED, LOW);
    delay(200); 
}

void blinkLED(uint8_t ledPin, int count, int delayMs) {
    for(int i = 0; i < count; i++) {
        mcp.digitalWrite(ledPin, HIGH);
        delay(delayMs);
        mcp.digitalWrite(ledPin, LOW);
        delay(delayMs);
    }
}

void scanI2C() {
    Serial.println("scanning I2C bus...");
    for(byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.printf("Found device at 0x%02X\n", address);
        }
    }
}

// non-blocking led stuff
void blinkP(uint8_t pin, int count) {
    if (blinksRemaining == 0) blinksRemaining = count * 2;

    if (millis() - lastBlink > 200) {
        lastBlink = millis();
        bool current = digitalRead(pin);
        digitalWrite(pin, !current);
        blinksRemaining--;

        if (blinksRemaining == 0) digitalWrite(pin, LOW);
    }
}
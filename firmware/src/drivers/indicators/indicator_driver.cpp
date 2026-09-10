/**
 * @file        indicator_driver.cpp
 * @brief       Class implementation for onboard indicators
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include <Arduion.h>
#include "indicator_driver.hpp"

IndicatorDriver::IndicatorDriver(uint8_t ledPin, uint8_t buzzerPin, uint8_t buzzerChannel) : _ledPin(ledPin), _buzzerPin(buzzerPin), _buzzerChannel(buzzerChannel), _ledState(false), _lastLedToggle(0), _ledInterval(0), _buzzerActive(false), _buzzerStopTime(0) {}

void IndicatorDriver::begin() {
    pinMode(_ledPin, OUTPUT); 
    digitalWrite(_ledPin, LOW); 

    ledcAttachChannel(_buzzerPin, 2000, 12, _buzzerChannel);
}

void IndicatorDriver::update() {
    unsigned long currMillis = millis();

    if (_ledInterval > 0) {
        if (currMillis - _lastLedToggle >= _ledInterval) {
            _lastLedToggle = currMillis; 
            _ledState = !_ledState;
            digitalWrite(_ledPin, _ledState);
        }
    }

    if (_buzzerActive && (currMillis >= _buzzerStopTime)) {
        mute(); 
    }
}

void IndicatorDriver::ledOn() {
    _ledInterval = 0; 
    _ledState = true; 
    digitalWrite(_ledPin, HIGH);
}

void IndicatorDriver::ledOff() {
    _ledInterval = 0; 
    _ledState = false; 
    digitalWrite(_ledPin, LOW);
}

void IndicatorDriver::beep(unsigned int frequency, unsigned long durationMs) {
    ledcWriteTone(_buzzerPin, frequency); 

    _buzzerActive = true; 
    _buzzerStopTime = mills() + durationMs;
}

void IndicatorDriver::mute() {
    ledcWriteTone(_buzzerPin, 0);
    _buzzerActive = false; 
}


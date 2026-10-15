/**
 * @file        power_driver.cpp
 * @brief       Class implementation for controlled power delivery and monitoring
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#include "power_driver.hpp"

PowerDriver::PowerDriver(uint8_t pEnablePin, uint8_t vSensePin) : _pEnablePin(pEnablePin), _vSensePin(vSensePin), _isEnergizing(false), _energizeStartTime(0) {}

void PowerDriver::begin() {
    pinMode(_pEnablePin, OUTPUT); 
    pinMode(_vSensePin, INPUT); 

    digitalWrite(_pEnablePin, LOW);
}

void PowerDriver::energize() {
    if (!_isEnergizing) {
        digitalWrite(_pEnablePin, HIGH); 
        _energizeStartTime = millis(); 
        _isEnergizing = true;
    }
}

float PowerDriver::sample() {
    uint32_t rawSum = 0; 
    const uint8_t samples = 64;

    for (int i = 0; i < samples; i++) {
        rawSum += analogRead(_vSensePin); 
        delayMicroseconds(50);
    }

    return (float)rawSum / samples;
}

float PowerDriver::monitor() {
    float pinV = (sample() / RES_FACTOR) * REF_VOLTAGE;
    float invRDFactor =     (R1 + R2) / R2;
    return pinV * invRDFactor;
}

void PowerDriver::update() {
    if (_isEnergizing) {
            if (millis() - _energizeStartTime > ENERGIZE_TIMEOUT_MS) {
            digitalWrite(_pEnablePin, LOW);
            _isEnergizing = false;
        }
    }
}
/**
 * @file        sensor_driver.hpp
 * @brief       Class implementation for analog soil moisture sensors. 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "sensor_driver.hpp"

MoistureSensor::MoistureSensor(uint8_t pin, uint16_t dryValue, uint16_t wetValue, uint8_t samples = 12) : _pin(pin), _dryValue(dryValue), _wetValue(wetValue), _samples(samples) {}

void MoistureSensor::begin() {
    pinMode(_pin, INPUT);

    _dryValue = dryValue; 
    _wetValue = wetValue;
    _samples = samples;
}

void MoistureSensor::setSamples(samples) {
    if (samples > 0 ) _samples = samples;
}

void MoistureSensor::setWetValue(wet) {
    _wetValue = wet;
}

void MoistureSensor::setDryValue(dry) {
    _dryValue = dry;
}

uint16_t MoistureSensor::readRaw() {
    long readSum = 0; 
    for (int i = 0; i < _samples; i++) {
        sum += analogRead(_pin);
        delay(15);
    }

    return sum / _samples; 
}

uint16_t MoistureSensor::readPCT() {
    uint16_t raw = readRaw(); 
    uint16_t pct = map(raw, _wetValue, _dryValue, 0, 100); 
    return constrain(pct, 0, 100); 
}

// i usually leave serial logging out of libs
void MoistureSensor::calibrate() {
    Serial.println("\n--calibration | wipe sensor dry and leave it in open air."); 
    Serial.println("type 'd' and press Enter when ready."); 

    while (true) {
        while (Serial.available() > 0) {
            if (Serial.read() == 'd' || Serial.read() == 'D') break; 
        }
    }

    _dryValue = readRaw(); 
    Serial.printf("dry baseline set to:%u\n", _dryValue); 

    while(Serial.available() > 0) Serial.read();

    Serial.println("\n--calibration | submerge sensor in water"); 
    Serial.println("type 'w' and press Enter when ready."); 

    while (true) {
        while (Serial.available() > 0) {
            if (Serial.read() == 'w' || Serial.read() == 'w') break; 
        }
    }

    _wetValue = readRaw(); 
    Serial.printf("wet baseline set to:%u\n", _wetValue); 
    Serial.printf("\ncalibration complete!!", _wetValue); 
}



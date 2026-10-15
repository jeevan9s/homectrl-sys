/**
 * @file        sensor_driver.hpp
 * @brief       Class implementation for analog soil moisture sensors. 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include "sensor_driver.hpp"

MoistureSensor::MoistureSensor(uint8_t pin, uint16_t dryValue, uint16_t wetValue, uint8_t samples) : _pin(pin), _dryValue(dryValue), _wetValue(wetValue), _samples(samples) {}

void MoistureSensorDriver::begin() {
    pinMode(_pin, INPUT);
}

void MoistureSensor::setSamples(uint8_t samples) {
    if (samples > 0) _samples = samples;
}

void MoistureSensor::setWetValue(uint16_t wet) {
    _wetValue = wet;
}

void MoistureSensor::setDryValue(uint16_t dry) {
    _dryValue = dry;
}

uint16_t MoistureSensor::readRaw() {
    uint32_t sum = 0; 
    for (int i = 0; i < _samples; i++) {
        sum += analogRead(_pin);
        delay(15);
    }

    return sum / _samples; 
}

uint16_t MoistureSensor::readPCT() {
    uint16_t raw = readRaw(); 
    // dry reads high and wet reads low on capacitive sensors
    long pct = map(raw, _dryValue, _wetValue, 0, 100); 
    return constrain(pct, 0, 100); 
}

// blocks until the given key (case-insensitive) is received
void MoistureSensor::waitForKey(char key) {
    while (true) {
        while (Serial.available() > 0) {
            if (tolower(Serial.read()) == key) return; 
        }
        delay(10);
    }
}

// i usually leave serial logging out of libs
void MoistureSensor::calibrate() {
    Serial.println("\n--calibration | wipe sensor dry and leave it in open air."); 
    Serial.println("type 'd' and press Enter when ready."); 
    waitForKey('d');

    _dryValue = readRaw(); 
    Serial.printf("dry baseline set to:%u\n", _dryValue); 

    while (Serial.available() > 0) Serial.read();

    Serial.println("\n--calibration | submerge sensor in water"); 
    Serial.println("type 'w' and press Enter when ready."); 
    waitForKey('w');

    _wetValue = readRaw(); 
    Serial.printf("wet baseline set to:%u\n", _wetValue); 
    Serial.println("\ncalibration complete!!"); 
}



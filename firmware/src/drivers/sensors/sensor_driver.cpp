/**
 * @file        sensor_driver.cpp
 * @brief       Class implementation for analog soil moisture sensors. 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include "sensor_driver.hpp"

MoistureSensorDriver::MoistureSensorDriver(uint8_t pin, uint16_t dryValue, uint16_t wetValue, uint8_t samples)
    : _pin(pin), _dryValue(dryValue), _wetValue(wetValue), _samples(samples > 0 ? samples : 1) {}

void MoistureSensorDriver::begin() {
    pinMode(_pin, INPUT);
}

void MoistureSensorDriver::setSamples(uint8_t samples) {
    if (samples > 0) _samples = samples;
}

uint16_t MoistureSensorDriver::readRaw() {
    uint32_t sum = 0; 
    for (uint8_t i = 0; i < _samples; i++) {
        sum += analogRead(_pin);
        delay(15);
    }

    return sum / _samples; 
}

float MoistureSensorDriver::readPCT() {
    // dry reads high and wet reads low on capacitive sensors
    if (_dryValue == _wetValue) return 0.0f;

    float raw = readRaw(); 
    float pct = (static_cast<float>(_dryValue) - raw) * 100.0f / (static_cast<float>(_dryValue) - static_cast<float>(_wetValue)); 
    return constrain(pct, 0.0f, 100.0f); 
}


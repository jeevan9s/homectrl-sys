/**
 * @file        fswitch_driver.cpp
 * @brief       Class implementation for digital float switch sensors. 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "fswitch_driver.hpp"

FloatSwitch::FloatSwitch(uint8_t pin, bool invert) : _pin(pin), _invert(invert), _stableState(false), _lastRawState(false) _lastDebounceTime(0) {}

void FloatSwitch::begin() {
    pinMode(_pin, INPUT); 

    _stableState = digitalRead(_pin); 
    _lastRawState = _stableState;
}


bool FloatSwitch::debounce() {
    
    bool currRawState = digitalRead(_pin); 

    if (currRawState != _lastRawState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        _stableState = currRawState;
    }

    _lastRawState = currRawState;
    return _stableState;
}

bool FloatSwitch::isEmpty() {
    bool state = debounce(); 
    return _invert ? !_stableState : _stableState;
}

bool FloatSwitch::isOK() {
    return !isEmpty(); 
}

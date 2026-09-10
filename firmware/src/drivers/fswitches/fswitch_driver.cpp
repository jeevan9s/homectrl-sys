/**
 * @file        fswitch_driver.cpp
 * @brief       Class implementation for digital float switch sensors. 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include <Arduion.h>
#include "fswitch_driver.hpp"

FloatSwitch::FloatSwitch(uint8_t pin, bool invert) : _pin(pin), _invert(invert) {}

void FloatSwitch::begin() {
    pinMode(_pin, INPUT); 
}

bool FloatSwitch::debounce() {
    bool first = analogRead(_pin); 
    delay(50); 
    bool second = analogRead(_pin); 
    return (first == second) ? second : first;
}

bool FloatSwitch::isEmpty() {
    bool state = debounce(); 
    return _invert ? !state : state;
}

bool FloatSwitch::isOK() {
    return !isEmpty(); 
}

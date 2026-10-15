/**
 * @file        fswitch_driver.hpp
 * @brief       Class definition for digital float switch sensors.
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>

class FloatSwitchDriver
{
public:
    FloatSwitchDriver(uint8_t pin, bool invert = false);
    void begin();
    bool update();
    bool isEmpty();
    bool isOK();

private:
    uint8_t _pin;
    bool _invert;

    bool _stableState;
    bool _lastRawState;

    unsigned long _lastDebounceTime;
    const unsigned long _debounceDelay = 50;
};
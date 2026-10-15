/**
 * @file        fswitch_driver.cpp
 * @brief       Class implementation for digital float switch sensors.
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include "fswitch_driver.hpp"

FloatSwitchDriver::FloatSwitchDriver(uint8_t pin, bool invert) : _pin(pin), _invert(invert), _stableState(false), _lastRawState(false), _lastDebounceTime(0) {}

void FloatSwitchDriver::begin()
{
    pinMode(_pin, INPUT);

    _stableState = digitalRead(_pin);
    _lastRawState = _stableState;
}

bool FloatSwitchDriver::update()
{

    bool currRawState = digitalRead(_pin);

    if (currRawState != _lastRawState)
    {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay)
    {
        _stableState = currRawState;
    }

    _lastRawState = currRawState;
    return _stableState;
}

bool FloatSwitchDriver::isEmpty()
{
    update();
    return _invert ? !_stableState : _stableState;
}

bool FloatSwitchDriver::isOK()
{
    return !isEmpty();
}

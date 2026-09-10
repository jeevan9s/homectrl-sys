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
#include "cstdint.h"

class FloatSwitch {
    public:
        FloatSwitch(uint8_t pin, bool invert = false); 
        void begin(); 
        bool isEmpty(); 
        bool isOK();

    private:
        uint8_t _pin; 
        bool _invert; 

        void debounce(); // dummy debounce with two reads
}
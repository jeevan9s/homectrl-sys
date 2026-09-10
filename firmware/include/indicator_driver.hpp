/**
 * @file        indicator_driver.hpp
 * @brief       Class definition for onboard indicators
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>

class IndicatorDriver {
    private:
        uint8_t _ledPin; 
        uint8_t _buzzerPin; 
        uint8_t _buzzerChannel; 

        bool _ledState;
        bool _lastLedToggle; 
        unsigned long _ledInterval

        bool _buzzerActive; 
        unsigned long _buzzerStopTime; 

    public:
        IndicatorDriver(int ledPin, int buzzerPin, int buzzerChannel = 0); 
        void begin(); 
        void update(); 

        void ledOn(); 
        void ledOff(); 
        void ledBlink(unsigned long intervalMs); 

        void beep(unsigned int frequency, unsigned long durationMs); 
        void mute(); 

        
}
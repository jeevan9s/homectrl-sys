/**
 * @file        power_driver.hpp
 * @brief       Class definition for controlled power delivery and monitoring
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>

class PowerDriver {
    public:
        PowerDriver(uint8_t pEnablePin, uint8_t vSensePin);
        void begin(); 
        void energize(); 
        float monitor(); 
        void update();

    private:

        float sample();
        
        float R1 = 100000.0; 
        float R2 = 20000.0;
        float RES_FACTOR = 4095.0; // 12-bit internal ADC
        float REF_VOLTAGE = 3.3; 
        
        uint8_t _pEnablePin; 
        uint8_t _vSensePin;

        bool _isEnergizing;
        uint32_t _energizeStartTime;
        static constexpr uint32_t ENERGIZE_DELAY_MS = 50; 
        static constexpr uint32_t ENERGIZE_TIMEOUT_MS = 5000; 
};
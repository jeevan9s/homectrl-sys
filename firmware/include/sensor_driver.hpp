/**
 * @file        sensor_driver.hpp
 * @brief       Class definition for analog soil moisture sensors. 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#pragma once
#include <Arduino.h>

class MoistureSensorDriver {
    public:
        MoistureSensorDriver(uint8_t pin, uint16_t dryValue, uint16_t wetValue,         uint8_t samples = 12); 
        void begin(); 
        uint16_t readRaw(); 
        uint16_t readPCT(); 
        void calibrate(); 

                void setSamples(uint8_t samples); 
                void setWetValue(uint16_t wet); 
                void setDryValue(uint16_t dry); 
    
            private:
                uint8_t _pin; 
                uint16_t _dryValue; 
                uint16_t _wetValue;
                uint8_t _samples; 

                void waitForKey(char key);
        };;

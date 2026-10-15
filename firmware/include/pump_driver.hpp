/**
 * @file        pump_driver.hpp
 * @brief       Class definition for DC pump driver supporting PWM.
 * @author      Jeevan Sanchez
 * @date        2026-09-07
 *
 * HOMECTRL
 */

#pragma once
#include <Arduino.h>

class PumpDriver {

    public:
        PumpDriver(uint8_t pin, uint32_t frequency = 5000, uint8_t resolution = 8, uint8_t channel = 1); 

        bool begin(); 
        void start(); 
        void stop(); 
        void setSpeed(float pct); 
        bool isRunning(); 

    private:
        uint8_t m_pin; 
        uint32_t m_frequency; 
        uint8_t m_resolution; 
        uint8_t m_channel; 
        uint32_t m_maxDuty; 
        bool m_running; 
}; 
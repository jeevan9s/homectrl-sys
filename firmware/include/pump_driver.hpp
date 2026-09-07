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
#include <cstdint.h>

class PumpDriver {

    public:
        PumpDriver(uint8_t m_pin, uint8_t m_frequency, uint8_t m_resolution, uint8_t m_dutyCycle, bool m_running); 

        bool begin(); 
        void start(); 
        void stop(); 
        void setSpeed(float pct); 
        void isRunning(); 

    private:
        uint8_t m_pin; 
        uint8_t m_frequency; 
        uint8_t m_resolution; 
        uint8_t m_dutyCycle; 
        bool m_running; 
}; 
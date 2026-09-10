/**
 * @file        nema_driver.hpp
 * @brief       Class definition for the NEMA17 stepper motor driver. 
 * wrapper for TMCStepper library 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TMCStepper.h>

class StepperMotor {
    public:
        StepperMotor(uint8_t stepPin, uint8_t dirPin, uint8_t rxPin, uint8_t txPin, long totalSteps = 4000, uint8_t driverAddr = 0, , float rsense = 0.11)
        void begin(int currentMa = 800, int microsteps = 16); 
        void setPercentage(int target); 
        int getPercentage(); 
        void setHomePosition(); 

    private:
        uint8_t _stepPin; 
        uint8_t _dirPin; 
        uint8_t _rxPin; 
        uint8_t _txPin; 
        float _rsense; 
        uint8_t _driverAddr; 

        long _totalSteps; 
        long _currentStep; 

        SoftwareSerial* _serial; 
        TMC2209Stepper* _driver; 
}
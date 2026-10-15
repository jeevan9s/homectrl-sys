/**
 * @file        nema_driver.cpp
 * @brief       Class implementation for the NEMA17 stepper motor driver. 
 * wrapper for TMCStepper library 
 * @author      Jeevan Sanchez
 * @date        2026-09-09
 *
 * HOMECTRL
 */

#include "nema_driver.hpp"

StepperMotor::StepperMotor(uint8_t stepPin, uint8_t dirPin, HardwareSerial& serial, uint8_t rxPin, uint8_t txPin, long totalSteps, uint8_t driverAddr, float rsense)
: _stepPin(stepPin), _dirPin(dirPin), _rxPin(rxPin), _txPin(txPin), _totalSteps(totalSteps), _currentStep(0), _serial(serial), _driver(&serial, rsense, driverAddr) {}

void StepperMotor::begin(int currentMa, int microsteps) {
    pinMode(_stepPin, OUTPUT); 
    pinMode(_dirPin, OUTPUT); 

    _serial.begin(115200, SERIAL_8N1, _rxPin, _txPin); 
    _driver.begin(); 

    _driver.toff(5);
    _driver.rms_current(currentMa);  
    _driver.microsteps(microsteps); 
    _driver.pwm_autoscale(true); 
    _driver.en_spreadCycle(false);
}

void StepperMotor::setPercentage(int target) {
    target = constrain(target, 0, 100); 
    long targetStep = (target * _totalSteps) / 100; 
    long stepsNeeded = targetStep - _currentStep; 
    if (stepsNeeded == 0) return;

    bool clockwise = (stepsNeeded > 0); 
    stepsNeeded = abs(stepsNeeded); 

    digitalWrite(_dirPin, clockwise ? HIGH : LOW); 
    for (int i = 0; i < stepsNeeded; i++) {
        digitalWrite(_stepPin, HIGH); 
        delayMicroseconds(2);
        digitalWrite(_stepPin, LOW); 
        delayMicroseconds(800); 

        if (clockwise) _currentStep++;
        else _currentStep--;  
    }
}

int StepperMotor::getPercentage() {
    return (_currentStep * 100 / _totalSteps);
}

void StepperMotor::setHomePosition() {
    _currentStep = 0;
}


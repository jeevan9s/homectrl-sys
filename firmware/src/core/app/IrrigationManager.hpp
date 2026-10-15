/**
 * @file        IrrigationManager.hpp
 * @brief       Irrigation orchestration definitions. 
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#pragma once 
#include <Arduino.h>
#include "Constants.hpp"

class IrrigationManager {
    public:
        void begin(); 
        void update(float moisture0, float moisture1); 
        void enable(); 
        void disable(); 

        IrrigationOutput getOutput(); 
        IrrigationState getState(); 

    private:
        bool m_enabled; 
        IrrigationOutput m_output; 
        IrrigationState m_state; 
        bool irrigate(float moisture, bool irrigating); 
};

enum class IrrigationState {
    IDLE, 
    READY,
    ACTIVE,
    COMPLETE,
    FAIL
};

struct IrrigationOutput {
    bool pump0On = false;
    bool pump1On = false;
};

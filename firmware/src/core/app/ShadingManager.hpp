/**
 * @file        ShadingManager.hpp
 * @brief       Shading orchestration definitions. 
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#pragma once 
#include <Arduino.h>
#include "Constants.hpp"

class ShadingManager {
    public:
        void begin(); 
        void update(int currPos); 
        void setPos(int pos);
        void enable(); 
        void disable(); 

        ShadingOutput getOutput() const;
        ShadingState getState() const; 

    private:
        bool m_enabled; 
        ShadingOutput m_output; 
        ShadingState m_state; 
        int m_targetPos; 
};

enum class ShadingState {
    IDLE, 
    READY,
    MOVING,
    AT_POSITION,
    FAIL
};

struct ShadingOutput {
    int pos; 
};

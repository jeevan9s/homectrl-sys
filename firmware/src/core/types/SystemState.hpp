/**
 * @file        SystemState.hpp
 * @brief       Global system state definitions.  
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#pragma once 

#include "IrrigationManager.hpp"
#include "ShadingManager.hpp"

struct State {
    bool WiFiConnected;
    bool pumpsEnergized; 
    bool systemReady; 
    bool irrigationActive0; 
    bool irrigationActive1; 
    bool shadingActive; 
    bool tankFull;
    
    float soilMoisture0;
    float soilMoisture1;
    float systemVoltage;
    int floatSwitch1; 
    int floatSwitch2; 
    int shadingPct; 
};

struct IrrigationStatus {
    IrrigationState state; 
    float moisture0;
    float moisture1;
    bool pump0On;
    bool pump1On;
};

struct ShadingState {
    ShadingState state;
    int currPos;
    int targetPos;
};

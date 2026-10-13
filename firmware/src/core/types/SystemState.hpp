/**
 * @file        SystemState.hpp
 * @brief       Global system state definitions.  
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#pragma once 

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


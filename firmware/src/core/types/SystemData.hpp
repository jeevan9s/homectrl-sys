/**
 * @file        SystemData.hpp
 * @brief       Global data definitions. 
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#pragma once 

enum moistureLevel {
    DRY,
    OPTIMAL,
    WET
};

struct SMSData {
    int moisture;
    moistureLevel level;
};

struct FSWData {
    bool loSwitch;
    bool hiSwitch; 
    bool isFull;
};

struct SensorData {
    SMSData SMS0;
    SMSData SMS1;
    FSWData FSW;  
    int vPumpSense;
};



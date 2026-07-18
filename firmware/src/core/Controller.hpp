/**
 * @file        Controller.hpp
 * @brief       Controller object definition. 
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#pragma once 
#include "Data.hpp"

struct Controller {
    PumpData pump1; 
    PumpData pump2;

    StepMtrData stepMotor; 

    ALSData als; 

    SMSData sms1; 
    SMSData sms2; 

    FSWData fswHI; 

    FSWData fswLO; 
}; 

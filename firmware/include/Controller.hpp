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

<<<<<<< HEAD
    // ALSData als; 

=======
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
    SMSData sms1; 
    SMSData sms2; 

    FSWData fsw; 
}; 

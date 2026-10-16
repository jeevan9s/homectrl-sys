/**
 * @file        IrrigationTask.hpp
 * @brief       Irrigation task definition. 
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>
#include "SystemData.hpp"
#include "SystemCommand.hpp"
#include "sensor_driver.hpp"
#include "pump_driver.hpp"
#include "indicator_driver.hpp"
#include "pinouts.hpp"
#include "IrrigationManager.hpp"
#include "Constants.hpp"
#include "rtos.hpp"

void irrigationTask(void *parameter);

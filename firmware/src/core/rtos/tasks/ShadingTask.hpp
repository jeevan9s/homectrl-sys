/**
 * @file        ShadingTask.hpp
 * @brief       Shading task definitions.
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#pragma once 

#include <Arduino.h>
#include "SystemData.hpp"
#include "SystemCommand.hpp"
#include "nema_driver.hpp"
#include "indicator_driver.hpp"
#include "pinouts.hpp
#include <HardwareSerial.h>
#include "rtos.hpp"
#include "ShadingTask.hpp"

void shadingTask(void *parameter);
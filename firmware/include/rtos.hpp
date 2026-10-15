/**
 * @file        rtos.hpp
 * @brief       RTOS initialization definitions. 
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "types/SystemCommand.hpp"

bool initRTOS(); 
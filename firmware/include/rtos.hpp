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
#include "SystemCommand.hpp"
#include "IrrigationTask.hpp"
#include "SystemState.hpp"

bool initRTOS(); 

struct IrrigationTaskParams {
    QueueHandle_t commandQueue;
    QueueHandle_t statusQueue; 
}

struct ShadingTaskParams {
    QueueHandle_t commandQueue;
    QueueHandle_t statusQueue; 
}

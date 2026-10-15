/**
 * @file        rtos.cpp
 * @brief       RTOS initialization. 
 * @author      Jeevan Sanchez
 * @date        2026-10-14
 *
 * HOMECTRL
 */

#include "rtos.hpp"

static QueueHandle_t irrigationQueue = nullptr; 
static QueueHandle_t shadingQueue = nullptr; 
static QueueHandle_t irrigationStatusQueue = nullptr; 
static QueueHandle_t shadingStatusQueue = nullptr; 

static TaskHandle_t irrigationTaskHandle = nullptr; 
static TaskHandle_t shadingTaskHandle = nullptr; 
static TaskHandle_t networkingTaskHandle = nullptr; 

bool initRTOS() {

    // init queues
    irrigationQueue = xQueueCreate(10, sizeof(Command));
    irrigationStatusQueue = xQueueCreate(1, sizeof(IrrigationStatus)); 
    IrrigationTaskParams.commandQueue = irrigationQueue; 
    IrrigationTaskParams.statusQueue = IrrigationStatusQueue; 

    shadingQueue = xQueueCreate(10, sizeof(Command)); 
    shadingStatusQueue = xQueueCreate(1, sizeof(ShadingTaskParams)); // replace
    ShadingTaskParams.commandQueue = shadingQueue; 
    shadingTaskParams.statusQueue = shadingStatusQueue; 

    if (irrigationQueue == nullptr || shadingQueue == nullptr || irrigationStatusQueue == nullptr) return false; 

    // create tasks 
    BaseType_t xResult = xTaskCreate(
        networkingTask, 
        "NetworkingTask", 
        4096,
        nullptr,
        1,
        &networkingTaskHandle 
    ); 

    if (xResult != pdPASS) return false;     

    xResult = xTaskCreate(
        irrigationTask, 
        "IrrigationTask", 
        4096,
        &IrrigationTaskParams,
        2,
        &irrigationTaskHandle 
    ); 

    if (xResult != pdPASS) return false; 

   xResult = xTaskCreate(
        shadingTask, 
        "ShadingTask", 
        4096,
        &ShadingTaskParams,
        3,
        &shadingTaskHandle 
    ); 

    if (xResult != pdPASS) return false; 

    return true;
 }
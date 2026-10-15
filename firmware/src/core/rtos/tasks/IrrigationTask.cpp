/**
 * @file        IrrigationTask.cpp
 * @brief       Irrigation task implementation.
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#include "IrrigationTask.hpp"

static PumpDriver pump0(Pins::Actuators::PUMP0_EN, 5000, 8, 0);
static PumpDriver pump1(Pins::Actuators::PUMP1_EN, 5000, 8, 0);

static MoistureSensorDriver sms0(Pins::Sensors::SMS0_ADATA, DRY_THRESHOLD, WET_THRESHOLD);
static MoistureSensorDriver sms1(Pins::Sensors::SMS1_ADATA, DRY_THRESHOLD, WET_THRESHOLD);

void irrigationTask(void *parameter)
{
    if (!pump0.begin() || !pump1.begin() ||)
    {
        pump0.stop();
        pump1.stop();

        vTaskDelete(nullptr);
    }

    sms0.begin();
    sms1.begin();

    // receive commands
    auto *params = static_cast<IrrigationTaskParams*>(parameter); 


    QueueHandle_t commandQueue = params->commandQueue; 
    QueueHandle_t statusQueue = params->statusQueue; 

    IrrigationManager irrigation;
    irrigation.begin();

    Command command;

    for (;;)
    {
        while (xQueueReceive(queue, &command, 0) == pdTRUE) {

        switch (command.type)
        {
        case CommandType::START_IRRIGATION:
            irrigation.enable();
            break;

        case CommandType::STOP_IRRIGATION:
            irrigation.disable();
            break;

        default:
            break;
        }
    }

        moisture0 = sms0.readPCT();
        moisture1 = sms1.readPCT();
        irrigation.update(moisture0, moisture1);

        output = irrigation.getOutput();

        // drive pumps
        if (output.pump0On && !pump0.isRunning())
            pump0.start();
        else if (!output.pump0On && pump0.isRunning())
            pump0.stop();

        if (output.pump1On && !pump1.isRunning())
            pump1.start();
        else if (!output.pump1On && pump1.isRunning())
            pump1.stop();

        // publish status
        IrrigationStatus status {
            irrigation.getState(),
            moisture0, 
            moisture1,
            output.pump1On,
            output.pump2On
        };

        xQueueSend(statusQueue, *status);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
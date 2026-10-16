/**
 * @file        ShadingTask.cpp
 * @brief       Shading task implementation.
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#include "ShadingTask.hpp"

extern HardwareSerial Serial; 
static StepperMotor stepper(Pins::Actuators::TMC_STEP, Pins::Actuators::TMC_DIR, Serial, Pins::S3_RXD, Pins::S3_TXD);

void shadingTask(void *parameter) {
    stepper.begin(); 
    stepper.setHomePosition(); 

    auto *params = static_cast<ShadingTaskParams*>(parameter); 
    QueueHandle_t commandQueue = params.commandQueue; 
    QueueHandle_t statusQueue = params.statusQueue;

    ShadingManager shading;
    shading.begin();

    ShadingState lastIndicatorState = ShadingState::FAIL;
    Command command; 

    for(;;) {
        while (xQueueReceive(commandQueue, &command, 0) == pdTRUE) {
            switch(command.type) {
                case CommandType::START_SHADING:
                    shading.enable();
                    break;
                
                case CommandType::STOP_SHADING:
                    shading.disable();
                    break;
                
                default:
                    break;
            }
        }

        int currPos = stepper.getPercentage(); 
        shading.update(currPos); 

        ShadingOutput output = shading.getOutput();
        const ShadingState shadingState = shading.getState();

        if (shadingState != lastIndicatorState)
        {
            switch (shadingState)
            {
            case ShadingState::MOVING:
                indicator.ledBlink(250);
                break;

            case ShadingState::READY:
                indicator.ledOn();
                break;

            default:
                indicator.ledOff();
                break;
            }

            lastIndicatorState = shadingState;
        }

        // drive motor
      
        // publish status
        ShadingStatus status {
            shading.getState(),
            currPos,
            output.pos,
        };

        xQueueOverwrite(statusQueue, &status);

        vTaskDelay(pdMS_TO_TICKS(100));
        
    }
}
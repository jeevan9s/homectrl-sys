/**
 * @file        telemetry.hpp
 * @brief       Serialization file for streaming.  
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "telemetry.hpp"

void Telemetry::serialize(const Controller &state, JsonDocument &doc) {
    doc["timestamp"] = millis(); 
}
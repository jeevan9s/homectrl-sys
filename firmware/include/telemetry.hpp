/**
 * @file        telemetry.hpp
 * @brief       Header for telemtry serialization.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Controller.hpp"

class Telemetry
{
public:
    static void serialize(const Controller &state, JsonDocument &doc);
};

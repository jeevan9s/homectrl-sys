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

void Telemetry::serialize(const Controller &state, JsonDocument &doc)
{
    doc["timestamp"] = millis();

<<<<<<< HEAD
    JsonObject pump1 = doc["PUMP1"].to<JsonObject>();
    JsonObject pump2 = doc["PUMP1"].to<JsonObject>();
=======
    JsonObject pump1 = doc["PUMP1"].to<JsonObject>(); 
    JsonObject pump2 = doc["PUMP2"].to<JsonObject>(); 
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
    JsonObject stepper = doc["STEP"].to<JsonObject>();
    JsonObject sms1 = doc["SMS1"].to<JsonObject>();
    JsonObject sms2 = doc["SMS2"].to<JsonObject>();
    // JsonObject als = doc["ALS1"].to<JsonObject>();
    JsonObject fsw = doc["FSW"].to<JsonObject>();

<<<<<<< HEAD
    pump1["state"] = static_cast<int>(state.pump1.state);
    pump2["state"] = static_cast<int>(state.pump2.state);
    stepper["state"] = static_cast<int>(state.stepMotor.state);

    sms1["raw"] = state.sms1.raw;
    sms1["moisture"] = state.sms1.moisture;
    sms1["isHydrated"] = state.sms1.hydrated;
=======
    pump1["state"] = static_cast<int>(state.pump1.state); 
    pump2["state"] = static_cast<int>(state.pump2.state); 

    stepper["state"] = static_cast<int>(state.stepMotor.state); 
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325

    sms2["raw"] = state.sms2.raw;
    sms2["moisture"] = state.sms2.moisture;
    sms2["isHydrated"] = state.sms2.hydrated;

    fsw["tankStatus"] = state.fsw.empty;
}
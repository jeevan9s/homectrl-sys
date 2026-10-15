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

void Telemetry::serialize(const State &state, JsonDocument &doc)
{
    doc["timestamp"] = millis();

    JsonObject pump1 = doc["PUMP1"].to<JsonObject>();
    JsonObject pump2 = doc["PUMP2"].to<JsonObject>();
    JsonObject stepper = doc["STEP"].to<JsonObject>();
    JsonObject sms1 = doc["SMS1"].to<JsonObject>();
    JsonObject sms2 = doc["SMS2"].to<JsonObject>();
    JsonObject fsw = doc["FSW"].to<JsonObject>();
    JsonObject sys = doc["SYS"].to<JsonObject>();

    // dashboard state codes: 0 = idle, 2 = running
    pump1["state"] = state.irrigationActive0 ? 2 : 0;
    pump1["enable"] = state.irrigationActive0;
    pump2["state"] = state.irrigationActive1 ? 2 : 0;
    pump2["enable"] = state.irrigationActive1;

    stepper["state"] = state.shadingActive ? 2 : 0;
    stepper["enable"] = state.shadingActive;
    stepper["shadePct"] = state.shadingPct;

    sms1["moisture"] = state.soilMoisture0;
    sms2["moisture"] = state.soilMoisture1;

    fsw["tankStatus"] = !state.tankFull;

    sys["wifi"] = state.WiFiConnected;
    sys["ready"] = state.systemReady;
    sys["pumpsEnergized"] = state.pumpsEnergized;
    sys["voltage"] = state.systemVoltage;
}
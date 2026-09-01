/**
 * @file        WebSocketServer.cpp
 * @brief       Handles client connect, disconnect, telemetry
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "WebSocketServer.hpp"

WebSocketServer::WebSocketServer(AsyncWebServer &server, Controller &stateRef) : state(stateRef)
{
    server.addHandler(&ws);
}

void WebSocketServer::begin()
{
    ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
               {
        if (type == WS_EVT_CONNECT) {
            this->clientConnected = true;
            activeBlinkPin = Pins::Indicators::WIFI_LED;
            blinkCount = 3;
            blinksRemaining = blinkCount * 2;
        }

        if (type == WS_EVT_DISCONNECT) {
            this->clientConnected = false;
            activeBlinkPin = Pins::Indicators::DBG_LED;
            blinkCount = 3;
            blinksRemaining = blinkCount * 2;
        }

        if (type == WS_EVT_DATA) {
            this->clientConnected = true; 
            activeBlinkPin = Pins::Indicators::WIFI_LED; 
            blinkCount = 3;
            blinksRemaining = blinkCount * 2; 

            AwsFrameInfo* info = (AwsFrameInfo*)arg; 
            if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
                data[len] = 0;
                String message = (char*)data; 
                this->handleCommand(message); 
            }
        } });
}

void WebSocketServer::update(const Controller &state)
{
    ws.cleanupClients();

    if (millis() - lastTelemetryTime < 100)
        return;
    lastTelemetryTime = millis();

    JsonDocument doc;

    Telemetry::serialize(state, doc);

    String payload;
    serializeJson(doc, payload);

    // Serial.println("websocket PAYLOAD: " + payload);

    ws.textAll(payload);
}
void WebSocketServer::handleCommand(const String &payload)
{
    // References can't be null, so you don't need 'if (!state)'
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
        return;

    if (!doc["cmd"].isNull()) {
    {
        int rawCmd = doc["cmd"];
        int val = doc["val"] | 0;

        auto cmd = static_cast<DashboardCommands>(rawCmd);

        switch (cmd)
        {
        case DashboardCommands::IRRIGATE_1:
            state.pump1.enable = val; // Use '.' instead of '->'
            break;
        case DashboardCommands::IRRIGATE_2:
            state.pump2.enable = val;
            break;

        case DashboardCommands::SHADE_DEFAULT:
            state.stepMotor.enable = val;
            state.stepMotor.shadePct = 0;
            break;

        case DashboardCommands::SHADE_PCT:
            state.stepMotor.shadePct = constrain(val, 0, 100);
            state.stepMotor.enable = 1;
            break;

        default:
            break;
        }
    }
}
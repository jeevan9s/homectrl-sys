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
#include "rtos.hpp"

WebSocketServer::WebSocketServer(AsyncWebServer &server)
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

void WebSocketServer::update(const State &state)
{
    ws.cleanupClients();

    if (millis() - lastTelemetryTime < 100)
        return;
    lastTelemetryTime = millis();

    JsonDocument doc;

    Telemetry::serialize(state, doc);

    String payload;
    serializeJson(doc, payload);


    ws.textAll(payload);
}
void WebSocketServer::handleCommand(const String &payload)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error || doc["cmd"].isNull())
        return;

    int val = doc["val"] | 0;
    Command command{};
    QueueHandle_t queue = nullptr;

    switch (static_cast<DashboardCommand>(doc["cmd"].as<int>()))
    {
    // irrigation commands carry the pump index (0 or 1) as their value
    case DashboardCommand::IRRIGATE_1:
        command = {val ? CommandType::START_IRRIGATION : CommandType::STOP_IRRIGATION, 0};
        queue = getIrrigationQueue();
        break;
    case DashboardCommand::IRRIGATE_2:
        command = {val ? CommandType::START_IRRIGATION : CommandType::STOP_IRRIGATION, 1};
        queue = getIrrigationQueue();
        break;

    case DashboardCommand::SHADE_DEFAULT:
        command = {val ? CommandType::SET_SHADING_POS : CommandType::STOP_SHADING, 0};
        queue = getShadingQueue();
        break;

    case DashboardCommand::SHADE_PCT:
        command = {CommandType::SET_SHADING_POS, constrain(val, 0, 100)};
        queue = getShadingQueue();
        break;

    default:
        return;
    }

    if (queue != nullptr)
        xQueueSend(queue, &command, 0);
}
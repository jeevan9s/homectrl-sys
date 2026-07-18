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
    });
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
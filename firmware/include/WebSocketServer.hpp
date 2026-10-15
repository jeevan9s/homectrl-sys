/**
 * @file        WebSocketServer.hpp
 * @brief       Header for WebSocketServer handling client connect, disconnect, telemetry
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "telemetry.hpp"
#include "config.hpp"
#include "SystemState.hpp"
#include "SystemCommand.hpp"

// wire-protocol command ids sent by the dashboard as {"cmd": id, "val": n}
enum class DashboardCommand {
    IRRIGATE_1 = 0,
    IRRIGATE_2 = 1,
    SHADE_DEFAULT = 2,
    SHADE_PCT = 3
};

class WebSocketServer {
    public:
        WebSocketServer(AsyncWebServer &server); 
        void begin(); 
        void update(const State &state); 
        bool clientConnected;
    private:
        AsyncWebSocket ws{"/ws"}; 
        static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
        void handleCommand(const String &payload);    
        uint32_t lastTelemetryTime = 0; 
};

 
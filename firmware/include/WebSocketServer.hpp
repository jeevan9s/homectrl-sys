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
#include "Controller.hpp"

class WebSocketServer {
    public:
        WebSocketServer(AsyncWebServer &server, Controller &state); 
        void begin(); 
        void update(const Controller &state); 
        bool clientConnected;
    private:
        AsyncWebSocket ws{"/ws"}; 
        static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
        void handleCommand(const String &payload);    
        uint32_t lastTelemetryTime = 0; 
<<<<<<< HEAD
        Controller &state;
=======

        Controller* systemState;
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
};

 
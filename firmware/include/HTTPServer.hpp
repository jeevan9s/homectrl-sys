/**
 * @file        HTTPServer.hpp
 * @brief       Header for HTTP router.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#pragma once

#include <ESPAsyncWebServer.h>
#include "WebSocketServer.hpp"
#include "SystemState.hpp"

class HTTPServer {
public:
    HTTPServer(); 
    void begin();
    void update(const State &state);

private:
    AsyncWebServer server;
    WebSocketServer websocket;
};
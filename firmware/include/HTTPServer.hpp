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
#include "Controller.hpp"

class HTTPServer {
public:
    HTTPServer(Controller &state); 
    void begin();
    void update(Controller &controllerRef);

private:
    AsyncWebServer server;
    WebSocketServer websocket;
};
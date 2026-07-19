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
    HTTPServer();
    void begin();
    void update(Controller &state);

private:
    AsyncWebServer server;
    WebSocketServer websocket;
};
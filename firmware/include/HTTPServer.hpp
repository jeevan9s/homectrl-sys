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
<<<<<<< HEAD
    HTTPServer(Controller &state); 
=======
    HTTPServer(Controller &controller);
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
    void begin();
    void update(Controller &controllerRef);

private:
    AsyncWebServer server;
    WebSocketServer websocket;
};
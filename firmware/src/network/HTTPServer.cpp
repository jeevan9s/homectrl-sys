/**
 * @file        HTTPServer.cpp
 * @brief       HTTP router.
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "HTTPServer.hpp"

<<<<<<< HEAD
HTTPServer::HTTPServer(Controller &state)
    : server(80),
      websocket(server, state)
=======
HTTPServer::HTTPServer(Controller & controller)
    : server(80),
      websocket(server, controller)
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
{
}

void HTTPServer::begin() {
  server.on("/", WebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "homectrl --online");
  });

  websocket.begin();
  server.begin();
}

void HTTPServer::update(Controller &state) {
    websocket.update(state);
}


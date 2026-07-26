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

HTTPServer::HTTPServer(Controller & controller)
    : server(80),
      websocket(server, controller)
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


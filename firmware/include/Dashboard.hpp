
/**
 * @file        Dashboard.cpp
 * @brief       Connects to Wi-Fi and starts the local async web server and WebSocket endpoints
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include "WebSocketServer.hpp"
#include "HTTPServer.hpp"

void run_dashboard();

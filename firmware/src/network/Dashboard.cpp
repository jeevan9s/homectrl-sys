
/**
 * @file        Dashboard.cpp
 * @brief       Connects to Wi-Fi and starts the local async web server and WebSocket endpoints
 * @author      Jeevan Sanchez
 * @date        2026-07-15
 *
 * HOMECTRL
 */

#include "Dashboard.hpp"

extern HTTPServer http;
extern bool dashboardRunning;

void run_dashboard()
{
    WiFi.mode(WIFI_STA);
    Serial.println("WIFI --connecting");
    WiFi.onEvent([](WiFiEvent_t event) {
        if (event == IP_EVENT_STA_GOT_IP) {
            Serial.println("WIFI --connected");
            activeBlinkPin = Pins::Indicators::WIFI_LED;
            blinkCount = 3;
            blinksRemaining = blinkCount * 2;
        } else if (event == WIFI_EVENT_STA_DISCONNECTED) {
            Serial.println("WIFI --disconnected");
            activeBlinkPin = Pins::Indicators::DBG_LED;
            blinkCount = 3;
            blinksRemaining = blinkCount * 2;
        }
    });

    WiFi.begin(ssid, pswd);

    http.begin();

    dashboardRunning = true;
}

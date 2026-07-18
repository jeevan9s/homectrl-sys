/**
 * @file        main.cpp
 * @brief       Main Entry Point
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "config.hpp"
#include "test.hpp"
#include "Dashboard.hpp"

bool menuShown = false;
HTTPServer http{cameraDriver};
bool dashboardRunning = false;

void displayMenu()
{
    Serial.println("\n--- homectrl ---");
    Serial.println("[SPACE] launch dashboard");
    Serial.println(" [t] : launch test bench");
    Serial.println(" [s] : scan I2C bus");
    Serial.println("------------------------");
}

void runTaskSpace()
{
    Serial.println("\n>> ---launching dashboard");
    run_dashboard();
}

void runTaskT()
{
    Serial.println("\n>> ---launching test bench");
    run_test_bench();
}

void runTaskS()
{
    Serial.println("\n>> ---scanning I2C bus");
    scanI2C();
    delay(1000);
}

void setup()
{
    Serial.begin(921600);

    while (!Serial && millis() < 4000)
    {
        delay(10);
    }

    Serial.println("\n==============================");
    Serial.println("homectrl ---initializing");

    mcp.pinMode(Pins::Indicators::DBG_LED, OUTPUT);
    mcp.pinMode(Pins::Indicators::WIFI_LED, OUTPUT);

    led_startup();
    displayMenu();
}

void loop()
{
    if (blinksRemaining > 0)
    {
        blinkP(activeBlinkPin, blinkCount);
    }
    scheduler.update(currentState);

    if (dashboardRunning)
    {
        http.update(currentState);
    }

    if (!menuShown && millis() > 5000)
    {
        displayMenu();
        menuShown = true;
    }

    if (Serial.available() > 0)
    {
        char choice = Serial.read();
        menuShown = true;

        switch (choice)
        {
        case 't':
        case 'T':
            runTaskT();
            displayMenu();
            break;

        case 's':
        case 'S':
            runTaskS();
            displayMenu();
            break;

        case 'm':
        case 'M':
            displayMenu();
            break;

        case ' ':
            runTaskSpace();
            break;

        case '\n':
        case '\r':
            break;

        default:

            break;
        }
    }
}

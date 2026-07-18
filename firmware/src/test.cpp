/**
 * @file        test.cpp
 * @brief       Hardware validation
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "pinouts.hpp"


void run_test_bench()
{
    while (true)
    {
        Serial.println("\n=== TEST BENCH ===");
        Serial.println("1 : POWER ");
        Serial.println("2 : WIFI");
        Serial.println("3 : PUMPS");
        Serial.println("4 : STEPPER MOTOR");
        Serial.println("5 : MOISTURE SENSORS");
        Serial.println("6 : FLOAT SWITCHES");
        Serial.println("x : EXIT");

        while (!Serial.available())
        {
            delay(10);
        }

        char choice = Serial.read();

        switch (choice)
        {
        case '1':
            break;

        case '2':
            break;

        case '3':
            break;

        case '4':
            break;

        case '5':
            break;

        case '6':
            break;

        case 'x':
        case 'X':
            return;
        }
    }
}

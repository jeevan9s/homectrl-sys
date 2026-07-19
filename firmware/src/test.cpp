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


void test_power() {
    ///
}

void test_wifi(const char* ssid, const char* pswd) {
    Serial.printf("\nconnecting to: %s\n", ssid);
    
    WiFi.disconnect(true);
    delay(100);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pswd);

    int timeout_idx = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(Pins::Indicators::WIFI_LED, HIGH); 
        delay(200); 
        digitalWrite(Pins::Indicators::WIFI_LED, LOW); 
        delay(200); 

        Serial.print(".");
        timeout_idx++;
        if (timeout_idx >= 28)
            break;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.printf("\nconnected to: %s\n", ssid);
        digitalWrite(Pins::Indicators::WIFI_LED, HIGH);
    }
    else
    {
        Serial.printf("\nFailed to connect. Status: %d\n", WiFi.status());
    }
}

void test_pump() {
    ///
}

void test_stepper() {
    ///
}

void test_sms() {
    ///
}

void test_indicators() {
    ///
}



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
        Serial.println("6 : INDICATORS");
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

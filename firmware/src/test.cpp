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
#include "test.hpp"

CRGB rgb_leds[NUM_LEDS];
FastLED.addLeds<WS2812B, RGB_DATA_PIN, GRB>(rgb_leds, NUM_LEDS);
rgb_leds[0] = CRGB::Black;
FastLED.show();

void test_power()
{
    pinMode(Pins::Power::VPMP_EN, OUTPUT);
    pinMode(Pins::Power::VSMS_EN, OUTPUT);

    digitalWrite(Pins::Power::VPMP_EN, HIGH);
    digitalWrite(Pins::Power::VSMS_EN, HIGH);
    Serial.println("pump supply --ON");
    Serial.println("sensor supply --ON");
    delay(10000);

    Serial.println("testing VPUMP SENSE...");
    int raw = analogRead(Pins::Power::VPMP_SENSE);
    float voltage = (raw / 4095.0) * 3.3 * ((100.0 + 20.0) / 20.0);
    Serial.printf("VPUMP sense: %.2fV\n", voltage);
}

void test_wifi(const char *ssid, const char *pswd)
{
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

void test_pump()
{
    pinMode(Pins::Actuators::PUMP1_EN, OUTPUT);
    pinMode(Pins::Actuators::PUMP2_EN, OUTPUT);
    pinMode(Pins::Power::VPMP_EN, OUTPUT);

    digitalWrite(Pins::Power::VPMP_EN, HIGH);
    delay(50);
    Serial.println("pump supply --ON");

    digitalWrite(Pins::Actuators::PUMP1_EN, HIGH);
    digitalWrite(Pins::Actuators::PUMP2_EN, HIGH);
    Serial.println("pumps --ON");
    delay(10000);
    digitalWrite(Pins::Actuators::PUMP1_EN, LOW);
    digitalWrite(Pins::Actuators::PUMP2_EN, LOW);
    Serial.println("pumps --OFF");
}

void test_stepper()
{
    ///
}

void test_sms()
{
    ///
}

void test_indicators()
{
    blinkLED(Pins::Indicators::DBG_LED, 4);
    blinkLED(Pins::Indicators::WIFI_LED, 4);

    uint8_t fluidBrightness = beatsin8(35, 20, 90);
    rgb_leds[0] = CHSV(55, 255, fluidBrightness);
    FastLED.show();
    delay(5000);
    // turn off
    rgb_leds[0] = CRGB::Black;
    FastLED.show();

    ledcWrite(BUZZER_PIN, 128);
    delay(3000);

    ledcWrite(BUZZER_PIN, 0);
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

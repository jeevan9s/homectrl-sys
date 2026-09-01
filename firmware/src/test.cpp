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

TMC2209Stepper driver(&Serial2, R_SENSE, DRIVER_ADDRESS);

CRGB rgb_leds[NUM_LEDS];

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
    pinMode(Pins::Actuators::TMC_ENN, OUTPUT);
    pinMode(Pins::Actuators::TMC_STEP, OUTPUT);
    pinMode(Pins::Actuators::TMC_DIR, OUTPUT);
    pinMode(Pins::Actuators::TMC_DIAG, INPUT);

    digitalWrite(Pins::Actuators::TMC_ENN, HIGH);

    Serial2.begin(115200, SERIAL_8N1, Pins::S3_RXD, Pins::S3_TXD);

    driver.begin();
    driver.toff(4);
    driver.rms_current(800);
    driver.microsteps(16);
    driver.pwm_autoscale(true);
    driver.en_spreadCycle(false);

    uint32_t drv_status = driver.DRV_STATUS();
    if (drv_status == 0x00000000 || drv_status == 0xFFFFFFFF)
    {
        Serial.println("UART Error");
        return;
    }

    digitalWrite(Pins::Actuators::TMC_ENN, LOW);
    digitalWrite(Pins::Actuators::TMC_DIR, HIGH);

    for (int i = 0; i < 400; i++)
    {
        digitalWrite(Pins::Actuators::TMC_STEP, HIGH);
        delayMicroseconds(600);
        digitalWrite(Pins::Actuators::TMC_STEP, LOW);
        delayMicroseconds(600);
    }
}

void test_sms()
{
    pinMode(Pins::Power::VSMS_EN, OUTPUT);
    digitalWrite(Pins::Power::VSMS_EN, HIGH);
    delay(50);

    analogReadResolution(12);
    analogSetPinAttenuation(Pins::Data::SMS1_ADATA, ADC_11db);

    const int NUM_SAMPLES = 10;
    int32_t sum = 0;

    analogRead(Pins::Data::SMS1_ADATA);
    delay(5);

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        sum += analogRead(Pins::Data::SMS1_ADATA);
        delay(2);
    }

    int32_t raw = sum / NUM_SAMPLES;

    digitalWrite(Pins::Power::VSMS_EN, LOW);

    Serial.print("raw SMS Value: ");
    Serial.println(raw);
}

void test_indicators()
{

    blinkLED(Pins::Indicators::DBG_LED, 4);
    blinkLED(Pins::Indicators::WIFI_LED, 4);

    rgb_leds[0] = CRGB::Black;
    FastLED.show();
    uint8_t fluidBrightness = beatsin8(35, 20, 90);
    rgb_leds[0] = CHSV(55, 255, fluidBrightness);
    FastLED.show();
    delay(5000);
    // turn off
    rgb_leds[0] = CRGB::Black;
    FastLED.show();

    ledcWrite(Pins::Indicators::BUZZ_EN, 128);
    delay(3000);

    ledcWrite(Pins::Indicators::BUZZ_EN, 0);
}

void test_float_switch()
{

    pinMode(Pins::Data::FSW1_SIG, INPUT_PULLUP);

    int state = digitalRead(Pins::Data::FSW1_SIG);

    Serial.print("FSW --RAW state: ");
    if (state == LOW)
    {
        Serial.println("LOW --closed");
    }
    else
    {
        Serial.println("HIGH --open");
    }
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
        Serial.println("7 : INDICATORS");
        Serial.println("x : EXIT");

        while (!Serial.available())
        {
            delay(10);
        }

        char choice = Serial.read();

        switch (choice)
        {
        case '1':
            test_power();
            break;

        case '2':
            test_wifi(ssid, pswd);
            break;

        case '3':
            test_pump();
            break;

        case '4':
            test_stepper();
            break;

        case '5':
            test_sms();
            break;

        case '6':
            test_float_switch();
            break;

        case '7':
            test_indicators();
            break;

        case 'x':
        case 'X':
            return;
        }
    }
}

/**
 * @file        sms_calibrate.cpp
 * @brief       Standalone soil moisture sensor calibration routine.
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "sms_calibrate.hpp"
#include "pinouts.hpp"
#include "sensor_driver.hpp"

static constexpr uint32_t STEP_TIMEOUT_MS = 60000;

// discards pending input, then waits for the key (case-insensitive)
static bool waitForKey(char key) {
    while (Serial.available() > 0) Serial.read();

    uint32_t start = millis();
    while (millis() - start < STEP_TIMEOUT_MS) {
        while (Serial.available() > 0) {
            if (tolower(Serial.read()) == key) return true;
        }
        delay(10);
    }
    Serial.println("timed out.");
    return false;
}

static void calibrateSensor(uint8_t pin, const char* name) {
    MoistureSensorDriver sensor(pin, 0, 0);
    sensor.begin();

    Serial.printf("\n== %s ==\nwipe sensor dry, leave in open air, send 'd'.\n", name);
    if (!waitForKey('d')) return;
    uint16_t dry = sensor.readRaw();

    Serial.println("submerge sensor in water, send 'w'.");
    if (!waitForKey('w')) return;
    uint16_t wet = sensor.readRaw();

    Serial.printf("%s | dry: %u | wet: %u\n", name, dry, wet);
    if (dry <= wet) Serial.println("warning: dry should read higher than wet; check the sensor and retry.");
}

void run_sms_calibration() {
    pinMode(Pins::Power::VSMS_EN, OUTPUT);
    digitalWrite(Pins::Power::VSMS_EN, HIGH);
    delay(500); // sensor settle time

    Serial.println("\n--- SMS calibration ---");
    calibrateSensor(Pins::Data::SMS0_ADATA, "SMS0");
    calibrateSensor(Pins::Data::SMS1_ADATA, "SMS1");
    Serial.println("\ndone. copy values into Constants.hpp.");

    digitalWrite(Pins::Power::VSMS_EN, LOW);
}

// sequential blink test code for the controller
#include <Arduino.h>
#include "config.h"

void setup() {
    pinMode(sysLED, OUTPUT);
    pinMode(wifiLED, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    Serial.begin(9600);
    Serial.println("controller initialized");
}

void blinkOne(int pin, int delayTime = 200) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
}

void loop() {
    blinkOne(sysLED);
    blinkOne(wifiLED);
    blinkOne(LED1);
    blinkOne(LED2);
}

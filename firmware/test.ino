// initial testing code for the controller
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

void loop() {
    digitalWrite(sysLED, HIGH);
    digitalWrite(wifiLED, HIGH);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
}
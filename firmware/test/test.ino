// testing for homectrl v2/rB
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <Wire.h>

const int ledPins[] = {41, 42};
const int wifiLed = 41;

// argb led defs 
int LED_PIN = 14;
int LED_COUNT = 1; 

const int pumpPin0 = 17;
const int pumpPin1 = 18;

const int step = 5;
const int dir = 6;
const int stepENN = 16;

const int SDA = 1;
const int SCL = 2;

const int adcDRDY = 11;

const int smsEN0 = 13;
const int smsEN1 = 12;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t magenta = strip.Color(255, 0, 255);

const char* ssid = ""; 
const char* pswd = "";

void blinkLed(const int pin, int ms) {
    digitalWrite(pin, HIGH); 
    delay(ms); 
    digitalWrite(pin, LOW);
    delay(ms);
}

void ledTest() {
    for (int i = 0; i < 2; i++) {
        Serial.printf("flashing LED on GPIO%d\n", ledPins[i]);
        blinkLed(ledPins[i], 800); 
    }
    strip.SetPixelColor(1, magenta);
}

void enablePump(const int pumpPin) {
    digitalWrite(pumpPin, HIGH); 
    Serial.printf("pump %d ON", pumpPin); 
    delay(1000); 
    digitalWrite(pumpPin, LOW);
    Serial.printf("pump %d OFF", pumpPin); 
}

void disablePump(const int pumpPin, int ms = 0) {
    digitalWrite(pumpPin, LOW);
    Serial.prntf("pump %d OFF", pumpPin);
    
    if (ms > 0) {
        delay(ms);
    }
}

void wifiTest(const char* ssid, const char* pswd) {
    Serial.printf("\nconnecting to: %s\n", ssid);
    WiFi.begin(ssid, pswd); 

    int timeout_idx = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        blinkLed(wifiLed, 300);
        Serial.print(".");
        timeout_idx++;
        if (timeout_idx=10)
          break;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\connected to: %s\n", ssid);
        digitalWrite(wifiLed, HIGH);
    } else {
        Serial.println("\nfailed to connect.");
    }
}

void enableSensor(int smsEN, int ms) {
    digitalWrite(smsEN, HIGH);
    delay(ms); 
}

void disableSensor(int smsEN, int ms = 0) {
    digitalWrite(smsEN, LOW);
    if (ms > 0) {
        delay(ms);
    }
}

void adcTest() {

}

void alsTest() {

}

void setup() { 
    Serial.begin(115200); 
    delay(1000);
    
    Serial.print("-----homectrl v2 testing-----");
    Serial.print("0: LED test | 1: pump 0 test | 2: pump 1 test | 3: step. motor test | 4: ADC test | 5: ALS test | 6: wifi test")

    disablePump(pumpPin0, pumpPin1);
    disableSensor(smsEN0);
    disableSensor(smsEN1);

    for (int i = 0; i < 2; i++) {
        pinMode(ledPins[i], OUTPUT);
    }

    for (int i = 0; i < 2; i++) {
        digitalWrite(ledPins[i], LOW);
    }

    strip.begin();
    strip.show();
}

void loop() {
    if (Serial.available() > 0) {
        char input = Serial.read();

        switch (input) {
            
        }
    }

}
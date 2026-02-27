/*
* testing FW for homectrl v2/revB
* author -> jeevan sanchez
* feb 2026
*/

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include <Adafruit_ADS1X15.h>
#include <TMCStepper.h>


const int ledPins[] = {41, 42};
const int wifiLed = 41;

// argb led defs 
int LED_PIN = 14;
int LED_COUNT = 1; 

const int pumpPin0 = 17;
const int pumpPin1 = 18;

const int step = 5;
const int dir = 6;
const int stepENN = 16; // active-low
const int rx = 15;
const int tx = 7;
#define R_SENSE 0.11f
#define DRIVER_ADDR 0b00

const int SDAPin = 1;
const int SCLPin = 2;

const int adcDRDY = 11;
#define ADC_ADDR = 0x48
#define ALS_ADDR = 0x29

const int smsEN0 = 13;
const int smsEN1 = 12;

// update after testing, calbiration constants for SMS
const float dryV = 2.5; 
const float wetV = 1.25;

TMC2209Stepper driver(&Serial2, R_SENSE, DRIVER_ADDR);

Adafruit_TSL2591 als = Adafruit_TSL2591(1);
Adafruit_ADS1115 adc;
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
    Serial.print("adressable RGB LED on");
    strip.setPixelColor(1, magenta);
}

void ledSetup() {
    for (int i = 0; i < 2; i++) {
    pinMode(ledPins[i], OUTPUT);
    }

    for (int i = 0; i < 2; i++) {
        digitalWrite(ledPins[i], LOW);
    }

    strip.begin();
    strip.show();
}

void enablePump(const int pumpPin, int ms = 1000) {
    digitalWrite(pumpPin, HIGH); 
    Serial.printf("pump %d ON", pumpPin); 
    delay(ms); 
    digitalWrite(pumpPin, LOW);
    Serial.printf("pump %d OFF", pumpPin); 
}

void disablePump(const int pumpPin, int ms = 0) {
    digitalWrite(pumpPin, LOW);
    Serial.printf("pump %d OFF", pumpPin);
    
    if (ms > 0) {
        delay(ms);
    }
}

// step = stepper motor
void stepSetup() {
    pinMode(step, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(stepENN, OUTPUT);
    digitalWrite(stepENN, HIGH);
    digitalWrite(dir, LOW);
}

void stepUARTSetup() {
    Serial2.begin(115200, SERIAL_8N1, rx, tx);
    driver.begin();

    driver.toff(5); 
    driver.rms_current(600);
    driver.microsteps(16);

    driver.pwm_autoscale(true);
    driver.en_spreadCycle(false);
}

void testStep(int steps, bool clockwise ) {
    Serial.print("testing stepper motor");

    digitalWrite(stepENN, LOW);
    driver.toff(5);
    driver.shaft(clockwise);

    for (int i = 0; i < steps; i++) {
        digitalWrite(step, HIGH);
        delayMicroseconds(800);
        digitalWrite(step, LOW);
        delayMicroseconds(800);
    }

    driver.toff(0);
    digitalWrite(stepENN, HIGH);
}

void wifiTest(const char* ssid, const char* pswd) {
    Serial.printf("\nconnecting to: %s\n", ssid);
    WiFi.begin(ssid, pswd); 

    int timeoutIdx = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        blinkLed(wifiLed, 300);
        Serial.print(".");
        timeoutIdx++;
        if (timeoutIdx=10)
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

void alsSetup() {
    als.begin();
    als.setGain(TSL2591_GAIN_MED);      
    als.setTiming(TSL2591_INTEGRATIONTIME_300MS); 
}

float getALSReading() {
    uint32_t lum = als.getFullLuminosity(); 
    uint16_t ir = lum >> 16;
    uint16_t full = lum & 0xfff;

    return als.calculateLux(full, ir);
}

void alsTest() {
    Serial.print("testing ALS for lux reading");
    float lux = getALSReading();

    if (lux < 0 || lux > 88000) {
        Serial.print("invalid reading");
    } else {
        Serial.print("lux: ");
        Serial.println(lux, 2);
    }
}

void adcSetup() {
    if (!adc.begin()) {
        Serial.print("failed to init. ADC");
        while (1);
    }

    adc.setGain(GAIN_TWOTHIRDS);
}

int16_t getADCRaw(int ch) {
    return adc.readADC_SingleEnded(ch); 
}

float adcRawToVoltage(int ch) {
    int16_t raw = getADCRaw(ch);
    float voltage = (raw * 0.1875) / 1000.0; //0.1875mV per bit
    return voltage;
}

float getMoisture(int ch) {
    float currV = adcRawToVoltage(ch);
    float moisture = (currV - dryV) * (100.0 - 0.0) / (wetV - dryV) + 0.0; // consts determined from testing
    
    return constrain(moisture, 0.0, 100.0);
}

void smsTest(int ch) {
    Serial.print("testing SMS on channel"); 
    Serial.println(ch);

    float moisture = getMoisture(ch);
    if (isnan(moisture)) {
        Serial.print("failed to get moisture");
    } else {
        Serial.printf("SMS%d reading: %.1f\n", ch, moisture);
    }
}

void setup() { 
    Serial.begin(115200); 
    Wire.begin(SDAPin, SCLPin);
    delay(1000);

    alsSetup();
    adcSetup();
    ledSetup();
    stepSetup();
    stepUARTSetup();

    disablePump(pumpPin0, pumpPin1);
    disableSensor(smsEN0);
    disableSensor(smsEN1);
    
    Serial.print("-----homectrl v2 testing-----");
    Serial.print("0: LED test | 1: pump 0 test | 2: pump 1 test | 3: step. motor test | 4: SMS0 test | 5: SMS1 test | 6: ALS test | 7: wifi test");

}

void loop() {
    if (Serial.available() > 0) {
        char input = Serial.read();

        switch (input) {
            case '0':
                ledTest();
                break;
            
            case '1':
                enablePump(pumpPin0);
                break;           
            
            case '2':
                enablePump(pumpPin1);
                break;

            case '3':
                testStep(3200, true);
                break;

            case '4':
                smsTest(0);
                break;

            case '5':
                smsTest(1);
                break;

            case '6':
                alsTest();
                break;

            case '7':
                wifiTest(ssid, pswd);
                break;
            
            default:
                Serial.print("test board functionality with num keys");
            
        }
    }

}
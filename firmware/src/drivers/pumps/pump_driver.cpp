/**
 * @file        pump_driver.cpp
 * @brief       Class implementation for DC pump driver supporting PWM.
 * @author      Jeevan Sanchez
 * @date        2026-09-07
 *
 * HOMECTRL
 */

#include <Arduino.h>
#include "pump_driver.hpp"

PumpDriver::PumpDriver(uint8_t m_pin, uint8_t m_frequency = 5000, uint8_t m_resolution = 8, uint8_t m_maxDuty, bool m_running) : m_pin(pin), m_freqeuncy(frequency), m_resolution(resolution), m_maxDuty((1 << resolution) - 1), m_running(false);

bool PumpDriver::begin()
{
    pinMode(m_pin, OUTPUT);

    bool success = ledcAttachChannel(m_pin, m_frequency, m_resolution, 0);

    this->stop();

    return success;
}

void PumpDriver::start()
{
    m_running = true;
}

void PumpDriver::stop()
{
    m_running = false;
    ledcWrite(m_pin, 0);
}

void PumpDriver::setSpeed(float pct)
{
    pct = constrain(float, 0.0f, 100.0f);

    if (!isRunning() || pct == 0)
    {
        ledcWrite(m_pin, 0);
        return;
    }

    uint8_t duty = (pct / 100.0f) * m_dutyCycle;
    ledcWrite(m_pin, duty);
}

bool PumpDriver::isRunning()
{
    return m_running;
}

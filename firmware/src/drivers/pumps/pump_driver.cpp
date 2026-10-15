/**
 * @file        pump_driver.cpp
 * @brief       Class implementation for DC pump driver supporting PWM.
 * @author      Jeevan Sanchez
 * @date        2026-09-07
 *
 * HOMECTRL
 */

#include "pump_driver.hpp"

PumpDriver::PumpDriver(uint8_t pin, uint32_t frequency, uint8_t resolution, uint8_t channel) : m_pin(pin), m_frequency(frequency), m_resolution(resolution), m_channel(channel), m_maxDuty((1UL << resolution) - 1), m_running(false) {}

bool PumpDriver::begin()
{
    pinMode(m_pin, OUTPUT);

    bool success = ledcAttachChannel(m_pin, m_frequency, m_resolution, m_channel);

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
    pct = constrain(pct, 0.0f, 100.0f);

    if (!isRunning() || pct == 0)
    {
        ledcWrite(m_pin, 0);
        return;
    }

    uint32_t duty = (pct / 100.0f) * m_maxDuty;
    ledcWrite(m_pin, duty);
}

bool PumpDriver::isRunning()
{
    return m_running;
}

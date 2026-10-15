/**
 * @file        IrrigationManager.cpp
 * @brief       Irrigation orchestration implementation. 
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#include "IrrigationManager.hpp"

void IrrigationManager::begin() {
    m_enabled  = false; 
    m_state = IrrigationState::IDLE; 

    m_output = {};
}

void IrrigationManager::enable() {
    m_enabled = true; 
    m_state = IrrigationState::READY; 
}

void IrrigationManager::disable() {
    m_enabled = false; 
    m_output = {};
    m_state = IrrigationState::IDLE; 
}

void IrrigationManager::update(float moisture0, float moisture1) {
    if (!m_enabled) {
        m_output = {};
        m_state = IrrigationState::IDLE; 

        return;
    }

    m_output.pump0On = irrigate(moisture0, m_output.pump0On); 
    m_output.pump1On = irrigate(moisture1, m_output.pump1On);

    m_state = (m_output.pump0On || m_output.pump1On) ? IrrigationState::ACTIVE : IrrigationState::READY;
    return;
}

bool IrrigationManager::irrigate(float moisture, bool irrigating) {
    if (moisture < 0.0f || moisture > 100.0f) return false; 

    if (irrigating) {
        return moisture < WET_THRESHOLD; 
    }

    return moisture <= DRY_THRESHOLD; 
}

IrrigationOutput IrrigationManager::getOutput() {
    return m_output; 
}

IrrigationState IrrigationManager::getState() {
    return m_state; 
}
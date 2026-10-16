/**
 * @file        ShadingManager.cpp
 * @brief       Shading orchestration implementation. 
 * @author      Jeevan Sanchez
 * @date        2026-10-15
 *
 * HOMECTRL
 */

#include "ShadingManager.hpp"

void ShadingManager::begin() {
    m_enabled = false;
    m_targetPos = 0;
    m_state = ShadingState::IDLE;
    m_output = {};
}

void ShadingManager::disable() {
    m_enabled = false;
    m_output = {};
    m_state = ShadingState::IDLE; 
}

void ShadingManager::enable() {
    m_enabled = true;
    m_state = ShadingState::READY;
}

void ShadingManager::update(int currPos) {
    if (!m_enabled) {
        m_state = ShadingState::IDLE; 
        return;
    }

    m_state = (currPos == m_targetPos) ? ShadingState::AT_POSITION : ShadingState::MOVING;
}

void ShadingManager::setPos(int pos) {
    if (!m_enabled) return;
    if (pos < MIN_STEP_POSITION || pos > MAX_STEP_POSITION) return;

    m_targetPos = pos; 
    m_output.pos = pos; 
    m_state = ShadingState::MOVING;
}

ShadingState ShadingManager::getState() const {
    return m_state; 
}

ShadingOutput ShadingManager::getOutput() const {
    return m_output;
}
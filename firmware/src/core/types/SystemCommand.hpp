/**
 * @file        SystemCommand.hpp
 * @brief       Global command definitions. 
 * @author      Jeevan Sanchez
 * @date        2026-10-13
 *
 * HOMECTRL
 */

#pragma once

enum class CommandType {
    WIFI_CONNECT,
    START_IRRIGATION,
    STOP_IRRIGATION,
    SET_SHADING_POS,
    START_SHADING,
    STOP_SHADING
}; 

struct Command {
    CommandType type;
    int value;
};
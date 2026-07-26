/**
 * @file        Data.hpp
 * @brief       Controller peripheral data object definition.
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

 enum struct ActuatorState
{
    IDLE,
    ENERGIZING,
    RUNNING,
    FAULT
};

enum struct DashboardCommands {
    IRRIGATE_1 = 0,
    IRRIGATE_2 = 1, 
    SHADE_DEFAULT = 2, 
    SHADE_PCT = 3
};


struct PumpData
{
    ActuatorState state;
    int enable;
};

struct StepMtrData
{
    ActuatorState state;
    int enable; 
    int shadePct; 
};

struct SMSData
{
    int32_t raw;
    float moisture;
    bool hydrated;
};

// struct ALSData {
//     ///
// };

struct FSWData
{
    boolean empty;
};


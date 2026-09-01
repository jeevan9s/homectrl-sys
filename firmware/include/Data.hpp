/**
 * @file        Data.hpp
 * @brief       Controller peripheral data object definition.
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

<<<<<<< HEAD
enum struct ActuatorState
=======
 enum struct ActuatorState
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
{
    IDLE,
    ENERGIZING,
    RUNNING,
    FAULT
};

<<<<<<< HEAD
=======
enum struct DashboardCommands {
    IRRIGATE_1 = 0,
    IRRIGATE_2 = 1, 
    SHADE_DEFAULT = 2, 
    SHADE_PCT = 3
};


>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325
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

<<<<<<< HEAD
enum struct DashboardCommands {
    IRRIGATE_1 = 0,
    IRRIGATE_2 = 1, 
    SHADE_DEFAULT = 2, 
    SHADE_PCT = 3
};
=======
>>>>>>> 4e62521e1b9c8ca0ba54fcbd538116f5ab588325

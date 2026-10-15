/**
 * @file        sms_calibrate.hpp
 * @brief       Standalone soil moisture sensor calibration routine.
 *
 * HOMECTRL
 */

#pragma once

// Interactive serial routine: prompts for dry and wet readings of each sensor and
// prints them. Copy the printed values into DRY_THRESHOLD / WET_THRESHOLD (Constants.hpp).
void run_sms_calibration();

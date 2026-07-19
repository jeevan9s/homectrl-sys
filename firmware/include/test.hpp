/**
 * @file        test.hpp
 * @brief       Header for hardware validation
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "pinouts.hpp"
#include "config.hpp"

#define NUM_LEDS 1

void run_test_bench(); 
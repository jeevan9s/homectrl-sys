/**
 * @file        pinouts.hpp
 * @brief       Board pinout definitions
 * @author      Jeevan Sanchez
 * @date        2026-07-18
 *
 * HOMECTRL
 */

#pragma once

#include <cstdint>

namespace Pins
{
    namespace Power
    {
        constexpr uint8_t VSMS_EN = 2;
        constexpr uint8_t VPMP_SENSE = 4;
        constexpr uint8_t VPMP_EN = 16;
    }

    namespace Actuators
    {
        constexpr uint8_t PUMP2_EN = 7;
        constexpr uint8_t PUMP1_EN = 15;
        constexpr uint8_t TMC_DIAG = 9;
        constexpr uint8_t TMC_ENN = 10;
        constexpr uint8_t TMC_STEP = 17;
        constexpr uint8_t TMC_DIR = 18;

        namespace Data
        {
            constexpr uint8_t SMS1_ADATA = 5;
            constexpr uint8_t SMS2_ADATA = 6;
            constexpr uint8_t FSW1_SIG = 41;
            constexpr uint8_t FSW2_SIG = 42;
        }

        namespace Indicators
        {
            constexpr uint8_t RGB_LED = 11;
            constexpr uint8_t WIFI_LED = 12;
            constexpr uint8_t DBG_LED = 13;
            constexpr uint8_t BUZZ_EN = 47;

        }

    }

    constexpr uint8_t S3_TXD = 3;

    constexpr uint8_t S3_RXD = 8;

    constexpr uint8_t I2C_SCL = 14;

    constexpr uint8_t I2C_SDA = 21;

}
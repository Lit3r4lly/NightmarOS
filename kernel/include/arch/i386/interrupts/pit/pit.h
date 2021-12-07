/**
* @file pit.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 07/12/2021
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>
#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <kernel/ports/ports.h>
//#include <arch/i386/interrupts/pit/timer.h>

namespace PIT {
    constexpr uint8_t kTimerFreq = 1193180 / 10000;
    constexpr uint16_t kPITChannel0 = 0x40;
    constexpr uint16_t kPITChannel3 = 0x43;
    constexpr uint8_t kPITInitCommand = 0x36;

    void Initialize(); //function to init the pit
    void SetPITCount(uint8_t freq); //function to set the pit frequency
}
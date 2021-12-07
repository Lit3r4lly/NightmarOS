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
#include <arch/i386/interrupts/pit/timer.h>

namespace PIT {

    constexpr uint8_t kChannel0 = 0x40;
    constexpr uint8_t kCommandChannel = 0x43;
    constexpr uint8_t kPITInitCmd = 0x36;
    constexpr uint8_t kClockFrequency = 1193180 / 10000; //about 10ms

    void SetPITCount(uint8_t count);
    void Initialize();

}

/**
* @file timer.h
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
#include <arch/i386/interrupts/isr/isr.h>

namespace Timer {
    extern uint64_t counter;
    void Initialize();
    void Sleep(uint64_t time);
    void IncCounter(uint8_t, ISR::StackState);

}
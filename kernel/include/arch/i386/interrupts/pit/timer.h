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
#include <arch/i386/interrupts/pit/pit.h>

namespace Timer {
    extern uint64_t counter;

    void Initialize();
    void IncCounter(uint8_t irq_num, ISR::StackState stack_state);
    void Sleep(uint64_t amount);
}
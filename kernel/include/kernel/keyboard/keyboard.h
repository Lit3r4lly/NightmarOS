/**
* @file keyboard.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 1/13/22
* @copyright Copyright (c) 2022
*/

#pragma once

#include <libc/stdio.h>
#include <kernel/common/kdefines.h>
#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <kernel/ports/ports.h>
#include <arch/i386/interrupts/isr/isr.h>

namespace Keyboard {
    struct InputKeyType {
        uint32_t character;
        bool is_error = false;
    };

    using KeyboardCallback = InputKeyType (*)(void*);

    void Initialize(KeyboardCallback source_callback);
    void KeyboardHandler(uint8_t int_num, ISR::StackState stack_state);
};
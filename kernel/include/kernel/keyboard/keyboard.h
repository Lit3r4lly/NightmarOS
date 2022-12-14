/**
* @file keyboard.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 1/13/22
* @copyright Copyright (c) 2022
*/

#pragma once

#include <libc/stdio.h>
#include <libc/string.h>
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

    struct Buffer{
        uint8_t kinputBuffer[kSize1kb] = {};
        uint32_t pos;
        uint32_t readPos;
        bool readMode;

        void insert(InputKeyType key) {
            if (this->pos >= kSize1kb)
                this->pos = 0;
            this->kinputBuffer[this->pos] = key.character;
            this->pos++;
        }
    };

    extern Buffer input;

    using KeyboardCallback = InputKeyType (*)(void*);

    void Initialize(KeyboardCallback source_callback); // Initialize the keyboard usage (driver specification etc.)
    void KeyboardHandler(uint8_t int_num, ISR::StackState stack_state); // Keyboard interrupt handler (ISR)
    void readS(void* p, size_t size); //red with size
    void read(void* p); //red till /n
};
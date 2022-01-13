/**
* @file ps2_keyboard.h
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
#include <kernel/keyboard/keyboard.h>

namespace PS2Keyboard {
    constexpr uint32_t kDataPort = 0x60;

    enum class KeyStatus {
        kPressed,
        kReleased
    };

    enum class SpecialCharacterType {
        kNormal,
        kEscape,
        kBackspace,
        kTab,
        kEnter,
        kLeftControl,
        kLeftShift,
        kRightShift,
        kLeftAlt,
        kCapsLock,
        kFKey
    };

    struct KeyDescriptor {
        uint8_t value;
        const char* explanation;
        KeyStatus status;
        SpecialCharacterType special_type = SpecialCharacterType::kNormal;
    };

    Keyboard::InputKeyType KeyboardSource(void* args);
};
/**
* @file interrupts.h
* @author Ori Feldman
* @brief declare interrupts control
* @date 9/6/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <arch/i386/interrupts/idt/idt.h>
#include <arch/i386/interrupts/isr/isr.h>

namespace Interrupts {
    void Initialize();
};
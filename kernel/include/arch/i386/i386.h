/**
* @file arch.h
* @author Ori Feldman
* @brief this file handles important and common i386 structures, functions and so on
* @date 9/3/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>

namespace I386 {
    // Stack state structure for ISRs (built as FIFO)
    struct StackState {
        u32int error_code : 32;
        u32int eip : 32;
        u32int cs : 32;
        u32int eflags : 32;
    } PACKED;
    using StackState = struct StackState;

    // Cpu state before ISR is occurred
    struct CpuState {
        u32int eax : 32;
        u32int ecx : 32;
        u32int edx : 32;
        u32int ebx : 32;
        u32int esp : 32;
        u32int ebp : 32;
        u32int esi : 32;
        u32int edi : 32;
    } PACKED;
};
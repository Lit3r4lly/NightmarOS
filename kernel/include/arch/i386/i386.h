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
    /*
     * stack state structure for ISRs (built as FIFO)
    */
    struct StackState {
        u32int interrupt_number : 32; // pushed manually interrupt number
        u32int error_code : 32; // interrupts 8, 10, 11, 12, 13, 14, 17 are error-code interrupts
        u32int eip : 32; // pushed eip value before interrupt occur
        u32int cs : 32; // pushed cs selector value before interrupt occur
        u32int eflags : 32; // pushed eflags value before interrupt occur
    } PACKED;
    using StackState = struct StackState;

    /*
     * cpu state before ISR is occurred.
     * contains all the registers values before the interrupt occur
    */
    struct CPUState {
        // manually pushed data segment selector
        u16int ds : 16;

        // pushad registers
        u32int edi : 32;
        u32int esi : 32;
        u32int ebp : 32;
        u32int esp : 32;
        u32int ebx : 32;
        u32int edx : 32;
        u32int ecx : 32;
        u32int eax : 32;
    } PACKED;
    using CPUState = struct CPUState;
};
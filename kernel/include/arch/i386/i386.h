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
    struct SegmentRegisters {
        u16int cs;
        u16int ss;
        u16int ds;
        u16int es;
        u16int fs;
        u16int gs;
    } PACKED

    struct Registers {
        u32int edi;
        u32int esi;
        u32int ebp;
        u32int esp;
        u32int ebx;
        u32int edx;
        u32int ecx;
        u32int eax;
    };
};
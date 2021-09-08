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
    } PACKED;

    struct Registers {
        u32int edi;
        u32int esi;
        u32int ebp;
        u32int esp;
        u32int ebx;
        u32int edx;
        u32int ecx;
        u32int eax;
    } PACKED;

    struct ControlRegisters {
        static u32int GetCr0() {
            u32int cr0;
            asm volatile ("mov %%cr0, %0" : "=r"(cr0));
            return cr0;
        }

        static u32int GetCr2() {
            u32int cr2;
            asm volatile ("mov %%cr2, %0" : "=r"(cr2));
            return cr2;
        }

        static u32int GetCr3() {
            u32int cr3;
            asm volatile ("mov %%cr3, %0" : "=r"(cr3));
            return cr3;
        }
    };
};
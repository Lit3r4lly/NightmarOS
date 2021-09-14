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
        uint16_t cs;
        uint16_t ss;
        uint16_t ds;
        uint16_t es;
        uint16_t fs;
        uint16_t gs;
    } PACKED;

    struct Registers {
        uint32_t edi;
        uint32_t esi;
        uint32_t ebp;
        uint32_t esp;
        uint32_t ebx;
        uint32_t edx;
        uint32_t ecx;
        uint32_t eax;
    } PACKED;

    struct ControlRegisters {
        static uint32_t GetCr0() {
            uint32_t cr0;
            asm volatile ("mov %%cr0, %0" : "=r"(cr0));
            return cr0;
        }

        static uint32_t GetCr2() {
            uint32_t cr2;
            asm volatile ("mov %%cr2, %0" : "=r"(cr2));
            return cr2;
        }

        static uint32_t GetCr3() {
            uint32_t cr3;
            asm volatile ("mov %%cr3, %0" : "=r"(cr3));
            return cr3;
        }
    };
};
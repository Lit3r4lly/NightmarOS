/**
* @file idt.h
* @author Ori Feldman
* @brief this file declare the IDT handling operations
* @date 8/28/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>

namespace IDT {
    // IDT pointer struct used for loading the new idt with the LIDT instruction
    struct IDTPointer {
        u16int limit : 16;
        u32int base_address : 32;
    } PACKED;
    using IDTPointer = struct IDTPointer;

    // interrupt descriptor (gate)  struct
    struct IDTDescriptor {
        u16int offset_low : 16;
        u16int segment_selector : 16;
        u8int unused : 8;
        u8int attributes : 8;
        u16int offset_high : 16;
    } PACKED;
    using IDTDescriptor = struct IDTDescriptor;

    void Initialize();
};
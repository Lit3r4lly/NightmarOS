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
    constexpr u32int kNumOfEntries = 256;

    // IDT pointer struct used for loading the new idt with the LIDT instruction
    struct IDTPointer {
        u16int size : 16;
        u32int base_address : 32;
    } PACKED;
    using IDTPointer = struct IDTPointer;

    // interrupt descriptor (gate) struct
    union IDTDescriptor {
        u64int raw;
        struct {
            u16int offset_low : 16;
            u16int segment_selector : 16;
            u8int unused : 8;
            u8int attributes : 8;
            u16int offset_high : 16;
        } PACKED;
    };

    void Initialize();
    void InsertDescriptor(u32int index, u32int offset, u16int segment_selector, u8int attributes);
};

/* -- Function imported from idt_flush.s assembly file -- */
ASM_SCOPE void idt_flush(IDT::IDTPointer* idt_ptr); // flush the IDT table and insert new address into the idtr register
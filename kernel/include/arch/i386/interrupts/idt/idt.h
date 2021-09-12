/**
* @file idt.h
* @author Ori Feldman
* @brief this file declare the IDT handling operations
* @date 8/28/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>
#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <arch/i386/interrupts/idt/descriptor_structure.h>

/* List of intel exceptions can be found at isr.h */

namespace IDT {
    // IDT offsets for PIC interrupts
    constexpr u8int kPICMasterOffset = 0x20;
    constexpr u8int kPICSlaveOffset = 0x28;

    constexpr u32int kNumOfEntries = 256;
    constexpr u16int kKernelCodeSelector = 0x8;

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
    void SetupInterrupts();
};

/* -- Function imported from idt_flush.s assembly file -- */
ASM_SCOPE void idt_flush(IDT::IDTPointer* idt_ptr); // flush the IDT table and insert new address into the idtr register

/* -- Function imported from isr/isr.s assembly file -- */
// these are all the macros for the first 32 isrs
ASM_SCOPE void isr_0(), isr_1(), isr_2(), isr_3(),
                isr_4(), isr_5(), isr_6(), isr_7(),
                isr_8(), isr_9(), isr_10(), isr_11(),
                isr_12(), isr_13(), isr_14(), isr_15(),
                isr_16(), isr_17(), isr_18(), isr_19(),
                isr_20(), isr_21(), isr_22(), isr_23(),
                isr_24(), isr_25(), isr_26(), isr_27(),
                isr_28(), isr_29(), isr_30(), isr_31();

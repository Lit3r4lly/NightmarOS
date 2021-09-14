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
    constexpr uint8_t kPICMasterOffset = 0x20;
    constexpr uint8_t kPICSlaveOffset = 0x28;

    constexpr uint32_t kNumOfEntries = 256;
    constexpr uint16_t kKernelCodeSelector = 0x8;

    // IDT pointer struct used for loading the new idt with the LIDT instruction
    struct IDTPointer {
        uint16_t size : 16;
        uint32_t base_address : 32;
    } PACKED;
    using IDTPointer = struct IDTPointer;

    // interrupt descriptor (gate) struct
    union IDTDescriptor {
        uint64_t raw;
        struct {
            uint16_t offset_low : 16;
            uint16_t segment_selector : 16;
            uint8_t unused : 8;
            uint8_t attributes : 8;
            uint16_t offset_high : 16;
        } PACKED;
    };

    void Initialize(); // initializes the IDT with new interrupts descriptors
    void FlushTable(); // flushing the idtr register with the new idt base address and table size
    void InsertDescriptor(uint32_t index, uint32_t offset, uint16_t segment_selector, uint8_t attributes); // insert new interrupt descriptor by the required fields - see the full structure in the end of descriptor_structure.h
    void SetupInterrupts(); // inserting to the idt the first 32 interrupts
};

/* -- Function imported from isr/isr_stubs.s assembly file -- */
// these are all the macros for the first 32 isrs
ASM_SCOPE void isr_0(), isr_1(), isr_2(), isr_3(),
                isr_4(), isr_5(), isr_6(), isr_7(),
                isr_8(), isr_9(), isr_10(), isr_11(),
                isr_12(), isr_13(), isr_14(), isr_15(),
                isr_16(), isr_17(), isr_18(), isr_19(),
                isr_20(), isr_21(), isr_22(), isr_23(),
                isr_24(), isr_25(), isr_26(), isr_27(),
                isr_28(), isr_29(), isr_30(), isr_31();

// these are all the 16 irq stubs
ASM_SCOPE void irq_0(), irq_1(), irq_2(), irq_3(),
                irq_4(), irq_5(), irq_6(), irq_7(),
                irq_8(), irq_9(), irq_10(), irq_11(),
                irq_12(), irq_13(), irq_14(), irq_15();

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
ASM_SCOPE void isr_0(); ASM_SCOPE void isr_1(); ASM_SCOPE void isr_2(); ASM_SCOPE void isr_3();
ASM_SCOPE void isr_4(); ASM_SCOPE void isr_5(); ASM_SCOPE void isr_6(); ASM_SCOPE void isr_7();
ASM_SCOPE void isr_8(); ASM_SCOPE void isr_9(); ASM_SCOPE void isr_10(); ASM_SCOPE void isr_11();
ASM_SCOPE void isr_12(); ASM_SCOPE void isr_13(); ASM_SCOPE void isr_14(); ASM_SCOPE void isr_15();
ASM_SCOPE void isr_16(); ASM_SCOPE void isr_17(); ASM_SCOPE void isr_18(); ASM_SCOPE void isr_19();
ASM_SCOPE void isr_20(); ASM_SCOPE void isr_21(); ASM_SCOPE void isr_22(); ASM_SCOPE void isr_23();
ASM_SCOPE void isr_24(); ASM_SCOPE void isr_25(); ASM_SCOPE void isr_26(); ASM_SCOPE void isr_27();
ASM_SCOPE void isr_28(); ASM_SCOPE void isr_29(); ASM_SCOPE void isr_30(); ASM_SCOPE void isr_31();

// these are all the 16 irq stubs
ASM_SCOPE void irq_0(); ASM_SCOPE void irq_1(); ASM_SCOPE void irq_2(); ASM_SCOPE void irq_3();
ASM_SCOPE void irq_4(); ASM_SCOPE void irq_5(); ASM_SCOPE void irq_6(); ASM_SCOPE void irq_7();
ASM_SCOPE void irq_8(); ASM_SCOPE void irq_9(); ASM_SCOPE void irq_10(); ASM_SCOPE void irq_11();
ASM_SCOPE void irq_12(); ASM_SCOPE void irq_13(); ASM_SCOPE void irq_14(); ASM_SCOPE void irq_15();

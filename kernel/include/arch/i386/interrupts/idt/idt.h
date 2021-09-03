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
#include <arch/i386/i386.h>
#include <arch/i386/interrupts/idt/descriptor_structure.h>

/**
    -- First 15 exceptions of intel i386 --
    0 	Divide Error
    1 	Debug Exceptions
    2 	[ Intel reserved ]
    3 	Breakpoint
    4 	Overflow
    5 	Bounds Check
    6 	Invalid Opcode
    7 	Coprocessor Not Available
    8 	Double Fault
    9 	Coprocessor Segment Overrun
    10 	Invalid TSS
    11 	Segment Not Present
    12 	Stack Exception
    13 	General Protection Exception(Triple Fault)
    14 	Page Fault
    15 	[ Intel reserved ]
    16 	Coprocessor Error
 */

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
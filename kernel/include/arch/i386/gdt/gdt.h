/**
* @file gdt.h
* @author Ori Feldman
* @brief declare GDT usable structures and functions
* @date 8/22/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>
#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <libc/stdio.h>
#include <arch/i386/gdt/descriptor_structure.h>

namespace GDT {
    // setup an memory flat model (32 bit registers can address all the address range)
    constexpr uint kNumOfEntries = 5;
    constexpr u32int kLimit = 0xFFFFFFFF;
    constexpr u32int kBaseAddress = 0x0;

    // set 0x0C byte for the granularity_flags (see intel's manual for more details)
    constexpr u8int kGranularityFlags = GDT::DescriptorFLags::kNonAvlBit |
                                        GDT::DescriptorFLags::kNonLBit |
                                        GDT::DescriptorFLags::k32Bit |
                                        GDT::DescriptorFLags::kPagesBit;

    struct GDTPointer {
        u16int size : 16;
        u32int base_address : 32;
    } PACKED;
    using GDTPointer = struct GDTPointer;

    /* See in the end of the document, the SegmentDescriptor structure by the intel's manual */
    // Each segment descriptor is 8-byte length
    struct SegmentDescriptor {
        u16int limit_low : 16;
        u16int base_low : 16;
        u8int base_middle : 8;
        u8int access_byte : 8;
        u8int limit_high : 4;
        u8int granularity_flags : 4;
        u8int base_high : 8;
    } PACKED;
    using SegmentDescriptor = struct SegmentDescriptor;

    void Initialize(); // initialize the GDT, by creating kNumOfEntries segment descriptors
    void InsertDescriptor(u32int index, u32int base_address, u32int limit, u8int access, u8int granularity_flags); // creates segment descriptor for inserting into the table
};

/* -- Function imported from gdt_flush.s assembly file -- */
ASM_SCOPE void gdt_flush(GDT::GDTPointer* gdt_ptr); // flush the GDT table and insert new address into the gdtr register

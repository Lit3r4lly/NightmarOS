//
// Created by ori on 8/22/21.
//

#pragma once

#include <arch/i386/tty/tty.h>
#include <kernel/kdefines.h>
#include <arch/i386/gdt/descriptor_structure.h>

namespace GDT {
    // setup an memory flat model (32 bit registers can address all the address range)
    constexpr uint kNumOfEntries = 5; // number of segment entries (descriptors)
    constexpr u32int kLimit = 0xFFFFFFFF; // every segment limit
    constexpr u32int kBaseAddress = 0x0; // every segment base address

    // set 0x0C byte for the granularity_flags (see intel's manual for more details)
    constexpr u8int kGranularityFlags = GDT::DescriptorFLags::kNonAvlBit |
                                        GDT::DescriptorFLags::kNonLBit |
                                        GDT::DescriptorFLags::k32Bit |
                                        GDT::DescriptorFLags::kPagesBit;

    struct GDTPointer {
        u16int limit : 16; // the size of the table - 1
        u32int base_address : 32; // the base address of the GDT, in other words - the first descriptor of the array
    } PACKED; // packed - compiler should keep the types and not align them
    using GDTPointer = struct GDTPointer;

    /* See in the end of the document, the SegmentDescriptor structure by the intel's manual */
    // Each segment descriptor is 8-byte length
    struct SegmentDescriptor {
        u16int limit_low : 16; // the lowest 2 bytes of the limit
        u16int base_low : 16; // the lowest 2 bytes of the base address
        u8int base_middle : 8; // the byte in the middle of the base address
        u8int access_byte : 8; // the access byte includes some information
        u8int limit_high : 4; // the highest 4 bits of the limit
        u8int granularity_flags : 4; // 4 bits of some granularity_flags
        u8int base_high : 8; // the highest byte of the base address
    } PACKED; // packed - compiler should keep the types and not align them
    using SegmentDescriptor = struct SegmentDescriptor;

    void Initialize(); // initialize the GDT, by creating kNumOfEntries segment descriptors
    void InsertDescriptor(u32int index, u32int base_address, u32int limit, u8int access, u8int granularity_flags); // creates segment descriptor for inserting into the table
};

/* -- Function imported from gdt_flush.s assembly file -- */
ASM_SCOPE void gdt_flush(GDT::GDTPointer* gdt_ptr); // flush the GDT table and insert new address into the gdtr register

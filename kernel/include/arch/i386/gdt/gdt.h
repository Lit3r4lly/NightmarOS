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
    constexpr unsigned int kNumOfEntries = 5;
    constexpr uint32_t kLimit = 0xFFFFFFFF;
    constexpr uint32_t kBaseAddress = 0x0;

    // set 0x0C byte for the granularity_flags (see intel's manual for more details)
    constexpr uint8_t kGranularityFlags = GDT::DescriptorFLags::kNonAvlBit |
                                          GDT::DescriptorFLags::kNonLBit |
                                          GDT::DescriptorFLags::k32Bit |
                                          GDT::DescriptorFLags::kPagesBit;

    struct GDTPointer {
        uint16_t size : 16;
        uint32_t base_address : 32;
    } PACKED;
    using GDTPointer = struct GDTPointer;

    /* See in the end of the document, the SegmentDescriptor structure by the intel's manual */
    // Each segment descriptor is 8-byte length
    struct SegmentDescriptor {
        uint16_t limit_low : 16;
        uint16_t base_low : 16;
        uint8_t base_middle : 8;
        uint8_t access_byte : 8;
        uint8_t limit_high : 4;
        uint8_t granularity_flags : 4;
        uint8_t base_high : 8;
    } PACKED;
    using SegmentDescriptor = struct SegmentDescriptor;

    void Initialize(); // initialize the GDT, by creating kNumOfEntries segment descriptors
    void InsertDescriptor(uint32_t index, uint32_t base_address, uint32_t limit, uint8_t access, uint8_t granularity_flags); // creates segment descriptor for inserting into the table
};

/* -- Function imported from gdt_flush.s assembly file -- */
ASM_SCOPE void gdt_flush(GDT::GDTPointer* gdt_ptr); // flush the GDT table and insert new address into the gdtr register

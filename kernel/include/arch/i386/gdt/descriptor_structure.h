/**
* @file descriptor_structure.h
* @author Ori Feldman
* @brief declare descriptors access bytes and flags
* @date 8/22/21
* @copyright Copyright (c) 2021
*/

#pragma once

/*
            ############## SegmentDescriptor struct ##############
                           (by the Intel's manual)
    ╔═════════════════╪═╤═╤═╤═╤═════════╪═╤═════╤═╤═══════╪═════════════════╗
    ║                 │ │ │ │A│         │ │     │ │       │                 ║
    ║   BASE 31..24   │G│X│O│V│ LIMIT   │P│ DPL │0│ TYPE  │ BASE 23..16     ║ 4
    ║                 │ │ │ │L│ 19..16  │ │     │ │       │                 ║
    ╟─────────────────┴─┴─┴─┴─┴─────────┼─┴─────┴─┴───────┴─────────────────╢
    ║                                   │                                   ║
    ║       SEGMENT BASE 15..0          │      SEGMENT LIMIT 15..0          ║ 0
    ║                                   │                                   ║
    ╚═════════════════╪═════════════════╪═════════════════╪═════════════════╝
 */


namespace GDT {
    enum DescriptorFLags : u32int {
        /* ------------------------- Access byte ------------------------- */

        // Ac bit
        kAcBit = 0, // access bit, should be set to 0 - the CPU would change it when the segment is accessed

        // Rw bit
        // code segment:
        kNonRcBit = 0 << 1, // read bit for code segment - only execute (cleared)
        kRcBit = 1 << 1, // read bit for code segment - execute & read (set)
        // data segment:
        kNonWdBit = 0 << 1, // write bit for data segment - only read (cleared)
        kWdBit = 1 << 1, // write bit for data segment - write & read (set)

        // Dc bit
        // code segment:
        kNonCBit = 0 << 2, // conforming bit for code segment - cleared
        kCBit = 1 << 2, // conforming bit for code segment - set
        // data segment:
        kNonDBit = 0 << 2, // direction bit for data segment - cleared
        kDBit = 1 << 2, // direction bit for data segment - set

        // Ex bit
        kExBit = 1 << 3, // if 1, segment is executable (code segment)
        kNonExBit = 0 << 3, // if 0, segment is non-executable (data segment)

        // S (descriptor type) bit
        kCodeBit = 1 << 4, // if 1, the segment is code or data segment
        kDataBit = 1 << 4, // ^^
        kSystemBit = 0 << 4, // if 0, the segment is system segment (eg .a TSS...)

        // Dpl bit (bits 5-6)
        kUserBit = 3 << 5, // if 3, dpl set to ring3
        kKernelBit = 0 << 5, // if 0, dpl set to ring0

        // Pr bit
        kPrBit = 1 << 7, // present bit - should be set for all the valid selector
        kNonPrBit = 0 << 7, // present bit - should be clear for all the invalid selector


        /* ------------------------- Granularity Flags ------------------------- */
        kNonAvlBit = 0, // available bit - not available for use by system
        kAvlBit = 1, // available bit - available for use by system

        kNonLBit = 0 << 1, // not 64 bit segment
        kLBit = 1 << 1, // set only for 64-bit segments

        k16Bit = 0 << 2, // operation in 16 bits
        k32Bit = 1 << 2, // operation in 32 bits

        kBytesBit = 0 << 3, // granularity bit - increment in bytes
        kPagesBit = 1 << 3 // granularity bit - increment in pages
    };

    enum class SegmentAccessType : u8int {
        // Null-segment access byte
        kNull = 0x0,

        // Kernel-code access byte
        kKernelCode = GDT::DescriptorFLags::kAcBit |
                      GDT::DescriptorFLags::kRcBit |
                      GDT::DescriptorFLags::kNonCBit |
                      GDT::DescriptorFLags::kExBit |
                      GDT::DescriptorFLags::kCodeBit |
                      GDT::DescriptorFLags::kKernelBit |
                      GDT::DescriptorFLags::kPrBit,

        // Kernel-data access byte
        kKernelData = GDT::DescriptorFLags::kAcBit |
                      GDT::DescriptorFLags::kWdBit |
                      GDT::DescriptorFLags::kNonDBit |
                      GDT::DescriptorFLags::kNonExBit |
                      GDT::DescriptorFLags::kDataBit |
                      GDT::DescriptorFLags::kKernelBit |
                      GDT::DescriptorFLags::kPrBit,

        // User-code access byte
        kUserCode = GDT::DescriptorFLags::kAcBit |
                    GDT::DescriptorFLags::kRcBit |
                    GDT::DescriptorFLags::kNonCBit |
                    GDT::DescriptorFLags::kExBit |
                    GDT::DescriptorFLags::kCodeBit |
                    GDT::DescriptorFLags::kUserBit |
                    GDT::DescriptorFLags::kPrBit,

        // User-data access byte 11110010
        kUserData = GDT::DescriptorFLags::kAcBit |
                    GDT::DescriptorFLags::kWdBit |
                    GDT::DescriptorFLags::kNonDBit |
                    GDT::DescriptorFLags::kNonExBit |
                    GDT::DescriptorFLags::kDataBit |
                    GDT::DescriptorFLags::kUserBit |
                    GDT::DescriptorFLags::kPrBit
    };
}
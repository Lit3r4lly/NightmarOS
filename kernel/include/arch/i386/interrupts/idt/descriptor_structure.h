/**
* @file descriptor_structure.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 8/29/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kdefines.h>

/* See descriptors structures at the end of the document - took from the Intel's manual */

namespace IDT {
    enum DescriptorFlags : uint32_t {
        // descriptor type, half-byte
        kTaskType = 0b0101, // 32 bit task gate - 0x5
        k16InterruptType = 0b0110, // 16 bit interrupt gate - 0x6
        k16TrapTYpe = 0b0111, // 16 bit trap gate - 0x7
        k32InterruptType = 0b1110, // 32 bit interrupt gate 0xE
        k32TrapType = 0b1111, // 32 bit trap gate - 0xF

        // storage segment bit
        kTrapStorageSegmentBit = 0 << 4, // clear for traps
        kInterruptStorageSegmentBit = 0 << 4, // clear for interrupts
        kTaskStorageSegmentBit = 1 << 4, // set for tasks

        // DPL bit
        kKernelBit = 0 << 5, // set 0 for ring0
        kUserBit = 3 << 5, // set 3 for ring3

        // P bit
        kPresent = 1 << 7, // set for used interrupts
        kNonPresent = 0 << 7, // clear for unused interrupts
    };

    enum DescriptorAttributes : uint8_t {
        kNonValidTask = IDT::DescriptorFlags::kTaskType |
                        IDT::DescriptorFlags::kTaskStorageSegmentBit |
                        IDT::DescriptorFlags::kKernelBit |
                        IDT::DescriptorFlags::kNonPresent,

        kValidTask = IDT::DescriptorFlags::kTaskType |
                     IDT::DescriptorFlags::kTaskStorageSegmentBit |
                     IDT::DescriptorFlags::kKernelBit |
                     IDT::DescriptorFlags::kPresent,

        kNonValidInterrupt = IDT::DescriptorFlags::k32InterruptType |
                             IDT::DescriptorFlags::kInterruptStorageSegmentBit |
                             IDT::DescriptorFlags::kKernelBit |
                             IDT::DescriptorFlags::kNonPresent,

        kValidInterrupt = IDT::DescriptorFlags::k32InterruptType |
                          IDT::DescriptorFlags::kInterruptStorageSegmentBit |
                          IDT::DescriptorFlags::kKernelBit |
                          IDT::DescriptorFlags::kPresent,

        kNonValidTrap = IDT::DescriptorFlags::k32TrapType |
                        IDT::DescriptorFlags::kTrapStorageSegmentBit |
                        IDT::DescriptorFlags::kKernelBit |
                        IDT::DescriptorFlags::kNonPresent,

        kValidTrap = IDT::DescriptorFlags::k32TrapType |
                     IDT::DescriptorFlags::kTrapStorageSegmentBit |
                     IDT::DescriptorFlags::kKernelBit |
                     IDT::DescriptorFlags::kPresent
    };
};

/*
                                i386 TASK GATE
 31                 23                 15               7                 0
 ╔═════════════════╪═════════════════╪═══╤═══╤═════════╪═════════════════╗
 ║              (NOT USED)           │ P │DPL│0 0 1 0 1│   (NOT USED)    ║4
 ╟───────────────────────────────────┼───┴───┴─────────┴─────────────────╢
 ║              SELECTOR             │              (NOT USED)           ║0
 ╚═════════════════╪═════════════════╪═════════════════╪═════════════════╝
                            i386 INTERRUPT GATE
 31                 23                15                7                 0
 ╔═════════════════╪═════════════════╪═══╤═══╤═════════╪═════╪═══════════╗
 ║          OFFSET 31..16            │ P │DPL│0 1 1 1 0│0 0 0│(NOT USED) ║4
 ╟───────────────────────────────────┼───┴───┴─────────┴─────┴───────────╢
 ║              SELECTOR             │          OFFSET 15..0             ║0
 ╚═════════════════╪═════════════════╪═════════════════╪═════════════════╝
                            i386 TRAP GATE
 31                 23                15                 7                0
 ╔═════════════════╪═════════════════╪═══╤═══╤═════════╪═════╪═══════════╗
 ║          OFFSET 31..16            │ P │DPL│0 1 1 1 1│0 0 0│(NOT USED) ║4
 ╟───────────────────────────────────┼───┴───┴─────────┴─────┴───────────╢
 ║              SELECTOR             │          OFFSET 15..0             ║0
 ╚═════════════════╪═════════════════╪═════════════════╪═════════════════╝
 */
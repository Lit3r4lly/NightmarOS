/**
* @file isr.h
* @author Ori Feldman
* @brief declare common isr handler stuff
* @date 9/3/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kuseful.h>
#include <arch/i386/i386.h>

/**
 * Control flow:
 * 1. interrupt occurs and the CPU searching in the IDT the interrupt n's entry for the isr
 * 2. the cpu calls the isr (assembly macro)
 * 3. the assembly macro calls the common stub after pushing the interrupt number or/and error code (assembly func)
 * 4. the common stub saves current cpu state and calls the common handler (cpp func)
 * 5. the common handler checks if there is custom handler for the interrupt, if exists, call it - if not, print interrupt number, dump register and punic
 */

namespace ISR {
    constexpr u32int kNumOfEntries = 256;
    constexpr u8int kNumOfExceptions = 17;

    struct StackState {
        u32int ds; // saved data segment
        u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushad registers
        u32int int_num, err_code; // interrupt number and error code
        u32int eip, cs, eflags; // all pushed-by-processor
    } PACKED;

    // struct of intel declared exceptions in the sdm (volume 3)
    struct IntelExceptions {
        char* mnemonic;
        char* description;
    };

    typedef void (*Handler)(u8int, StackState); // same as `void Handler(u8int int_num, StackState stack_state);`

    void Initialize(); // initialize interrupts ISRs
    void InsertUniqueHandler(u8int int_num, Handler handler); // install custom handler for interrupt (e.g. page-fault for restoring new page)
    extern "C" void InterruptCommonStub(StackState stack_state); // interrupts common handler - prints the information of the interrupt or call the unique handler
};
/**
* @file isr.h
* @author Ori Feldman
* @brief declare common isr handler stuff
* @date 9/3/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/common/kuseful.h>

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
    typedef void (*Handler)(void*); // declare handler function types (returns void, takes pointer as argument)

    // struct of intel declared exceptions in the sdm (volume 3)
    struct IntelExceptions {
        u32int exception_id;
        char* description;
    };

    void Initialize();
    void InsertUniqueHandler(u8int interrupt_id, Handler handler);
    extern "C" void InterruptCommonStub();
};
/**
* @file memory_management.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 29/12/2021
* @copyright Copyright (c) 2021
*/
#pragma once

#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <arch/i386/i386.h>
#include <arch/i386/paging/paging.h>

/**
 * name space to manage the paging allocation of memory
 */
namespace MemoryManager {

    constexpr uint32_t kNumFrames = SIZE16MB / SIZE64B; //the number of frames
    extern uint32_t* kFrames; // the available frames
    extern Paging::PageDirectory* KernelDir; //the directory of the kernel
    extern uint32_t kBaseAddress; //the current available address

    uint32_t AllocateMemory(uint32_t size, int aligned, uint32_t* physical_address);


}
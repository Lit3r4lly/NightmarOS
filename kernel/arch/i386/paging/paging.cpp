/**
* @file paging.cpp
* @author Ori Feldman
* @brief <insert here file brief>
* @date 12/23/21
* @copyright Copyright (c) 2021
*/

//#include <arch/i386/paging/paging.h>
#include <arch/i386/paging/memory_manager.h>

uint32_t* MemoryManager::kHeap; // the available frames
Paging::PageDirectory* MemoryManager::KernelDir; //the directory of the kernel
uint32_t  MemoryManager::kBaseAddress;

void Paging::Initialize() {

    //allocating heap
    MemoryManager::kHeap = (uint32_t*)MemoryManager::AllocateMemory(MemoryManager::kNumFrames / 32, 1,0);

    //allocating the kernel memory
    MemoryManager::KernelDir = (PageDirectory*)MemoryManager::AllocateMemory(sizeof(PageDirectory),1,0 );

    /*
     * TODO (allocate the frames for the kernel dir)
     * */

    load_page_directory(MemoryManager::KernelDir->physical_addresses);
    enable_paging();
}

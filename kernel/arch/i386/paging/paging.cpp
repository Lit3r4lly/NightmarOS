/**
* @file paging.cpp
* @author Ori Feldman
* @brief <implementation of the paging mechanism>
* @date 12/23/21
* @copyright Copyright (c) 2021
*/

//#include <arch/i386/paging/paging.h>
#include <arch/i386/paging/memory_manager.h>

uint32_t* MemoryManager::kHeap; // the available frames
Paging::PageDirectory* MemoryManager::KernelDir; //the directory of the kernel
uint32_t MemoryManager::kBaseAddress;

void Paging::Initialize() {

    //allocating heap
    MemoryManager::kHeap = (uint32_t*) MemoryManager::AllocateMemory(MemoryManager::kNumFrames / kSize4b, 1, 0);
    memset(MemoryManager::kHeap, 0, MemoryManager::kNumFrames / kSize4b);

    //allocating the kernel memory
    MemoryManager::KernelDir = (PageDirectory*) MemoryManager::AllocateMemory(sizeof(PageDirectory), 1, 0);
    memset(MemoryManager::KernelDir, 0, sizeof(Paging::PageDirectory));

    for (auto i = (uint32_t)Paging::kernelStart; i < (uint32_t)Paging::kernelEnd; i += kSize64b) {
        MemoryManager::AllocatePage(Paging::GetPage(i, 1, MemoryManager::KernelDir), 0, 0);
    }


    ISR::InsertUniqueHandler(0xe, ISR::Handler {Paging::PFHandler,false,false});
    load_page_directory((uint32_t*)&MemoryManager::KernelDir->physical_addresses);
    enable_paging();
}

/***
 * function to get a page
 * @param address - the address of the page
 * @param make - do you want to create a new table in case it is not allocated
 * @param directory - the directory to get the page from
 * @return the wanted page
 */
Paging::Page* Paging::GetPage(uint32_t address, int make, Paging::PageDirectory* directory) {
    address /= kSize64b;
    uint32_t table_index = address / kSize32b;
    if (directory->entries[table_index]) {
        return &directory->entries[table_index]->entries[address % kSize32b];

    } else if(make) {
        MemoryManager::AllocateTable(table_index, directory);
        return &directory->entries[table_index]->entries[address % kSize32b];

    } else {
        return nullptr;
    }
}

void Paging::PFHandler(uint8_t, ISR::StackState) {
    printf("page fault has happened");
}

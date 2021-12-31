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

    //allocating the kernel memory
    MemoryManager::KernelDir = (PageDirectory*) MemoryManager::AllocateMemory(sizeof(PageDirectory), 1, 0);

    //allocating heap
    MemoryManager::kHeap = (uint32_t*) MemoryManager::AllocateMemory(MemoryManager::kNumFrames / 32, 1, 0);


    /*
     * TODO (reset the trash memory of the heap and kernel)
     * */

    for (uint32_t i {}; i < MemoryManager::kBaseAddress; i += SIZE64B) {
        MemoryManager::AllocatePage(Paging::GetPage(i, 1,MemoryManager::KernelDir), 0, 0);
    }

    load_page_directory(MemoryManager::KernelDir->physical_addresses);
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
    address /= SIZE64B;
    uint32_t table_index = address / SIZE32B;
    if (directory->entries[table_index]) {
        return &directory->entries[table_index]->entries[address%SIZE32B];

    } else if(make) {
        MemoryManager::AllocateTable(table_index, directory);
        return &directory->entries[table_index]->entries[address%SIZE32B];

    } else {
        return nullptr;
    }
}
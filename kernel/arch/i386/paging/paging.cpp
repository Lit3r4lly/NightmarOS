/**
* @file paging.cpp
* @author Ori Feldman
* @brief <implementation of the paging mechanism>
* @date 12/23/21
* @copyright Copyright (c) 2021
*/

//#include <arch/i386/paging/paging.h>
#include <arch/i386/paging/memory_manager.h>

uint32_t* MemoryManager::kFrames; // the available frames
Paging::PageDirectory* MemoryManager::KernelDir; //the directory of the kernel
Paging::PageDirectory* MemoryManager::CurrentDir; //the directory of the kernel
uint32_t MemoryManager::kBaseAddress;


void Paging::Initialize() {

    K_LOG("kernel start: %x, kernel end: %x", &Paging::CodeStart, &Paging::CodeEnd);
    //allocating heap
    MemoryManager::kFrames = (uint32_t*) MemoryManager::AllocateMemory(K_FRAME_INDEX(MemoryManager::kNumFrames), 0, 0);
    memset(MemoryManager::kFrames, 0, K_FRAME_INDEX(MemoryManager::kNumFrames));

    //allocating the kernel memory
    MemoryManager::KernelDir = (PageDirectory*) MemoryManager::AllocateMemory(sizeof(PageDirectory), 1, 0);
    memset(MemoryManager::KernelDir, 0, sizeof(Paging::PageDirectory));
    MemoryManager::CurrentDir = MemoryManager::KernelDir;

    printf("starting to map");
    uint32_t i {};
    while ( i < MemoryManager::kBaseAddress) {
        MemoryManager::AllocatePage(Paging::GetPage(i, 1, MemoryManager::KernelDir), 0, 0);
        i += kSize4kb;
    }

    printf("mapped the kernel base\n");
    uint32_t start = reinterpret_cast<uintptr_t>(&Paging::CodeStart);
    uint32_t end = reinterpret_cast<uintptr_t>(&Paging::CodeEnd);

    while (start < end) {
        //MemoryManager::ForceFrame(Paging::GetPage(start, 1, MemoryManager::KernelDir), 0, 0,start);
        MemoryManager::AllocatePage(Paging::GetPage(start, 1, MemoryManager::KernelDir), 0, 0);
        start += kSize4kb;
    }

    printf("mapped the kernel code\n");

    printf("mapping is done\n");
    K_LOG("Mapped the kernel memory");

    ISR::InsertUniqueHandler(0xe, ISR::Handler {Paging::PFHandler,false,false});
    //Paging::SwitchDirectory(MemoryManager::KernelDir);
}

/***
 * function to get a page
 * @param address - the address of the page
 * @param make - do you want to create a new table in case it is not allocated
 * @param directory - the directory to get the page from
 * @return the wanted page
 */
Paging::Page* Paging::GetPage(uint32_t address, int make, Paging::PageDirectory* directory) {
    address /= kSize4kb;
    volatile uint32_t table_index = address / kSize1kb;
    if (directory->entries[table_index]) {
        return &directory->entries[table_index]->entries[address % kSize1kb];

    } else if(make) {
//        MemoryManager::AllocateTable(table_index, directory);
        uint32_t temp_physical_address;
        directory->entries[table_index] = (Paging::PageTable*) MemoryManager::AllocateMemory(sizeof(Paging::PageTable), 1,
                                                                                             &temp_physical_address);
        memset(directory->entries[table_index], 0, kSize4kb);

        directory->physical_table_addresses[table_index] = temp_physical_address | 0x7;
        return &directory->entries[table_index]->entries[address % kSize1kb];

    } else {
        return nullptr;
    }
}


void Paging::SwitchDirectory(Paging::PageDirectory* dir){
    MemoryManager::CurrentDir = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->physical_table_addresses));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}


void Paging::PFHandler(uint8_t, ISR::StackState regs) {

    uint32_t faulting_address = 0;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

    bool present = !(regs.err_code & 0x1);

    if (present){
        uint32_t base_fault = faulting_address & (-0x1000);
        uint32_t top_fault = base_fault + 0x1000;
        uint32_t i = base_fault;
        while (i < top_fault) {
            MemoryManager::AllocatePage(Paging::GetPage(i, 1, MemoryManager::CurrentDir), 0, 0);
            i +=kSize4kb;
        }
    }

}

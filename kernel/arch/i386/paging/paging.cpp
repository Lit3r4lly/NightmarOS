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
uint32_t MemoryManager::kBaseAddress = (uint32_t)&Paging::CodeEnd;
Heap::HeapT* MemoryManager::kHeap;
Heap::HeapT* MemoryManager::Currheap;


void Paging::Initialize() {
    uint32_t start = (uint32_t)&Paging::CodeStart;
    uint32_t end = (uint32_t)&Paging::CodeEnd;
    K_LOG("kernel start: %x, kernel end: %x", start, end);

    //allocating frame data set
    MemoryManager::kFrames = (uint32_t*) MemoryManager::AllocateMemory(K_BIT_INDEX(MemoryManager::kNumFrames), 0, 0);
    memset(MemoryManager::kFrames, 0, K_BIT_INDEX(MemoryManager::kNumFrames));

    //allocating the kernel memory
    MemoryManager::KernelDir = (PageDirectory*) MemoryManager::AllocateMemory(sizeof(PageDirectory), 1, 0);
    memset(MemoryManager::KernelDir, 0, sizeof(Paging::PageDirectory));
    MemoryManager::CurrentDir = MemoryManager::KernelDir;


    for (uint32_t i = Heap::kHeapStart; i < Heap::kHeapStart + Heap::kHeapSize;i += kSize4kb)
        Paging::GetPage(i,1,MemoryManager::KernelDir);


    uint32_t i {};
    while ( i < MemoryManager::kBaseAddress + kSize4kb) {
        MemoryManager::AllocatePage(Paging::GetPage(i, 1, MemoryManager::KernelDir), 0, 0);
        i += kSize4kb;
    }

    i = Heap::kHeapStart;
    while (i < Heap::kHeapStart + Heap::kHeapSize) {
        MemoryManager::AllocatePage(Paging::GetPage(i,1,MemoryManager::KernelDir),0,0);
        i += kSize4kb;
    }

    i = 0xB8000;
    while(i < 0xB800 + 80 * 25 + kSize4kb) {
        MemoryManager::ForceFrame(Paging::GetPage(i, 1, MemoryManager::KernelDir), 0, 0,i);
        i += kSize4kb;
    }

    K_LOG("Mapped the kernel memory");

    ISR::InsertUniqueHandler(0xe, ISR::Handler {Paging::PFHandler,false,true});
    Paging::SwitchDirectory(MemoryManager::KernelDir);
    K_LOG("enabled paging :)")

    MemoryManager::kHeap = Heap::CreateHeap(Heap::kHeapStart, Heap::kHeapStart + Heap::kHeapSize, 0xCFFFF000, 0,0);
    MemoryManager::Currheap = MemoryManager::kHeap;
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
    asm volatile ("cli");
    MemoryManager::CurrentDir = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->physical_table_addresses));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
    asm volatile ("sti");
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

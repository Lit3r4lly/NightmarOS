/**
* @file memory_manager.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 29/12/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/paging/memory_manager.h>

/**
 * function to allocate memory with the given size
 * @param size - the size to allocate
 * @param aligned - is the memory need to be aligned
 * @param physical_address - the physical address of the memory we just allocated
 * @return
 */
uint32_t MemoryManager::AllocateMemory(uint32_t size, int aligned, uint32_t* physical_address) {

    // aligning the address
    if(aligned == 1 && (MemoryManager::kBaseAddress & 0x00000FFF))
    {
        MemoryManager::kBaseAddress &= 0x00000FFF;
        MemoryManager::kBaseAddress += 0x1000;
    }

    if (physical_address)
        *physical_address = MemoryManager::kBaseAddress;

    uint32_t temp_address = MemoryManager::kBaseAddress;
    MemoryManager::kBaseAddress += size;
    return temp_address;
}

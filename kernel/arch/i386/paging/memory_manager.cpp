/**
* @file memory_manager.cpp
* @author Oshri Taub
* @brief <implementation of the memory manager>
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
        MemoryManager::kBaseAddress += SIZE64B;
    }

    if (physical_address)
        *physical_address = MemoryManager::kBaseAddress;

    uint32_t temp_address = MemoryManager::kBaseAddress;
    MemoryManager::kBaseAddress += size;
    return temp_address;
}

/**
 * create a new page table for a given directory
 * @param table_index - the index of the table to create
 * @param directory  - the directory to append
 */
void MemoryManager::AllocateTable(uint32_t table_index, Paging::PageDirectory* directory) {
    uint32_t temp_physical_address;
    directory->entries[table_index] = (Paging::PageTable*) MemoryManager::AllocateMemory(sizeof(Paging::PageTable), 1,
                                                                                         &temp_physical_address);
    //TODO(erase trash memory with memset)

    directory->physical_table_addresses[table_index] = temp_physical_address | 0x07;
}

/***
 * function to set the flags of a frame to announce the frame is in use
 * @param frame_address - the page frame to set its data
 */
void MemoryManager::SetFrameFlags(uint32_t frame_address) {
    uint32_t frame_id = frame_address / SIZE64B;
    MemoryManager::kHeap[frame_id / 4] |= (0x01 << (frame_id % 4));
}


void MemoryManager::AllocatePage(Paging::Page *page, int32_t is_read_write, int32_t is_user) {
    if (page->frame_addr != 0)
        return ;// the page has already allocated


    uint32_t frame_id; //TODO (init with a proper frame from heap
    if (frame_id == (uint32_t)(-1)) {
        return ;//there is no memory left
    }

    MemoryManager::SetFrameFlags(frame_id * SIZE64B);

    page->frame_addr = frame_id;
    page->is_present = 1;
    page->rw = is_read_write;
    page->is_user = is_user;

}

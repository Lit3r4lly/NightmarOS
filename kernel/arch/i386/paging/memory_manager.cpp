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
    if(aligned == 1 && (MemoryManager::kBaseAddress & 0xFFFFF000))
    {
        MemoryManager::kBaseAddress &= 0xFFFFF000;
        MemoryManager::kBaseAddress += kSize4kb;
    }

    if (physical_address)
        *physical_address = MemoryManager::kBaseAddress;

    uint32_t temp_address = MemoryManager::kBaseAddress;
    MemoryManager::kBaseAddress += size;
    return temp_address;
}

/***
 * function to set the flags of a frame to announce the frame is in use
 * @param frame_address - the frame to set its flags
 */
void MemoryManager::SetFrameFlags(uint32_t frame_address) {
    uint32_t frame = frame_address / kSize4kb;
    uint32_t idx = K_BIT_INDEX(frame);
    uint32_t offset = K_BIT_OFFSET(frame);
    MemoryManager::kFrames[idx] |= (0x1 << offset);
}

/***
 * function clear the flags of a frame
 * @param frame_address - the frame to clear its flags
 */
void MemoryManager::ClearFrameFlags(uint32_t frame_address) {
    uint32_t frame = frame_address / kSize4kb;
    uint32_t idx = K_BIT_INDEX(frame);
    uint32_t offset = K_BIT_OFFSET(frame);
    MemoryManager::kFrames[idx] &= ~(0x1 << offset);
}

/***
 * function to check if page flags are already sets
 * @param frame_address - the frame to test
 * @return - is the frame is already taken bool
 */
uint32_t MemoryManager::TestFrameFlags(uint32_t frame_address) {
    uint32_t frame = frame_address / kSize4kb;
    uint32_t idx = K_BIT_INDEX(frame);
    uint32_t offset = K_BIT_OFFSET(frame);
    return (MemoryManager::kFrames[idx] & (0x1 << offset));
}


/***
 * function to allocate a new page
 * @param page - the page to allocate
 * @param is_read_write - can you read and write to page (the opposite is only read)
 * @param is_user - is the page is user or system
 */
void MemoryManager::AllocatePage(Paging::Page *page, int32_t is_user, int32_t is_read_write) {
    if (page->frame_addr != (uint32_t)0)
        return ;// the page has already allocated


    uint32_t frame_id = MemoryManager::GetFreeFrame();
    if (frame_id == (uint32_t)(-1)) {
        return ;//there is no memory left
    }

    MemoryManager::SetFrameFlags(frame_id*kSize4kb);

    page->frame_addr = frame_id;
    page->is_present = 1;
    page->rw = (uint32_t)is_read_write;
    page->is_user = (uint32_t)is_user;

}

/**
 * function to deallocate a page
 * @param page - the page to de allocate
 */
void MemoryManager::DeallocatePage(Paging::Page *page) {
    uint32_t frame = page->frame_addr;
    if(!frame) {
        return; //the page isn't allocated
    }
    MemoryManager::ClearFrameFlags(frame);
    page->frame_addr = 0x0;
}

/***
 * function to get the first free frame in the available frames
 * @return - the first free frame
 */
uint32_t MemoryManager::GetFreeFrame() {
    for (uint32_t i {}; i < K_BIT_INDEX(MemoryManager::kNumFrames); i++) {
        if (MemoryManager::kFrames[i] != 0xFFFFFFFF) {
            for (uint32_t j {}; j < kSize4b; j++) {
                if (!(MemoryManager::kFrames[i] & (0x01 << j)))
                    return i*kSize4b +j;

            }
        }
    }
    return (uint32_t)(-1);
}


void MemoryManager::ForceFrame(Paging::Page* page, int32_t is_user, int32_t is_read_write, uint32_t address) {
    SetFrameFlags(address*kSize4kb);

    page->is_present = 1;
    page->rw = (uint32_t)is_read_write;
    page->is_user = (uint32_t)is_user;
    page->frame_addr = address;
}
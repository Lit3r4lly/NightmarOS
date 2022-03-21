/**
* @file malloc.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 20/03/2022
* @copyright Copyright (c) 2022
*/

#include <libc/stdlib.h>
#include <arch/i386/paging/memory_manager.h>

void* malloc(size_t size) {
    void* p = Heap::alloc(size, 0, MemoryManager::Currheap);
    memset(p, '\0',size);
    return p;
};
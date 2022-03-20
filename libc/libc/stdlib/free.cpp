/**
* @file fee.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 20/03/2022
* @copyright Copyright (c) 2022
*/

#include <libc/stdlib.h>
#include <arch/i386/paging/memory_manager.h>

void free(void* p) {
    Heap::free(p, MemoryManager::Currheap);
}
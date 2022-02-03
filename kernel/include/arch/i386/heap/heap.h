/**
* @file heap.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 31/01/2022
* @copyright Copyright (c) 2022
*/
#pragma once
#include <kernel/common/kuseful.h>
#include <arch/i386/paging/memory_manager.h>
#include <libc/containers.h>

namespace Heap {
    constexpr uint32_t kHeapStart = 0xC0000000;
    constexpr uint32_t kHeadSize = 0x100000;
    constexpr uint32_t kHeapIndexSize = 0x20000;
    constexpr uint32_t kHeapMagic = 0x123890AB;
    constexpr uint32_t kHeapMinSize = 0x70000;



    struct Header {
        uint32_t magic;
        uint8_t is_hole;
        uint32_t size;
    };

    struct Footer {
        uint32_t magic;
        Heap::Header* header;
    };

    struct HeapT {
        OrderedArray::Array index;
        uint32_t start_address;
        uint32_t end_address;
        uint32_t max_address;
        uint8_t supervisor;
        uint8_t readOnly;
    };

    //function to create the heap
    Heap::HeapT* CreateHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervise, uint8_t read_only);

    //function to allocate new memory
    type_t alloc(uint32_t size, uint8_t page_align, Heap::HeapT* heap);

    //function to free the memory allocated with alloc
    void free(type_t p, Heap::HeapT* heap);

    //function to find the smallest available memory address
    uint32_t FindSmallestHole(uint32_t size, uint8_t align, Heap::HeapT* heap);

    //function needed by the ordered array for the heap
    int8_t HeapLessThan(type_t a, type_t b);

    void Expend(uint32_t new_size, Heap::HeapT* heap);
    uint32_t Contract(uint32_t new_size, Heap::HeapT* heap);
};
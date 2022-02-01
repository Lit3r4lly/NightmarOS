/**
* @file heap.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 31/01/2022
* @copyright Copyright (c) 2022
*/
#include <arch/i386/heap/heap.h>

/**
 * function to find the smallest hole to fit new data
 * @param size - the size of the wanted hole
 * @param align - is te memory is page aligned
 * @param heap - the heap to find the hole
 * @return the index of the hole
 */
uint32_t FindSmallestHole(uint32_t size, uint8_t align, Heap::HeapT* heap) {

    uint32_t iter {};
    while (iter < heap->index.size) {
        Heap::Header* header = (Heap::Header*)OrderedArray::Find(iter, &heap->index);

        if (align > 0) {
            uint32_t location = (uint32_t)header;
            int32_t offset = 0;

            if(((location+sizeof (Heap::Header)) & 0xFFFFF000) != 0)
                offset = kSize4kb - (location+sizeof(Heap::Header))%kSize4kb;

            int32_t hole_size = (int32_t)header->size - offset;

            if (hole_size >= (int32_t)size)
                break;

        } else if (header->size >= size)
            break;

        iter++;
    }

    if (iter == heap->index.size) {
        return -1;
    } else {
        return iter;
    }
}

/**
 * function for the heap ordered array
 * @param a
 * @param b
 * @return
 */
int8_t Heap::HeapLessThan(type_t a, type_t b) {
  return (((Heap::Header*)a)->size > ((Heap::Header*)b)->size) ? 1:0;
}

/**
 * function create heap
 * @param start - the start address for the heap
 * @param end - the initial end of the heap
 * @param max - the max address the heap can expand to
 * @param supervise - is it system or user
 * @param read_only - is it read or read and write
 * @return - the new heap
 */
Heap::HeapT* Heap::CreateHeap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervise, uint8_t read_only) {
    Heap::HeapT* heap = (Heap::HeapT*)MemoryManager::AllocateMemory(sizeof (Heap::HeapT),0,0);

    //making sure the addresses are page aligned
    if (start%kSize4kb == 0 || end%kSize4kb == 0)
        return nullptr;

    heap->index = OrderedArray::PlaceOrderedArray((type_t)start, max, Heap::HeapLessThan);

    start += sizeof(type_t)*Heap::kHeapIndexSize;//now we can start putting data

    //page align
    if ((start & 0xFFFFF000) != 0) {
        start &= 0xFFFFF000;
        start += kSize4kb;
    }

    heap->start_address = start;
    heap->end_address = end;
    heap->readOnly = read_only;
    heap->supervisor = supervise;
    heap->max_address = max;

    Heap::Header* hole = (Heap::Header*)start;
    hole->size = end - start;
    hole->magic = Heap::kHeapMagic;
    hole->is_hole = 1;
    OrderedArray::InsertToArray((type_t*)hole, &heap->index);

    return heap;
}


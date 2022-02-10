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
int32_t Heap::FindSmallestHole(uint32_t size, uint8_t align, Heap::HeapT* heap) {

    uint32_t iter {};
    while (iter < heap->index.size) {
        Heap::Header* header = (Heap::Header*)OrderedArray::Find(iter, &heap->index);

        if (align > 0) {
            uint32_t location = (uint32_t)header;
            int32_t offset = 0;

            if((location+sizeof (Heap::Header)) & 0xFFFFF000)
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
    if (!start%kSize4kb || !end%kSize4kb)
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

/***
 * function to expand the heap to a new size
 * @param new_size - the wanted size
 * @param heap  - the heap to expand
 */
void Heap::Expend(uint32_t new_size, Heap::HeapT* heap) {
    if (new_size < heap->end_address - heap->start_address)
        return;

    //page align
    if (new_size & 0xFFFFF000) {
        new_size &=0xFFFFF000;
        new_size+=kSize4kb;
    }

    //check we are not overflowing
    if (heap->start_address + new_size > heap->max_address)
        return;

    uint32_t old_size = heap->end_address - heap->start_address;
    uint32_t i = old_size;

    while (i < new_size) {
        MemoryManager::AllocatePage(Paging::GetPage(heap->start_address + i,1,MemoryManager::CurrentDir),heap->supervisor?1:0,heap->readOnly?1:0);
        i++;
    }

    heap->end_address = heap->start_address+new_size;
}

/**
 * function to reduce the given heap to a new size
 * @param new_size - the target size
 * @param heap - the heap to reduce
 * @return - the new size
 */
uint32_t Heap::Contract(uint32_t new_size, Heap::HeapT* heap) {
    if (new_size > heap->end_address - heap->start_address)
        return heap->end_address - heap->start_address;

    if(new_size & 0xFFFFF000) {
        new_size &= 0xFFFFF000;
        new_size += kSize4kb;
    }

    if (new_size < Heap::kHeapMinSize)
        new_size = Heap::kHeapMinSize;

    uint32_t old_size = heap->end_address - heap->start_address;
    uint32_t i = old_size - kSize4kb;

    while(i > new_size) {
        MemoryManager::DeallocatePage(Paging::GetPage(heap->start_address + i,0,MemoryManager::CurrentDir));
        i -= kSize4kb;
    }

    heap->end_address = heap->start_address + new_size;
    return new_size;
}

/***
 * function to allocate new memory to the heap
 * @param size - the wanted size of the memory
 * @param align - is it needed to be page aligned
 * @param heap - the heap to allocate on
 * @return - the address of the memory
 */
type_t Heap::alloc(uint32_t size, uint8_t align, Heap::HeapT* heap) {

    uint32_t new_size = size + sizeof(Heap::Footer) + sizeof(Heap::Header);
    int32_t iter = Heap::FindSmallestHole(new_size, align, heap);

    if (iter == -1) {

    } else {
        Heap::Header* original_hole_header = (Heap::Header*) OrderedArray::Find(iter, &heap->index);
        uint32_t original_hole_pos = (uint32_t)original_hole_header;
        uint32_t original_hole_size = original_hole_header->size;

        if (original_hole_size - new_size < sizeof(Heap::Footer) + sizeof (Heap::Header)) {
            size += original_hole_size - new_size;
            new_size = original_hole_size;
        }

        if (align && original_hole_pos & 0xFFFFF000) {
            uint32_t new_location = original_hole_pos + kSize4kb;
            Heap::Header* hole_header = (Heap::Header*)new_location;
            hole_header->size = kSize4kb - (original_hole_pos&0xFFF) - sizeof (Heap::Header);
            hole_header->magic = Heap::kHeapMagic;
            hole_header->is_hole = 1;

            Heap::Footer* hole_footer = (Heap::Footer*) ((uint32_t)new_location - sizeof (Heap::Footer));
            hole_footer->magic = Heap::kHeapMagic;
            hole_footer->header = hole_header;
            original_hole_pos = new_location;
            original_hole_size = original_hole_size - hole_header->size;
        } else {
            OrderedArray::Remove(iter, &heap->index);
        }

        Heap::Header* block_header = (Heap::Header*)original_hole_pos;
        block_header->magic = Heap::kHeapMagic;
        block_header->is_hole = 0;
        block_header->size = new_size;

        Heap::Footer* block_footer = (Heap::Footer*)(original_hole_pos + sizeof (Heap::Header) + size);
        block_footer->magic = Heap::kHeapMagic;
        block_footer->header = block_header;

        if(original_hole_size - size > 0) {
            Heap::Header* hole_header = (Heap::Header*)(original_hole_pos + sizeof (Heap::Header) + size +sizeof(Heap::Footer));
            hole_header->magic = Heap::kHeapMagic;
            hole_header->is_hole = 1;
            hole_header->size = original_hole_size - new_size;

            Heap::Footer* hole_footer = (Heap::Footer*)((uint32_t)hole_header + original_hole_size - new_size - sizeof (Heap::Footer));

            if((uint32_t)hole_footer < heap->end_address) {
                hole_footer->magic = Heap::kHeapMagic;
                hole_footer->header = hole_header;
            }

            OrderedArray::InsertToArray((type_t)hole_header, &heap->index);
        }

        return (type_t) ((uint32_t)block_header + sizeof (Heap::Header));
    }

}
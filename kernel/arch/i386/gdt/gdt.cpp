/**
* @file gdt.cpp
* @author Ori Feldman
* @brief defines GDT flushing functions and descriptors
* @date 8/22/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/gdt/gdt.h>

GDT::SegmentDescriptor gdt_entries[GDT::kNumOfEntries] = { 0 }; // initialize an array of the GDT entries
GDT::GDTPointer gdt_ptr = {0, 0 }; // initialize the gdt_ptr struct

/**
 * initializes the GDT, by creating kNumOfEntries descriptors, flush the GDT and insert the new address to the gdtr register
 */
void GDT::Initialize() {
    K_LOG("Initializing GDT");

    // set GDT pointer that need to be sent for flushing
    gdt_ptr.size = (uint16_t)(sizeof(GDT::SegmentDescriptor) * kNumOfEntries) - 1; // set 16 bit limit address of the table
    gdt_ptr.base_address = (uint32_t)gdt_entries; // set 32 bit base address of the GDT
    K_LOG("Created GDT pointer struct");

    // creates 5 new descriptors
    GDT::InsertDescriptor(0, 0, 0, (uint8_t)GDT::SegmentAccessType::kNull, 0); // kNull segment descriptor
    GDT::InsertDescriptor(1, GDT::kBaseAddress, GDT::kLimit, (uint8_t)GDT::SegmentAccessType::kKernelCode, GDT::kGranularityFlags); // Kernel code segment descriptor
    GDT::InsertDescriptor(2, GDT::kBaseAddress, GDT::kLimit, (uint8_t)GDT::SegmentAccessType::kKernelData, GDT::kGranularityFlags); // Kernel data segment descriptor
    GDT::InsertDescriptor(3, GDT::kBaseAddress, GDT::kLimit, (uint8_t)GDT::SegmentAccessType::kUserCode, GDT::kGranularityFlags); // User code segment descriptor
    GDT::InsertDescriptor(4, GDT::kBaseAddress, GDT::kLimit, (uint8_t)GDT::SegmentAccessType::kUserData, GDT::kGranularityFlags); // User data segment descriptor
    K_LOG("Created %d new descriptors", GDT::kNumOfEntries);

    // Flush the GDT and insert into the gdtr register the new GDT base address (asm func)
    gdt_flush(&gdt_ptr);
    K_LOG("Initialized and flushed GDT");
}

/**
 * insert new segment descriptor by the required fields - see the full structure in the end of the header file
 * @param index - the index of the current entry
 * @param base_address - the base address of the segment
 * @param limit - the maximum addressable unit in the descriptor
 * @param access - access byte of the descriptor
 * @param granularity_flags - granularity flags (4 bits)
 */
void GDT::InsertDescriptor(uint32_t index, uint32_t base_address, uint32_t limit, uint8_t access, uint8_t granularity_flags) {
    if (index >= kNumOfEntries)
        K_PANIC("index of descriptor is overflowed");

    K_LOG("Created segment [%d] - base address: %x, limit: %x", index, base_address, limit);

    // manipulate the base_address variable into the struct
    gdt_entries[index].base_low = (base_address & 0xFFFF); // pull only the 2 lowest bytes of the base address
    gdt_entries[index].base_middle = ((base_address >> 16) & 0xFF); // shift right 2 bytes, and pull the middle byte of the base address
    gdt_entries[index].base_high = ((base_address >> 24) & 0xFF); // shift right 3 bytes and pull the last byte of the base address

    // manipulate the limit variable into the struct
    gdt_entries[index].limit_low = (limit & 0xFFFF); // pull the lowest 2 bytes of the limit
    gdt_entries[index].limit_high = ((limit >> 16) & 0xF); // shift right 2 bytes and pull the highest 4 bits

    // manipulate the access and granularity_flags variable into the struct
    gdt_entries[index].granularity_flags = granularity_flags & 0x0F;
    gdt_entries[index].access_byte = access;
}

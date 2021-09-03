/**
* @file idt.cpp
* @author Ori Feldman
* @brief this file define the IDT handling operations
* @date 8/28/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/idt/idt.h>

IDT::IDTDescriptor idt_entries[IDT::kNumOfEntries] = { 0 };
IDT::IDTPointer idt_ptr = { 0, 0 };

/**
 * initializes the IDT with new interrupts descriptors
 */
void IDT::Initialize() {
    // set up idt pointer struct
    idt_ptr.size = (sizeof(IDT::IDTDescriptor) * IDT::kNumOfEntries) - 1; // set 16 bit size address of the table
    idt_ptr.base_address = (u32int)idt_entries; // set 32 bit base address of the IDT



    idt_flush(&idt_ptr); // flush the new idt and set the address to the idtr register
}

/**
 * insert new interrupt descriptor by the required fields - see the full structure in the end of descriptor_structure.h
 * @param index - index of the interrupt descriptor (in the IDT)
 * @param offset - relative address from the segment base address when the ISR is located at
 * @param segment_selector - segment selector where the ISR is located at (CS, PL0 - mostly)
 * @param attributes - attributes of the interrupt (type, dpl, etc...)
 */
void IDT::InsertDescriptor(u32int index, u32int offset, u16int segment_selector, u8int attributes) {
    if (index >= kNumOfEntries)
        K_PANIC("index of descriptor is overflowed");

    K_LOG("Created isr descriptor [%d] - segment selector: %x, offset: %x", index, segment_selector, offset);

    // insert the offset into the interrupt descriptor struct (offset beyond the segment base address)
    idt_entries[index].offset_low = (u16int)(offset & 0xFFFF);
    idt_entries[index].offset_high = (u16int)((offset << 16) & 0xFFFF);

    // set segment selector where the ISR is located at (CS selector)
    idt_entries[index].segment_selector = (u16int)segment_selector;

    // set unused byte
    idt_entries[index].unused = (u8int)0;

    // set interrupt descriptor attributes (type, dpl, etc...)
    idt_entries[index].attributes = (u8int)attributes;
}
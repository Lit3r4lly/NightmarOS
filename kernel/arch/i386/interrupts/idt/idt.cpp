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

    K_LOG("Created IDT pointer struct");
    IDT::SetupInterrupts(); // create the first 32 descriptors in the idt
    K_LOG("Created %d new descriptors", IDT::kNumOfEntries);

    IDT::FlushTable(); // flush the new idt and set the address to the idtr register
}

/*
 * flushing the idtr register with the new idt base address and table size
 */
void IDT::FlushTable() {
    asm volatile ("lidt %0" : : "m"(idt_ptr));
}

/**
 * insert new interrupt descriptor by the required fields - see the full structure in the end of descriptor_structure.h
 * @param index - index of the interrupt descriptor (in the IDT)
 * @param offset - relative address from the segment base address when the ISR is located at
 * @param segment_selector - segment selector where the ISR is located at (CS, PL0 - mostly)
 * @param attributes - attributes of the interrupt (type, dpl, etc...)
 */
void IDT::InsertDescriptor(u32int index, u32int offset, u16int segment_selector, u8int attributes) {
    if (index >= kNumOfEntries) {
        K_LOG("Index %x is not in the idt range", index);
        return;
    }

    K_LOG("Created interrupt descriptor [%d] - segment selector: %x, offset: %x", index, segment_selector, offset);

    // insert the offset into the interrupt descriptor struct (offset beyond the segment base address)
    idt_entries[index].offset_low = (u16int)(offset & 0xFFFF);
    idt_entries[index].offset_high = (u16int)((offset >> 16) & 0xFFFF);

    // set segment selector where the ISR is located at (CS selector)
    idt_entries[index].segment_selector = (u16int)segment_selector;

    // set unused byte
    idt_entries[index].unused = (u8int)0;

    // set interrupt descriptor attributes (type, dpl, etc...)
    idt_entries[index].attributes = (u8int)attributes;
}

/**
 * inserting to the idt the first 32 interrupts
 */
void IDT::SetupInterrupts() {
    // setup regular interrupts in the IDT
    IDT::InsertDescriptor(0, reinterpret_cast<u32int>(isr_0), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(1, reinterpret_cast<u32int>(isr_1), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(2, reinterpret_cast<u32int>(isr_2), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(3, reinterpret_cast<u32int>(isr_3), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(4, reinterpret_cast<u32int>(isr_4), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(5, reinterpret_cast<u32int>(isr_5), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(6, reinterpret_cast<u32int>(isr_6), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(7, reinterpret_cast<u32int>(isr_7), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(8, reinterpret_cast<u32int>(isr_8), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(9, reinterpret_cast<u32int>(isr_9), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(10, reinterpret_cast<u32int>(isr_10), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(11, reinterpret_cast<u32int>(isr_11), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(12, reinterpret_cast<u32int>(isr_12), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(13, reinterpret_cast<u32int>(isr_13), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(14, reinterpret_cast<u32int>(isr_14), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(15, reinterpret_cast<u32int>(isr_15), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(16, reinterpret_cast<u32int>(isr_16), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(17, reinterpret_cast<u32int>(isr_17), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(18, reinterpret_cast<u32int>(isr_18), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(19, reinterpret_cast<u32int>(isr_19), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(20, reinterpret_cast<u32int>(isr_20), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(21, reinterpret_cast<u32int>(isr_21), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(22, reinterpret_cast<u32int>(isr_22), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(23, reinterpret_cast<u32int>(isr_23), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(24, reinterpret_cast<u32int>(isr_24), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(25, reinterpret_cast<u32int>(isr_25), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(26, reinterpret_cast<u32int>(isr_26), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(27, reinterpret_cast<u32int>(isr_27), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(28, reinterpret_cast<u32int>(isr_28), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(29, reinterpret_cast<u32int>(isr_29), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(30, reinterpret_cast<u32int>(isr_30), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(31, reinterpret_cast<u32int>(isr_31), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);

    // setup IRQs in the IDT
    IDT::InsertDescriptor(32, reinterpret_cast<u32int>(irq_0), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(33, reinterpret_cast<u32int>(irq_1), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(34, reinterpret_cast<u32int>(irq_2), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(35, reinterpret_cast<u32int>(irq_3), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(36, reinterpret_cast<u32int>(irq_4), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(37, reinterpret_cast<u32int>(irq_5), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(38, reinterpret_cast<u32int>(irq_6), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(39, reinterpret_cast<u32int>(irq_7), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(40, reinterpret_cast<u32int>(irq_8), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(41, reinterpret_cast<u32int>(irq_9), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(42, reinterpret_cast<u32int>(irq_10), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(43, reinterpret_cast<u32int>(irq_11), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(44, reinterpret_cast<u32int>(irq_12), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(45, reinterpret_cast<u32int>(irq_13), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(46, reinterpret_cast<u32int>(irq_14), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
    IDT::InsertDescriptor(47, reinterpret_cast<u32int>(irq_15), IDT::kKernelCodeSelector, IDT::DescriptorAttributes::kValidInterrupt);
}
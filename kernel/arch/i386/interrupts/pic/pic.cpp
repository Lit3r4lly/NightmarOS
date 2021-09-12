/**
* @file pic.cpp
* @author Oshri Taub
* @brief this file implement th PIC handler
* @date 11/09/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pic/pic.h>

/**
 * Encapsulate the remap function
 */
void PIC::Initialize() {
    PIC::Remap(PIC::kMasterOffset, PIC::kSlaveOffset);
    K_LOG("Remapped the master and slave PICs");
}

/**
 * function to remap the master and slave PICs to new offsets
 * @param master_offset - the new master IDT offset
 * @param slave_offset  - the new slave IDT offset
 */
void PIC::Remap(int master_offset, int slave_offset) {
    u8int master_masks, slave_masks = 0;

    K_LOG("Remapping PICs");
    K_LOG("New master offset: %x", master_offset);
    K_LOG("New slave offset: %x", slave_offset);

    // save masks
    master_masks = Ports::InB(PIC::kMasterData);
    slave_masks = Ports::InB(PIC::kSlaveData);

    // starts the initialization sequence (in cascade mode)
    Ports::OutB(PIC::kMasterCommand, PIC::kICW1Init | PIC::kICW1ICW4);
    Ports::IoWait();
    Ports::OutB(PIC::kSlaveCommand, PIC::kICW1Init | PIC::kICW1ICW4);
    Ports::IoWait();

    // gives the PIC new offsets
    Ports::OutB(PIC::kMasterData, master_offset);
    Ports::IoWait();
    Ports::OutB(PIC::kSlaveData, slave_offset);
    Ports::IoWait();

    // tells the PICs that slave/master exists
    Ports::OutB(PIC::kMasterData, 4);
    Ports::IoWait();
    Ports::OutB(PIC::kSlaveData, 2);
    Ports::IoWait();
    
    // gives additional info about the architecture
    Ports::OutB(PIC::kMasterData, PIC::kICW48086);
    Ports::IoWait();
    Ports::OutB(PIC::kSlaveData, PIC::kICW48086);
    Ports::IoWait();

    // restore masks
    Ports::OutB(PIC::kMasterData, master_masks);
    Ports::OutB(PIC::kSlaveData, slave_masks);
}

/**
 * sends end-of-interrupt to the pic chip when the interrupt routine is done \ end
 * @param irq - irq number
 */
void PIC::SendEOI(u8int irq) {
    // if the irq came from slave PIC - sends EOI both to slave and both to master
    // if the irq came from master PIC - sends EOI only to the master
    if (irq >= PIC::kSlaveOffset)
        Ports::OutB(PIC::kSlaveCommand, PIC::kEOI);

    Ports::OutB(PIC::kMasterCommand, PIC::kEOI);

    K_LOG("Sent End-Of-Interrupt for irq: %x", irq);
}


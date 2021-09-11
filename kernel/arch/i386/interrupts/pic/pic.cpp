/**
* @file pic.cpp
* @author Oshri Taub
* @brief this file implement th PIC handler
* @date 11/09/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pic/pic.h>

/**
 * function to remap the master and slave PICs to new offsets
 * @param master_offset - the new master IDT offset
 * @param slave_offset  - the new slave IDT offset
 */
void PIC::PICRemap(int master_offset, int slave_offset) {
    u8int master_masks, slave_masks = 0;

    K_LOG("Remapping PICs");
    K_LOG("New master offset: %x", master_offset);
    K_LOG("New slave offset: %x", slave_offset);

    // save masks
    master_masks = Ports::InB(PIC::kPICMasterData);
    slave_masks = Ports::InB(PIC::kPICSlaveData);

    // starts the initialization sequence (in cascade mode)
    Ports::OutB(PIC::kPICMasterCommand, PIC::kICW1Init | PIC::kICW1ICW4);
    Ports::IoWait();
    Ports::OutB(PIC::kPICSlaveCommand, PIC::kICW1Init | PIC::kICW1ICW4);
    Ports::IoWait();

    // gives the PIC new offsets
    Ports::OutB(PIC::kPICMasterData, master_offset);
    Ports::IoWait();
    Ports::OutB(PIC::kPICSlaveData, slave_offset);
    Ports::IoWait();

    // tells the PICs that slave/master exists
    Ports::OutB(PIC::kPICMasterData, 4);
    Ports::IoWait();
    Ports::OutB(PIC::kPICSlaveData, 2);
    Ports::IoWait();
    
    // gives additional info about the architecture
    Ports::OutB(PIC::kPICMasterData, PIC::kICW48086);
    Ports::IoWait();
    Ports::OutB(PIC::kPICSlaveData, PIC::kICW48086);
    Ports::IoWait();

    // restore masks
    Ports::OutB(PIC::kPICMasterData, master_masks);
    Ports::OutB(PIC::kPICSlaveData, slave_masks);
}

/**
 * Encapsulate the remap function
 */
void PIC::Initialize() {
    PIC::PICRemap(0x20, 0x28);
    K_LOG("Remapped the master and slave PICs");
}


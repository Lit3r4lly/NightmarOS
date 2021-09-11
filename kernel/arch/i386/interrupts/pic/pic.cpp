/**
* @file pic.cpp
* @author Oshri Taub
* @brief this file implement th PIC handler
* @date 11/09/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pic/pic.h>

void PIC::PicRemap(int offset1, int offset2)
{
    u8int a1, a2;

    a1 = Ports::InB(PIC::kPic1Data);                        // save masks
    a2 = Ports::InB(PIC::kPic2Data);

    Ports::OutB(PIC::kPic1Command, PIC::kIcw1Init | PIC::kIcw1Icw4);  // starts the initialization sequence (in cascade mode)
    Ports::IoWait();
    Ports::OutB(PIC::kPic2Command, PIC::kIcw1Init | PIC::kIcw1Icw4);
    Ports::IoWait();
    Ports::OutB(PIC::kPic1Data, offset1);                 // ICW2: Master PIC vector offset
    Ports::IoWait();
    Ports::OutB(PIC::kPic2Data, offset2);                 // ICW2: Slave PIC vector offset
    Ports::IoWait();
    Ports::OutB(PIC::kPic1Data, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    Ports::IoWait();
    Ports::OutB(PIC::kPic2Data, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
    Ports::IoWait();

    Ports::OutB(PIC::kPic1Data, PIC::kIcw48086);
    Ports::IoWait();
    Ports::OutB(PIC::kPic2Data, PIC::kIcw48086);
    Ports::IoWait();

    Ports::OutB(PIC::kPic1Data, a1);   // restore saved masks.
    Ports::OutB(PIC::kPic2Data, a2);
}

void PIC::Initialize() {
    PIC::PicRemap(0x8, 0x70);
    K_LOG("remapped the master and slave PICs");
}


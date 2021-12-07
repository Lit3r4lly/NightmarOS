/**
* @file pit.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 07/12/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pit/pit.h>

void PIT::SetPITCount(uint8_t count) {
    //asm volatile ("cli");

    Ports::OutB(PIT::kChannel0,count & 0xFF);
    Ports::OutB(PIT::kChannel0,(count >> 8) & 0xFF);

    K_LOG("New PIT frequency has been set %d", count);
    //asm volatile ("sti");
}

void PIT::Initialize() {
    K_LOG("initialized the PIT");

    Timer::Initialize();
    Ports::OutB(PIT::kCommandChannel, PIT::kPITInitCmd);
    PIT::SetPITCount(PIT::kClockFrequency);
}
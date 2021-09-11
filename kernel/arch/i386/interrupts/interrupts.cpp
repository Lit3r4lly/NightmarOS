/**
* @file interrupts.cpp
* @author Ori Feldman
* @brief define interrupts control
* @date 9/6/21
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/interrupts.h>

/**
 * initializing all interrupts components (IDT ISRs, PIC, etc.)
 */
void Interrupts::Initialize() {
    IDT::Initialize();
    ISR::Initialize();
    PIC::Initialize();
}

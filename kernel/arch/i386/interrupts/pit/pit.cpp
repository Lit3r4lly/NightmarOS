/**
* @file pit.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 07/12/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pit/pit.h>

/**
 * Initializing the PIT to predefined frequency ~10ms
 */
void PIT::Initialize() {
    K_LOG("Initializing The PIT with frequency of %d", PIT::kTimerFreq)

    Ports::OutB(PIT::kPITChannel3, PIT::kPITInitCommand);
    PIT::SetPITCount(PIT::kTimerFreq);
}

/**
 * function to set the PIT to new frequency
 * @param freq - the wanted frequency
 */
void PIT::SetPITCount(uint8_t freq) {
    Ports::OutB(PIT::kPITChannel0,freq & 0xFF);
    Ports::OutB(PIT::kPITChannel0, freq >> 8);
}

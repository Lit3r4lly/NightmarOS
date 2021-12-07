/**
* @file timer.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 07/12/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pit/timer.h>

uint64_t Timer::counter;

void Timer::Initialize() {
    Timer::counter = 0;
    ISR::InsertUniqueHandler(ISR::kNumOfExceptions, ISR::Handler {Timer::IncCounter, true, true});
}

void Timer::IncCounter(uint8_t, ISR::StackState) {
    Timer::counter++;
}

void Timer::Sleep(uint64_t time)
{
    uint64_t wait_time = Timer::counter;
    while((Timer::counter - wait_time) < time)
    {
        asm volatile("hlt");
    }
}

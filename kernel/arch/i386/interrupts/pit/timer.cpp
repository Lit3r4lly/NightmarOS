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
    ISR::Handler handler {Timer::IncCounter, true, true};
    ISR::InsertUniqueHandler(0x20, handler);
    PIT::Initialize();
}

void Timer::IncCounter(uint8_t irq_num, ISR::StackState stack_state) {
    Timer::counter++;
}

void Timer::Sleep(uint64_t amount) {
    uint64_t curr = Timer::counter;

    while ((Timer::counter - curr) < amount)
        asm volatile("hlt;");
}

/**
* @file timer.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 07/12/2021
* @copyright Copyright (c) 2021
*/

#include <arch/i386/interrupts/pit/timer.h>

uint64_t Timer::counter;

/**
 * function to initialize the timer
 */
void Timer::Initialize() {
    Timer::counter = 0;
    ISR::InsertUniqueHandler(ISR::kNumOfExceptions, ISR::Handler {Timer::IncCounter, true, true});
}

/**
 * the pit handler the inc the internal counter
 */
void Timer::IncCounter(uint8_t, ISR::StackState) {
    Timer::counter++;
}

/**
 * implementation of sleep
 * @param time - the amount if time to sleep in ms
 */
void Timer::Sleep(uint64_t time)
{
    // FIXME: this shit is making some troubles...
    uint64_t wait_time = Timer::counter;
    while((Timer::counter - wait_time) < (time / 10))
    {
        asm volatile("hlt");
    }
}

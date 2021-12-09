/**
* @file timer.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 07/12/2021
* @copyright Copyright (c) 2021
*/

#pragma once
#include <kernel/common/kdefines.h>
#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <kernel/ports/ports.h>
#include <arch/i386/interrupts/isr/isr.h>

namespace Timer {
    extern uint64_t counter; //the internal counter

    void Initialize(); //function to init the timer
    void Sleep(uint64_t time); //function that make the sys sleep
    void IncCounter(uint8_t, ISR::StackState); //the handler function for the pit
}
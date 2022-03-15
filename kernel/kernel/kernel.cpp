/**
* @file kernel.cpp
* @author Ori Feldman
* @brief define kernel entry point (main) file for initializations and so on
* @date 8/3/21
* @copyright Copyright (c) 2021
*/

#include <kernel/kernel.h>

/**
 * Entry point for the run of the kernel
 * In this point there some initialization of the components that necessary for running the system.
 */
C_SCOPE NO_RETURN void kernel_main() {
    K_LOG("Entered to kernel_main");


    /**
     * Initialization process:
     * 1. TTY
     * 2. GDT
     * 3. Interrupts (IDT, PIC, etc.)
     * ...
     */

    GDT::Initialize();
    Interrupts::Initialize();
    Paging::Initialize();
    TTY::Initialize();

    Keyboard::Initialize(PS2Keyboard::KeyboardSource);

    K_LOG("set up is complete");

    printf("Hello! \nWelcome to NightmareOS kernel ;^)\n");
    printf("Enter whatever you would like: ");


    // halt the cpu forever and avoid the system to shutdown
    while (true)
        asm volatile ("hlt;");
}
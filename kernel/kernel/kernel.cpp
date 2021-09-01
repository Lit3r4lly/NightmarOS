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
    TTY::Initialize();
    GDT::Initialize();
    printf("Hello! \nWelcome to NightmareOS kernel ;^)\n");

    // wait (halt) for interrupt
    asm volatile ("hlt;");
}
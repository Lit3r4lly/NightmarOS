//
// Created by ori on 8/3/21.
//

#include <kernel/kernel.h>

/**
 * Entry point for the run of the kernel
 * In this point there some initialization of the components that necessary for running the system.
 */
C_SCOPE void kernel_main() {
    TTY::Initialize();
    GDT::Initialize();
    TTY::WriteString("Hello World!\nJust entered to NightmareOS kernel!\n");
}
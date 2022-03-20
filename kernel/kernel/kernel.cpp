/**
* @file kernel.cpp
* @author Ori Feldman
* @brief define kernel entry point (main) file for initializations and so on
* @date 8/3/21
* @copyright Copyright (c) 2021
*/

#include <kernel/kernel.h>
#include <arch/i386/paging/memory_manager.h>
void heap_demon ();
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
    heap_demon();

    printf("Hello! \nWelcome to NightmareOS kernel ;^)\n");
    printf("Enter whatever you would like: ");

    // halt the cpu forever and avoid the system to shutdown
    while (true)
        asm volatile ("hlt;");
}


void heap_demon (){
    uint32_t* b = (uint32_t*)malloc(8);
    uint32_t* c = (uint32_t*) malloc(8);

    printf("b: %x, c:%x\n",b,c);
    *c = 12;

    free((void*)c);
    free((void*)b);

    uint32_t d = (uint32_t)malloc(12);

    printf("d: %x\n",d);

};
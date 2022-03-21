/**
* @file kernel.cpp
* @author Ori Feldman
* @brief define kernel entry point (main) file for initializations and so on
* @date 8/3/21
* @copyright Copyright (c) 2021
*/

#include <kernel/kernel.h>
void heap_demon();
void input_demon();

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
    Timer::Sleep(20000);
    printf("after sleep !!!\n");

    heap_demon();
    input_demon();


    // halt the cpu forever and avoid the system to shutdown
    while (true)
        asm volatile ("hlt;");
}


void heap_demon (){
    uint32_t* b = new uint32_t;
    uint32_t* c = new uint32_t;

    printf("b: %x, c:%x\n",b,c);
    *c = 12;
    printf("c: %d\n", *c);

    delete b;
    delete c;
};


void input_demon() {
    char* str = new char[4];

    gets(str);
    printf("%s\n",str);

    delete []str;
}
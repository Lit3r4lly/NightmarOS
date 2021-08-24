//
// Created by ori on 8/3/21.
//

#include <arch/i386/tty/tty.h>
#include <arch/i386/gdt/gdt.h>

extern "C" void kernel_main() {
    TTY::Initialize();
    GDT::Initialize();
    TTY::WriteString("Hello World!\nJust entered to NightmareOS kernel!\n");
}
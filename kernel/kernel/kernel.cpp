//
// Created by ori on 8/3/21.
//

#include <arch/i386/TTY/tty.h>
#include <arch/i386/GDT/gdt.h>

extern "C" void kernel_main() {
    TTY::Initialize();
    GDT::Initialize();
    TTY::WriteString("Hello World!\nJust entered to NightmareOS kernel!\n");
}
/**
* @file stdio.h
* @author Ori Feldman
* @brief declare stdio libc functions
* @date 8/19/21
* @copyright Copyright (c) 2021
*/

#pragma once

#if defined(__is_libk)
#include <arch/i386/tty/tty.h>
#endif

#include <libc/ldefines.h>

#ifdef __cplusplus
C_SCOPE {
#endif

    u8int putchar(u8int ich); // print char to the screen using the TTY
    u32int printf(const char* format,...); //print formatted string to the screen

#ifdef __cplusplus
};
#endif
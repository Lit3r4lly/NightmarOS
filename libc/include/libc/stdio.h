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

#ifdef __cplusplus
C_SCOPE {
#endif

    int putchar(int ich); // print char to the screen using the TTY
    int printf(const char* format,...);

#ifdef __cplusplus
};
#endif
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

    uint8_t putchar(uint8_t ich); // print char to the screen using the TTY
    uint32_t printf(const char* format, ...); //print formatted string to the screen
    void getc(char* p);
    void gets(char* p);
    void geti(int32_t* p);

#ifdef __cplusplus
};
#endif
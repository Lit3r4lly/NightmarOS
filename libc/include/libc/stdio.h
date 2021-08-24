//
// Created by ori on 8/19/21.
//

#pragma once

#if defined(__is_libk)
#include <arch/i386/tty/tty.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

    int putchar(int ich); // print char to the screen using the TTY

#ifdef __cplusplus
};
#endif
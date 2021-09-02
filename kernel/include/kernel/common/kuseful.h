/**
* @file kuseful.h
* @author Ori Feldman
* @brief declare useful shitty stuff for the kernel
* @date 9/2/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <kernel/panic/panic.h>

#define K_PANIC(info) Panic::Panic(info, __FILE__, __FUNCTION__, __LINE__)

#ifdef __cplusplus
#define assert(expr) (static_cast<bool>(expr) \
                    ? void (0)                \
                    : K_PANIC(#expr))
#else
#define assert(expr) ((expr \
                     ? void (0)       \
                     : K_PANIC(#expr))
#endif
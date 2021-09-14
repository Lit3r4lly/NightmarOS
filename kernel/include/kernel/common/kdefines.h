/**
* @file kdefines.h
* @author Ori Feldman
* @brief kernel common definitions
* @date 8/3/21
* @copyright Copyright (c) 2021
*/

#pragma once

// freestanding headers
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#define C_SCOPE extern "C"
#define ASM_SCOPE extern "C"

#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wattributes"
    #define IGNORE(warning) GCC diagnostic ignored "warning"
    #define PACKED __attribute__((packed))
    #define NO_RETURN __attribute__((__noreturn__))
#endif